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
	STATE_ERROR
} emotePlayerState;

typedef struct
{
	servoHandle** servos;
	uint8_t servoCount;
} emotePlayerCreateInfo;

typedef struct
{
	uint8_t servoCount;
	servoHandle** servos;
	uint32_t* currentEmote;
	emotePlayerState state;
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

#define SET_ANGLE_D1(servoId, angle, speed) (command) 0 | (uint8_t)COMMAND_SET_ANGLE_D1 << 24 | (uint8_t)servoId << 16 | (uint8_t)angle << 8 | (uint8_t)speed

#define DELAY(servoId, time) (command) 0 | (uint8_t)COMMAND_DELAY << 24 | (uint8_t)servoId << 16 | (uint16_t)time << 8

#define BARRIER(servoId, barrierId) (command) 0 | (uint8_t)COMMAND_BARRIER << 24 | (uint8_t)servoId << 16

#define GET_COMMAND_ID(command) (uint8_t) 0 | (command)command >> 24

#define GET_SERVO_COUNT(command) (uint8_t) 0 | (command)command >> 16

#define GET_SERVO_ID(command) (uint8_t) 0 | (command)command >> 16

#define GET_ANGLE(command) (uint8_t) 0 | (command)command >> 8


__attribute__((unused)) static int testEmote[] =
{
		HEADER(4),
		START(1),			START(2),			START(3),			START(4),
		SET_ANGLE_D0(1, 0),	SET_ANGLE_D0(2, 0),	SET_ANGLE_D0(3, 0),	SET_ANGLE_D0(4, 0),
		DELAY(1, 1000),		DELAY(2, 1000),		DELAY(3, 1000),		DELAY(4, 1000),
		FINISH(1),			FINISH(2),			FINISH(3),			FINISH(4)
};

emotePlayer* emote_initPlayer(emotePlayerCreateInfo createInfo);
void emote_start(emotePlayer* player, uint32_t* emote);
bool emote_update(emotePlayer* player);
void emote_finish(emotePlayer* player);

#endif /* INC_EMOTE_H_ */
