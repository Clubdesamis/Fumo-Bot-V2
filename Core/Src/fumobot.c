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
		.maxAngle = 120,//ANGLE_MAX,
		.inverted = true
	};

	servoHandleCreateInfo servoArmLeftCreateInfo =
	{
		.timer = handles.pwmTimer,
		.timerChannel = SERVO_ARM_LEFT_CHANNEL,
		.minPulseWidth = PW_MIN,
		.maxPulseWidth = PW_MAX,
		.maxAngle = 120,//ANGLE_MAX,
		.inverted = false
	};

	servoHandleCreateInfo servoBounceRightCreateInfo =
	{
		.timer = handles.pwmTimer,
		.timerChannel = SERVO_BOUNCE_RIGHT_CHANNEL,
		.minPulseWidth = PW_MIN,
		.maxPulseWidth = PW_MAX,
		.maxAngle = ANGLE_MAX,
		.inverted = true
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

void fumobot_mainLoop()
{


	servo_setAngled0(&servoArmRight, 0.0);
	servo_setAngled0(&servoArmLeft, 0.0);
	//servo_setAngled0(&servoBounceRight, 0.0);
	//servo_setAngled0(&servoBounceLeft, 0.0);
	HAL_Delay(800);
	servo_setAngled0(&servoArmRight, 90.0);
	servo_setAngled0(&servoArmLeft, 90.0);
	//servo_setAngled0(&servoBounceRight, 90.0);
	//servo_setAngled0(&servoBounceLeft, 90.0);
	HAL_Delay(800);
	servo_setAngled0(&servoArmRight, 180.0);
	servo_setAngled0(&servoArmLeft, 180.0);
	//servo_setAngled0(&servoBounceRight, 180.0);
	//servo_setAngled0(&servoBounceLeft, 180.0);
	HAL_Delay(800);





		//servo_setAngled1(&servoArmLeft, 180.0, 10.0);


		//emote_start(player, testEmote, sizeof(testEmote));



	//servo_setAngled0(&servoArmRight, 0.0);
	//servo_setAngled0(&servoArmLeft, 0.0);
	//servo_setAngled0(&servoBounceRight, 0.0);
	//servo_setAngled0(&servoBounceLeft, 0.0);


	HAL_Delay(10);

	//if(servo_update(&servoArmLeft, 10))
	//{

		//servo_setAngled0(&servoArmRight, 180.0);
		//servo_setAngled0(&servoArmLeft, 180.0);
		//servo_setAngled0(&servoBounceRight, 180.0);
		//servo_setAngled0(&servoBounceLeft, 180.0);


		//emote_update(player, 10);
	//}

}
