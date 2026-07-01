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
		.inverted = false //true
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
		.inverted = false //true
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


	static int set = 1;

	if(set)
	{
		setServoAngled1(&servoArmRight, 20.0, 5.0);
		//setServoAngled0(&servoArmRight, 90.0);
		//setServoAngled1(&servoArmLeft, 20.0, 1.0);
		//setServoAngled1(&servoBounceRight, 20.0, 1.0);
		//setServoAngled1(&servoBounceLeft, 20.0, 1.0);

		set = 0;
	}


	HAL_Delay(10);

	updateServo(&servoArmRight, 10);
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
