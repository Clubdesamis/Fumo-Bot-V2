/*
 * fumobot.c
 *
 *  Created on: May 5, 2026
 *      Author: club
 */

#include "servo.h"
#include "fumobot.h"

// Variables
Handles handles;

servoHandle servoArmRight;
servoHandle servoArmLeft;
servoHandle servoBounceRight;
servoHandle servoBounceLeft;
servoHandle* servos[4];

emotePlayer* player;

bool emotePlaying = false;
int32_t emoteCooldown;

void fumobot_initHandles(const Handles* _handles)
{
	handles = *_handles;
}

void fumobot_init()
{
	servoHandleCreateInfo servoArmRightCreateInfo =
	{
		.timer = handles.pwmTimer,
		.timerChannel = SERVO_ARM_RIGHT_CHANNEL,
		.minPulseWidth = PW_MIN,
		.maxPulseWidth = PW_MAX,
		.minAngle = ARM_SERVO_ANGLE_MIN,
		.maxAngle = ARM_SERVO_ANGLE_MAX,
		.inverted = true
	};

	servoHandleCreateInfo servoArmLeftCreateInfo =
	{
		.timer = handles.pwmTimer,
		.timerChannel = SERVO_ARM_LEFT_CHANNEL,
		.minPulseWidth = PW_MIN,
		.maxPulseWidth = PW_MAX,
		.minAngle = ARM_SERVO_ANGLE_MIN,
		.maxAngle = ARM_SERVO_ANGLE_MAX,
		.inverted = false
	};

	servoHandleCreateInfo servoBounceRightCreateInfo =
	{
		.timer = handles.pwmTimer,
		.timerChannel = SERVO_BOUNCE_RIGHT_CHANNEL,
		.minPulseWidth = PW_MIN,
		.maxPulseWidth = PW_MAX,
		.minAngle = BOUNCE_SERVO_ANGLE_MIN,
		.maxAngle = BOUNCE_SERVO_ANGLE_MAX,
		.inverted = true
	};

	servoHandleCreateInfo servoBounceLeftCreateInfo =
	{
		.timer = handles.pwmTimer,
		.timerChannel = SERVO_BOUNCE_LEFT_CHANNEL,
		.minPulseWidth = PW_MIN,
		.maxPulseWidth = PW_MAX,
		.minAngle = BOUNCE_SERVO_ANGLE_MIN,
		.maxAngle = BOUNCE_SERVO_ANGLE_MAX,
		.inverted = false
	};

	servo_initHandle(&servoArmRightCreateInfo, &servoArmRight);
	servo_initHandle(&servoArmLeftCreateInfo, &servoArmLeft);
	servo_initHandle(&servoBounceRightCreateInfo, &servoBounceRight);
	servo_initHandle(&servoBounceLeftCreateInfo, &servoBounceLeft);

	servos[0] = &servoArmRight;
	servos[1] = &servoArmLeft;
	servos[2] = &servoBounceRight;
	servos[3] = &servoBounceLeft;

	emotePlayerCreateInfo playerCreateInfo =
	{
		.servoCount = 4,
		.servos = servos
	};

	player = emote_initPlayer(&playerCreateInfo);

	servo_setAngled0(&servoArmRight, 90);
	servo_setAngled0(&servoArmLeft, 90);
	servo_setAngled0(&servoBounceRight, 90);
	servo_setAngled0(&servoBounceLeft, 90);
}

uint16_t readADC()
{
	HAL_ADC_PollForConversion(handles.sensorAdc, 1000);
	uint16_t readValue = HAL_ADC_GetValue(handles.sensorAdc);
	HAL_ADC_Start(handles.sensorAdc);

	return readValue;
}

void fumobot_mainLoop(uint32_t deltaTime)
{
	uint16_t readValue = readADC();

	if(emotePlaying)
	{
		if(emote_update(player, deltaTime))
		{
			emotePlaying = false;
			emoteCooldown = EMOTE_COOLDOWN_MS;
		}
	}
	else
	{
		if(emoteCooldown > 0)
		{
			if(emoteCooldown - deltaTime <= 0)
			{
				emoteCooldown = 0;
			}
			else
			{
				emoteCooldown -= deltaTime;
			}
		}
		else
		{
			if(readValue >= SENSOR_CLOSE_THRESHOLD)
			{
				uint32_t randomEmoteIndex = readValue % (sizeof(emotePool) / sizeof(uint32_t*));
				emote_start(player, emotePool[randomEmoteIndex], emotePoolSizes[randomEmoteIndex]);
				emotePlaying = true;
			}
		}
	}

	HAL_Delay(DELAY_TIME_MS);
}
