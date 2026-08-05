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

// Typedefs

typedef struct HandleStruct
{
	TIM_HandleTypeDef* pwmTimer;
} Handles;

void fumobot_init(void);
void fumobot_initHandles(const Handles* _handles);
void fumobot_initTimers(void);
void fumobot_init(void);
void fumobot_initUSB(void);
void fumobot_mainLoop(void);

#endif /* INC_FUMOBOT_H_ */
