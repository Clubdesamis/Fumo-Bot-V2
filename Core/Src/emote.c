#include "emote.h"
#include "servo.h"

emotePlayer* emote_initPlayer(emotePlayerCreateInfo* createInfo)
{
	emotePlayer* player = malloc(sizeof(emotePlayer));
	player->servoCount = createInfo->servoCount;
	player->servos = malloc(createInfo->servoCount * sizeof(emoteServoContext));
	player->state = STATE_STOPPED;

	for(uint32_t i = 0; i < createInfo->servoCount; i++)
	{
		player->servos[i].commandIndex = 0;
		player->servos[i].timeToWait = 0;
		player->servos[i].state = STATE_STOPPED;
		player->servos[i].handle = createInfo->servos[i];
	}

	return player;
}

void emote_destroyPlayer(emotePlayer* player)
{
	free(player->servos);
	free(player);
}

bool emote_start(emotePlayer* player, uint32_t* emote, uint32_t emoteSize)
{
	//Trouver le header et valider que le emote est bel et bien fait pour le bon nombre de servo que le player, sinon mettre en error state
	if(GET_COMMAND_ID(emote[0]) != COMMAND_HEADER || GET_SERVO_COUNT(emote[0]) != player->servoCount)
	{
		return false;
	}
	//Pour chaque servo, trouver la commande START associée à son ID (index)
	//Si une commande start est introuvable ou qu'une commande start est invalide, mettre le player en error state
	for(uint32_t i = 0; i < player->servoCount; i++)
	{
		for(int j = 0; j < emoteSize; j++)
		{
			if(GET_SERVO_ID(emote[j]) == i)
			{
				player->servos[i].commandIndex = j;
				player->servos[i].state = STATE_PLAYING;
				break;
			}
			else if(j == emoteSize - 1)
			{
				return false;
			}
		}
	}

	player->currentEmoteSize = emoteSize;
	player->currentEmote = emote;
	player->state = STATE_PLAYING;
	return true;
}

void goToNextCommand(uint8_t servoID, emotePlayer* player)
{
	uint32_t currentIndex = player->servos[servoID].commandIndex;
	for(uint32_t i = currentIndex + 1; i < player->currentEmoteSize; i++)
	{
		uint8_t servoId = GET_SERVO_ID(player->currentEmote[i]);
		if(servoId == servoID)
		{
			player->servos[servoID].timeToWait = 0;
			player->servos[servoID].state = STATE_PLAYING;
			player->servos[servoID].commandIndex = i;
			return;
		}
	}

	player->servos[servoID].timeToWait = 0;
	player->servos[servoID].state = STATE_ERROR;
}

bool emote_update(emotePlayer* player, uint32_t deltaTime)
{
	bool breakLoop = false;
	for(uint32_t servoIndex = 0; servoIndex < player->servoCount; servoIndex++)
	{
		command currentCommand = player->currentEmote[player->servos[servoIndex].commandIndex];
		switch(GET_COMMAND_ID(currentCommand))
		{
			case COMMAND_HEADER:
				player->state = STATE_ERROR;
			break;

			case COMMAND_START:
				//Find next command with same servo ID
				goToNextCommand(servoIndex, player);
			break;

			case COMMAND_FINISH:
				//Agir comme barrier et quand tlm a fini mettre le emote player à stopped
				player->servos[servoIndex].state = STATE_STOPPED;
			break;

			case COMMAND_SET_ANGLE_D0:
				//Call setAngled0
				servo_setAngled0(player->servos[servoIndex].handle, GET_ANGLE(currentCommand));
				//Find next command with same servo ID
				goToNextCommand(servoIndex, player);
			break;

			case COMMAND_SET_ANGLE_D1:
				//Si premier update: call la fonction setAngled1
				if(player->servos[servoIndex].state == STATE_PLAYING)
				{
					servo_setAngled1(player->servos[servoIndex].handle, GET_ANGLE(currentCommand), GET_SPEED(currentCommand));
					player->servos[servoIndex].state = STATE_WAITING;
				}
				else if(player->servos[servoIndex].state == STATE_WAITING)
				{
					if(servo_update(player->servos[servoIndex].handle, deltaTime))
					{
						player->servos[servoIndex].state = STATE_PLAYING;
						goToNextCommand(servoIndex, player);
					}
				}
				else
				{
					player->servos[servoIndex].state = STATE_ERROR;
				}
				//Si pas le premier: update le servo avec le deltaTime
				//Si le servo a fini de bouger, find next command with same servo ID
				//Sinon, ne rien faire et attendre le prochain update
			break;

			case COMMAND_DELAY:
				if(player->servos[servoIndex].state == STATE_PLAYING)
				{
					player->servos[servoIndex].timeToWait = GET_TIME_TO_WAIT(currentCommand);
					player->servos[servoIndex].state = STATE_WAITING;
				}
				else if(player->servos[servoIndex].state == STATE_WAITING)
				{
					if(deltaTime >= player->servos[servoIndex].timeToWait)
					{
						goToNextCommand(servoIndex, player);
					}
					else
					{
						player->servos[servoIndex].timeToWait -= deltaTime;
					}
				}
				else
				{
					player->servos[servoIndex].state = STATE_ERROR;
				}
			break;

			case COMMAND_BARRIER:
				if(player->servos[servoIndex].state == STATE_PLAYING)
				{
					player->servos[servoIndex].state = STATE_WAITING;
				}
				else if(player->servos[servoIndex].state == STATE_WAITING)
				{
					bool barrierFinished = true;

					for(int i = 0; i < player->servoCount; i++)
					{
						uint8_t commandID = GET_COMMAND_ID(player->currentEmote[player->servos[i].commandIndex]);
						uint8_t barrierID = GET_BARRIER_ID(player->currentEmote[player->servos[i].commandIndex]);

						if(commandID != COMMAND_BARRIER || GET_BARRIER_ID(currentCommand) != barrierID)
						{
							barrierFinished = false;
						}
					}

					if(barrierFinished)
					{
						for(int j = 0; j < player->servoCount; j++)
						{
							player->servos->state = STATE_PLAYING;
							goToNextCommand(j, player);
						}

						breakLoop = true;
					}
				}
				else
				{
					player->servos[servoIndex].state = STATE_ERROR;
				}
			break;
		}

		if(breakLoop)
		{
			break;
		}
	}

	bool finished = true;
	for(int i = 0; i < player->servoCount; i++)
	{
		if(player->servos[i].state != STATE_STOPPED)
		{
			finished = false;
		}
	}

	return finished;
}

void emote_finish(emotePlayer* player)
{

}
