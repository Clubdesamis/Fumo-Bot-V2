/*
 * emote.h
 *
 *  Created on: Jul 1, 2026
 *      Author: club
 */

#ifndef INC_EMOTE_H_
#define INC_EMOTE_H_

#include <inttypes.h>
#include <stdbool.h>
#include "servo.h"

typedef enum
{
	STATE_STOPPED,
	STATE_PLAYING,
	STATE_WAITING,
	STATE_ERROR
} state;

typedef enum
{
	ARM_RIGHT,
	ARM_LEFT,
	BOUNCE_RIGHT,
	BOUNCE_LEFT
} servoIdentifiers;

typedef struct
{
	servoHandle** servos;
	uint8_t servoCount;
} emotePlayerCreateInfo;

typedef struct
{
	servoHandle* handle;
	int commandIndex;
	uint32_t timeToWait;
	state state;
} emoteServoContext;

typedef struct
{
	uint8_t servoCount;
	emoteServoContext* servos;
	uint32_t* currentEmote;
	uint32_t currentEmoteSize;
	state state;
} emotePlayer;

typedef enum
{
	COMMAND_HEADER = 1,
	COMMAND_START,
	COMMAND_FINISH,
	COMMAND_SET_ANGLE_D0,
	COMMAND_SET_ANGLE_D1,
	COMMAND_DELAY,
	COMMAND_BARRIER,
} commandType;

typedef uint32_t command;

#define HEADER(servoCount) (command) 0 | (uint8_t)COMMAND_HEADER << 24 | (uint8_t)servoCount << 16

#define START(servoId) (command) 0 | (uint8_t)COMMAND_START << 24 | (uint8_t)servoId << 16

#define FINISH(servoId) (command) 0 | (uint8_t)COMMAND_FINISH << 24 | (uint8_t)servoId << 16

#define SET_ANGLE_D0(servoId, angle) (command) 0 | (uint8_t)COMMAND_SET_ANGLE_D0 << 24 | (uint8_t)servoId << 16 | (uint8_t)angle << 8

#define SET_ANGLE_D1(servoId, angle, speed) (command) 0 | (uint8_t)COMMAND_SET_ANGLE_D1 << 24 | (uint8_t)servoId << 16 | (uint8_t)angle << 8 | (uint8_t)speed << 0

#define DELAY(servoId, time) (command) 0 | (uint8_t)COMMAND_DELAY << 24 | (uint8_t)servoId << 16 | (uint16_t)time << 0

#define BARRIER(servoId, barrierId) (command) 0 | (uint8_t)COMMAND_BARRIER << 24 | (uint8_t)servoId << 16 | (uint8_t)barrierId << 8

#define GET_COMMAND_ID(_command) (uint8_t)(0 | (command)_command >> 24)

#define GET_SERVO_COUNT(_command) (uint8_t)(0 | (command)_command >> 16)

#define GET_SERVO_ID(_command) (uint8_t)(0 | (command)_command >> 16)

#define GET_ANGLE(_command) (uint8_t)(0 | (command)_command >> 8)

#define GET_SPEED(_command) (uint8_t)(0 | (command)_command >> 0)

#define GET_TIME_TO_WAIT(_command) (uint16_t)(0 | (command)_command >> 0)

#define GET_BARRIER_ID(_command) (uint8_t)(0 | (command)_command >> 8)


__attribute__((unused)) static uint32_t testEmote2[] =
{
		HEADER(4),
		START(ARM_RIGHT),			START(ARM_LEFT),			START(BOUNCE_RIGHT),			START(BOUNCE_LEFT),
		SET_ANGLE_D0(ARM_RIGHT, 0),	SET_ANGLE_D0(ARM_LEFT, 0),	SET_ANGLE_D0(BOUNCE_RIGHT, 0),	SET_ANGLE_D0(BOUNCE_LEFT, 0),
		DELAY(ARM_RIGHT, 1000),		DELAY(ARM_LEFT, 1000),		DELAY(BOUNCE_RIGHT, 1000),		DELAY(BOUNCE_LEFT, 1000),
		SET_ANGLE_D0(ARM_RIGHT, 180),	SET_ANGLE_D0(ARM_LEFT, 180),	SET_ANGLE_D0(BOUNCE_RIGHT, 180),	SET_ANGLE_D0(BOUNCE_LEFT, 180),
		FINISH(ARM_RIGHT),			FINISH(ARM_LEFT),			FINISH(BOUNCE_RIGHT),			FINISH(BOUNCE_LEFT)
};

