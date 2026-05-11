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

ServoHandle servoArmRight;
ServoHandle servoArmLeft;
ServoHandle servoBounceRight;
ServoHandle servoBounceLeft;

void initHandles(const Handles* _handles)
{
	handles = *_handles;
}

void initServos()
{
	ServoHandleCreateInfo servoArmRightCreateInfo =
	{
		.timer = handles.pwmTimer,
		.timerChannel = SERVO_ARM_RIGHT_CHANNEL,
		.minPulseWidth = PW_MIN,
		.maxPulseWidth = PW_MAX,
		.maxAngle = ANGLE_MAX,
		.inverted = true
	};

	ServoHandleCreateInfo servoArmLeftCreateInfo =
	{
		.timer = handles.pwmTimer,
		.timerChannel = SERVO_ARM_LEFT_CHANNEL,
		.minPulseWidth = PW_MIN,
		.maxPulseWidth = PW_MAX,
		.maxAngle = ANGLE_MAX,
		.inverted = false
	};

	ServoHandleCreateInfo servoBounceRightCreateInfo =
	{
		.timer = handles.pwmTimer,
		.timerChannel = SERVO_BOUNCE_RIGHT_CHANNEL,
		.minPulseWidth = PW_MIN,
		.maxPulseWidth = PW_MAX,
		.maxAngle = ANGLE_MAX,
		.inverted = true
	};

	ServoHandleCreateInfo servoBounceLeftCreateInfo =
	{
		.timer = handles.pwmTimer,
		.timerChannel = SERVO_BOUNCE_LEFT_CHANNEL,
		.minPulseWidth = PW_MIN,
		.maxPulseWidth = PW_MAX,
		.maxAngle = ANGLE_MAX,
		.inverted = false
	};

	initServoHandle(&servoArmRightCreateInfo, &servoArmRight);
	initServoHandle(&servoArmLeftCreateInfo, &servoArmLeft);
	initServoHandle(&servoBounceRightCreateInfo, &servoBounceRight);
	initServoHandle(&servoBounceLeftCreateInfo, &servoBounceLeft);
}

void mainLoop()
{
	for(int i = 0; i <= 160000 / 2; i += 16)
	  {
		  //__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, i);
		  HAL_Delay(1);
	  }
}
