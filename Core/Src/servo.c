/*
 * servo.c
 *
 *  Created on: May 5, 2026
 *      Author: club
 */

#include "servo.h"

void initServoHandle(ServoHandleCreateInfo* createInfo, ServoHandle* handle)
{
	handle->timer = createInfo->timer;

}

void setServoAngle0(ServoHandle* servoHandle, float angle)
{

}

void setServoAngled1(ServoHandle* servoHandle, float angle, float speed)
{

}

void setServoAngled2(ServoHandle* servoHandle, float angle, float speed, float acceleration)
{

}

void updateServo(ServoHandle* servoHandle, uint32_t deltaTime)
{

}

