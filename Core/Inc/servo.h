/*
 * servo.h
 *
 *  Created on: May 5, 2026
 *      Author: club
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

// Includes
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdlib.h>
// Constants
#define ANGLE_MAX 180


// TODO À changer à 320000 quand on installe les servos
#define PW_MIN 0
// TODO À changer à 320000 quand on installe les servos
#define PW_MAX 160000
// TODO À changer à 320000 quand on installe les servos
#define PW_WHOLE PW_MAX - PW_MIN

#define PW_PER_DEGREE PW_WHOLE / ANGLE_MAX

#define SERVO_1_CHANNEL TIM_CHANNEL_1
#define SERVO_2_CHANNEL TIM_CHANNEL_2
#define SERVO_3_CHANNEL TIM_CHANNEL_3
#define SERVO_4_CHANNEL TIM_CHANNEL_4

#define SERVO_ARM_RIGHT_CHANNEL SERVO_1_CHANNEL
#define SERVO_ARM_LEFT_CHANNEL SERVO_2_CHANNEL
#define SERVO_BOUNCE_RIGHT_CHANNEL SERVO_3_CHANNEL
#define SERVO_BOUNCE_LEFT_CHANNEL SERVO_4_CHANNEL

#define SERVO_ARM_RIGHT_SIGN = -1
#define SERVO_ARM_LEFT_SIGN = 1
#define SERVO_BOUNCE_RIGHT_SIGN = -1
#define SERVO_BOUNCE_LEFT_SIGN = 1

// Structures

typedef struct ServoHandleCreateInfo
{
	//Handle to the timer used to generate PWM for the servo
	TIM_HandleTypeDef* timer;
	//Timer channel which generates PWM for the servo
	uint8_t timerChannel;
	//Minimum pulse width accepted (effectively "0 degrees")
	uint32_t minPulseWidth;
	//Maximum pulse width accepted (max angle)
	uint32_t maxPulseWidth;
	//Maximum angle to be reached by the servo
	float maxAngle;
	//Offset angle, used to calibrate the servo in case of misalignment
	float offsetAngle;
	//Determines in which direction the servo moves
	bool inverted;
} ServoHandleCreateInfo;

typedef struct ServoHandle
{
	//Handle to the timer used to generate PWM for the servo
	const TIM_HandleTypeDef* timer;
	//Timer channel which generates PWM for the servo
	uint32_t timerChannel;
	//Minimum pulse width accepted (effectively "0 degrees")
	uint32_t minPulseWidth;
	//Maximum pulse width accepted (max angle)
	uint32_t maxPulseWidth;
	//Offset angle, used to calibrate the servo in case of misalignment
	float offset;
	//The servo's current angle
	float angle;
	//The servo's target angle
	float targetAngle;
	//The servo's current movement speed
	float speed;
	//The servo's target movement speed
	float targetSpeed;
	//The servo's current acceleration (probably won't be used, let's be honest)
	float acceleration;
	//Determines in which direction the servo moves
	bool inverted;
} ServoHandle;

void initServoHandle(ServoHandleCreateInfo* createInfo, ServoHandle* handle);
void setServoAngle0(ServoHandle* servoHandle, float angle);
void setServoAngled1(ServoHandle* servoHandle, float angle, float speed);
void setServoAngled2(ServoHandle* servoHandle, float angle, float speed, float acceleration);
void updateServo(ServoHandle* servoHandle, uint32_t deltaTime);

#endif /* INC_SERVO_H_ */