__attribute__((unused)) static uint32_t testEmote3[] =
{
		HEADER(4),
		START(ARM_RIGHT),			START(ARM_LEFT),			START(BOUNCE_RIGHT),			START(BOUNCE_LEFT),
		SET_ANGLE_D0(ARM_RIGHT, 0),	SET_ANGLE_D0(ARM_LEFT, 0),	SET_ANGLE_D0(BOUNCE_RIGHT, 0),	SET_ANGLE_D0(BOUNCE_LEFT, 0),
		DELAY(ARM_RIGHT, 1000),		DELAY(ARM_LEFT, 1000),		DELAY(BOUNCE_RIGHT, 1000),		DELAY(BOUNCE_LEFT, 1000),
		SET_ANGLE_D1(ARM_RIGHT, 180, 10),	SET_ANGLE_D1(ARM_LEFT, 180, 10),	SET_ANGLE_D1(BOUNCE_RIGHT, 180, 10),	SET_ANGLE_D1(BOUNCE_LEFT, 180, 10),
		SET_ANGLE_D0(ARM_RIGHT, 0),	SET_ANGLE_D0(ARM_LEFT, 0),	SET_ANGLE_D0(BOUNCE_RIGHT, 0),	SET_ANGLE_D0(BOUNCE_LEFT, 0),
		FINISH(ARM_RIGHT),			FINISH(ARM_LEFT),			FINISH(BOUNCE_RIGHT),			FINISH(BOUNCE_LEFT)
};

__attribute__((unused)) static uint32_t testEmote[] =
{
		HEADER(4),
		START(ARM_RIGHT),			START(ARM_LEFT),			START(BOUNCE_RIGHT),			START(BOUNCE_LEFT),
		SET_ANGLE_D0(ARM_RIGHT, 0),	SET_ANGLE_D0(ARM_LEFT, 0),	SET_ANGLE_D0(BOUNCE_RIGHT, 0),	SET_ANGLE_D0(BOUNCE_LEFT, 0),
		DELAY(ARM_RIGHT, 500),		DELAY(ARM_LEFT, 500),		DELAY(BOUNCE_RIGHT, 500),		DELAY(BOUNCE_LEFT, 500),
		SET_ANGLE_D0(ARM_RIGHT, 180),	SET_ANGLE_D0(ARM_LEFT, 180),	SET_ANGLE_D0(BOUNCE_RIGHT, 180),	SET_ANGLE_D0(BOUNCE_LEFT, 180),
		DELAY(ARM_RIGHT, 350),
		SET_ANGLE_D1(ARM_RIGHT, 0, 30),
		DELAY(ARM_RIGHT, 350),
		SET_ANGLE_D1(ARM_RIGHT, 180, 30),
		BARRIER(ARM_RIGHT, 0),		BARRIER(ARM_LEFT, 0),		BARRIER(BOUNCE_RIGHT, 0),			BARRIER(BOUNCE_LEFT, 0),
		DELAY(ARM_LEFT, 350),
		SET_ANGLE_D1(ARM_LEFT, 0, 30),
		DELAY(ARM_LEFT, 350),
		SET_ANGLE_D1(ARM_LEFT, 180, 30),
		BARRIER(ARM_RIGHT, 1),		BARRIER(ARM_LEFT, 1),		BARRIER(BOUNCE_RIGHT, 1),			BARRIER(BOUNCE_LEFT, 1),
		SET_ANGLE_D0(ARM_RIGHT, 90),	SET_ANGLE_D0(ARM_LEFT, 90),	SET_ANGLE_D0(BOUNCE_RIGHT, 90),	SET_ANGLE_D0(BOUNCE_LEFT, 90),
		FINISH(ARM_RIGHT),			FINISH(ARM_LEFT),			FINISH(BOUNCE_RIGHT),			FINISH(BOUNCE_LEFT)
};



//static int e = sizeof(testEmote);

emotePlayer* emote_initPlayer(emotePlayerCreateInfo* createInfo);
void emote_destroyPlayer(emotePlayer* player);
bool emote_start(emotePlayer* player, uint32_t* emote, uint32_t emoteSize);
bool emote_update(emotePlayer* player, uint32_t deltaTime);
void emote_finish(emotePlayer* player);

#endif /* INC_EMOTE_H_ */
