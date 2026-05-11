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

// Defines

// Typedefs

typedef struct HandleStruct
{
	TIM_HandleTypeDef* pwmTimer;
} Handles;

void fumoBotInit();
void initHandles(const Handles* _handles);
void initTimers();
void initServos();
void initUSB();
void mainLoop(void);

#endif /* INC_FUMOBOT_H_ */
