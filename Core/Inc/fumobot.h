/*
 * fumobot.h
 *
 *  Created on: May 5, 2026
 *      Author: club
 */

#ifndef INC_FUMOBOT_H_
#define INC_FUMOBOT_H_

// Includes
#include "servo.h"
#include "emote.h"

// Defines
#define ARM_SERVO_ANGLE_MIN 30
#define ARM_SERVO_ANGLE_MAX 150
#define BOUNCE_SERVO_ANGLE_MIN 30
#define BOUNCE_SERVO_ANGLE_MAX 120

#define SERVO_ARM_RIGHT_CHANNEL TIM_CHANNEL_2
#define SERVO_ARM_LEFT_CHANNEL TIM_CHANNEL_3
#define SERVO_BOUNCE_RIGHT_CHANNEL TIM_CHANNEL_4
#define SERVO_BOUNCE_LEFT_CHANNEL TIM_CHANNEL_1

#define SENSOR_CLOSE_THRESHOLD 1000

#define EMOTE_COOLDOWN_MS 2000
#define DELAY_TIME_MS 10


// Typedefs

typedef struct HandleStruct
{
	ADC_HandleTypeDef* sensorAdc;
	TIM_HandleTypeDef* pwmTimer;
} Handles;

void fumobot_init(void);
void fumobot_initHandles(const Handles* _handles);
void fumobot_initTimers(void);
void fumobot_init(void);
void fumobot_initUSB(void);
void fumobot_mainLoop(uint32_t deltaTime);

#endif /* INC_FUMOBOT_H_ */
