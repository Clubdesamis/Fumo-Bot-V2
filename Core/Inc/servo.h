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
#include <string.h>
// Constants
#define ANGLE_MIN 0
#define ANGLE_MAX 180



// TODO À changer à 320000 quand on installe les servos
#define PW_MIN 8000//0
// TODO À changer à 320000 quand on installe les servos
#define PW_MAX 40000
// TODO À changer à 320000 quand on installe les servos
#define PW_WHOLE PW_MAX - PW_MIN

#define PW_PER_DEGREE PW_WHOLE / ANGLE_MAX

#define SERVO_ARM_RIGHT_SIGN = -1
#define SERVO_ARM_LEFT_SIGN = 1
#define SERVO_BOUNCE_RIGHT_SIGN = -1
#define SERVO_BOUNCE_LEFT_SIGN = 1

// Structures

typedef enum _ServoState
{
	SERVO_STOPPED,
	SERVO_MOVING,
	SERVO_ERROR
} ServoState;

typedef struct
{
	//Handle to the timer used to generate PWM for the servo
	TIM_HandleTypeDef* timer;
	//Timer channel which generates PWM for the servo
	uint8_t timerChannel;
	//Minimum pulse width accepted (effectively "0 degrees")
	uint32_t minPulseWidth;
	//Maximum pulse width accepted (max angle)
	uint32_t maxPulseWidth;
	// Minimum angle to be reached by the servo
	float minAngle;
	// Maximum angle to be reached by the servo
	float maxAngle;
	// Offset angle, used to calibrate the servo in case of misalignment
	float offsetAngle;
	// Determines in which direction the servo moves
	bool inverted;
} servoHandleCreateInfo;

typedef struct
{
	//Handle to the timer used to generate PWM for the servo
	const TIM_HandleTypeDef* timer;
	//Timer channel which generates PWM for the servo
	uint32_t timerChannel;
	//Minimum pulse width accepted (effectively "0 degrees")
	uint32_t minPulseWidth;
	//Maximum pulse width accepted (max angle)
	uint32_t maxPulseWidth;
	//Determines in which direction the servo moves
	bool inverted;
	//Offset angle, used to calibrate the servo in case of misalignment
	float offsetAngle;
	// The pulse count per degree;
	float pulsePerDegree;
	// The servo's minimum angle
	float minAngle;
	//The servo's maximum angle
	float maxAngle;
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


} servoHandle;

void servo_initHandle(servoHandleCreateInfo* createInfo, servoHandle* handle);
void servo_setAngled0(servoHandle* servoHandle, float angle);
void servo_setAngled1(servoHandle* servoHandle, float angle, float speed);
bool servo_update(servoHandle* servoHandle, uint32_t deltaTime);

#endif /* INC_SERVO_H_ */
