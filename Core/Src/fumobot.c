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

void fumobot_initHandles(const Handles* _handles)
{
	handles = *_handles;
}

void fumobot_initServos()
{
	servoHandleCreateInfo servoArmRightCreateInfo =
	{
		.timer = handles.pwmTimer,
		.timerChannel = SERVO_ARM_RIGHT_CHANNEL,
		.minPulseWidth = PW_MIN,
		.maxPulseWidth = PW_MAX,
		.maxAngle = ANGLE_MAX,
		.inverted = false //true
	};

	servoHandleCreateInfo servoArmLeftCreateInfo =
	{
		.timer = handles.pwmTimer,
		.timerChannel = SERVO_ARM_LEFT_CHANNEL,
		.minPulseWidth = PW_MIN,
		.maxPulseWidth = PW_MAX,
		.maxAngle = ANGLE_MAX,
		.inverted = false
	};

	servoHandleCreateInfo servoBounceRightCreateInfo =
	{
		.timer = handles.pwmTimer,
		.timerChannel = SERVO_BOUNCE_RIGHT_CHANNEL,
		.minPulseWidth = PW_MIN,
		.maxPulseWidth = PW_MAX,
		.maxAngle = ANGLE_MAX,
		.inverted = false //true
	};

	servoHandleCreateInfo servoBounceLeftCreateInfo =
	{
		.timer = handles.pwmTimer,
		.timerChannel = SERVO_BOUNCE_LEFT_CHANNEL,
		.minPulseWidth = PW_MIN,
		.maxPulseWidth = PW_MAX,
		.maxAngle = ANGLE_MAX,
		.inverted = false
	};

	servo_initHandle(&servoArmRightCreateInfo, &servoArmRight);
	servo_initHandle(&servoArmLeftCreateInfo, &servoArmLeft);
	servo_initHandle(&servoBounceRightCreateInfo, &servoBounceRight);
	servo_initHandle(&servoBounceLeftCreateInfo, &servoBounceLeft);
}

void fumobot_mainLoop()
{


	static int set = 1;

	if(set)
	{
		servo_setAngled0(&servoArmRight, 0.0);
		servo_setAngled0(&servoArmLeft, 0.0);
		servo_setAngled0(&servoBounceRight, 0.0);
		servo_setAngled0(&servoBounceLeft, 0.0);

		servo_setAngled1(&servoArmLeft, 180.0, 60.0);

		set = 0;
	}


	HAL_Delay(10);

	if(servo_update(&servoArmLeft, 10))
	{
		servo_setAngled0(&servoArmRight, 180.0);
		//setServoAngled0(&servoArmLeft, 180.0);
		servo_setAngled0(&servoBounceRight, 180.0);
		servo_setAngled0(&servoBounceLeft, 180.0);
	}
	//updateServo(&servoArmLeft, 10);
	//updateServo(&servoBounceRight, 10);
	//updateServo(&servoBounceLeft, 10);


	/*
	setServoAngled0(&servoArmRight, 20.0);
	setServoAngled0(&servoArmLeft, 20);
	setServoAngled0(&servoBounceRight, 20);
	setServoAngled0(&servoBounceLeft, 20);
	HAL_Delay(500);
	setServoAngled0(&servoArmRight, 80);
	setServoAngled0(&servoArmLeft, 80);
	setServoAngled0(&servoBounceRight, 80);
	setServoAngled0(&servoBounceLeft, 80);
	HAL_Delay(500);
	setServoAngled0(&servoArmRight, 140);
	setServoAngled0(&servoArmLeft, 140);
	setServoAngled0(&servoBounceRight, 140);
	setServoAngled0(&servoBounceLeft, 140);
	HAL_Delay(500);
	setServoAngled0(&servoArmRight, 180);
	setServoAngled0(&servoArmLeft, 180);
	setServoAngled0(&servoBounceRight, 180);
	setServoAngled0(&servoBounceLeft, 180);
	HAL_Delay(500);
	*/
}
