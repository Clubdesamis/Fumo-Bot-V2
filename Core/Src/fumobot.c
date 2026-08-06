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
}

uint16_t readADC()
{
	HAL_ADC_PollForConversion(handles.sensorAdc, 1000);
	uint16_t readValue = HAL_ADC_GetValue(handles.sensorAdc);
	HAL_ADC_Start(handles.sensorAdc);

	return readValue;
}

void fumobot_mainLoop()
{

	uint16_t readValue = readADC();
	int e = 2;


	static bool set = true;

	if(set)
	{
		emote_start(player, testEmote, sizeof(testEmote));
		set = false;
	}

	HAL_Delay(10);

	bool bs = emote_update(player, 10);


}
