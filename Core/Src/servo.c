/*
 * servo.c
 *
 *  Created on: May 5, 2026
 *      Author: club
 */

#include "servo.h"

void initServoHandle(ServoHandleCreateInfo* createInfo, ServoHandle* handle)
{
	// Making sure the whole struct is set to zero (you never know lmao)
	memset(handle, 0, sizeof(ServoHandle));
	handle->timer = createInfo->timer;
	handle->timerChannel = createInfo->timerChannel;
	handle->minPulseWidth = createInfo->minPulseWidth;
	handle->maxPulseWidth = createInfo->maxPulseWidth;
	handle->minAngle = createInfo->minAngle;
	handle->maxAngle = createInfo->maxAngle;
	handle->offsetAngle = createInfo->offsetAngle;
	handle->inverted = createInfo-> inverted;
	handle->pulsePerDegree = (createInfo->maxPulseWidth - createInfo->minPulseWidth) / (createInfo->maxAngle - createInfo->minAngle);
}

void setServoAngled0(ServoHandle* servo, float angle)
{
	uint32_t pulse = 0;

	if(angle > servo->maxAngle)
	{
		angle = servo->maxAngle;
	}
	else if(angle < ANGLE_MIN)
	{
		angle = ANGLE_MIN;
	}

	servo->angle = angle;

	if(servo->inverted)
	{
		pulse = servo->maxPulseWidth - servo->pulsePerDegree * angle - servo->pulsePerDegree * servo->offsetAngle;
	}
	else
	{
		pulse = servo->minPulseWidth + servo->pulsePerDegree * angle + servo->pulsePerDegree * servo->offsetAngle;
	}

	// Somewhat useless code segment, might remove it
	if(pulse > servo->maxPulseWidth)
	{
		pulse = servo->maxPulseWidth;
	}
	else if(pulse < servo->minPulseWidth)
	{
		pulse = servo->minPulseWidth;
	}

	__HAL_TIM_SET_COMPARE(servo->timer, servo->timerChannel, pulse);
}

void setServoAngled1(ServoHandle* servo, float angle, float speed)
{
	if(angle + servo->offsetAngle > servo->maxAngle)
	{
		servo->targetAngle = servo->maxAngle;
	}
	else if(angle + servo->offsetAngle < 0)
	{
		servo->targetAngle = 0;
	}
	else
	{
		servo->targetAngle = angle;
	}

	servo->speed = speed;

}

void setServoAngled2(ServoHandle* servoHandle, float angle, float speed, float acceleration)
{

}

bool updateServo(ServoHandle* servo, uint32_t deltaTime)
{
	if(servo->speed != 0.0)
	{
		//uint32_t deltaTime = timestamp - servo->timestamp;
		//servo->timestamp = timestamp;
		float deltaAngle = ((float)deltaTime * servo->speed) / 1000;

		//Going down
		if(servo->angle > servo->targetAngle)
		{
			if(servo->angle - deltaAngle < servo->targetAngle)
			{
				setServoAngled0(servo, servo->targetAngle);
				servo->speed = 0.0;
				return true;
			}
			else
			{
				setServoAngled0(servo, servo->angle - deltaAngle);
			}
		}
		//Going up
		else if(servo->angle < servo->targetAngle)
		{
			if(servo->angle + deltaAngle > servo->targetAngle)
			{
				setServoAngled0(servo, servo->targetAngle);
				servo->speed = 0.0;
				return true;
			}
			else
			{
				setServoAngled0(servo, servo->angle + deltaAngle);
			}
		}
	}

	return false;
}

