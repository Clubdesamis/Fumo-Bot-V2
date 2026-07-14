#include "emote.h"

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
		player->servos[i].handle = createInfo->servos[i];
	}

	return player;
}

void emote_destroyPlayer(emotePlayer* player)
{
	free(player->servos);
	free(player);
}

bool emote_start(emotePlayer* player, uint32_t* emote)
{
	//Trouver le header et valider que le emote est bel et bien fait pour le bon nombre de servo que le player, sinon mettre en error state
	uint8_t c = GET_COMMAND_ID((command)emote[0]);
	//if(GET_COMMAND_ID(emote[0]) != COMMAND_HEADER || GET_SERVO_COUNT(emote[0]) != player->servoCount)
	//{
		//return false;
	//}
	//Pour chaque servo, trouver la commande START associée à son ID (index)
	//Si une commande start est introuvable ou qu'une commande start est invalide, mettre le player en error state
	for(uint32_t i = 0; i < player->servoCount; i++)
	{

	}

	return true;
}

bool emote_update(emotePlayer* player, uint32_t deltatime)
{

	return false;
}

void emote_finish(emotePlayer* player)
{

}
