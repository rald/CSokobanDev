#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"

typedef struct Player Player;
typedef enum PlayerState PlayerState;
typedef enum PlayerDirection PlayerDirection;

enum PlayerState {
	PLAYER_STATE_IDLE=0,
	PLAYER_STATE_MOVE_UP,
	PLAYER_STATE_MOVE_DOWN,
	PLAYER_STATE_MOVE_LEFT,
	PLAYER_STATE_MOVE_RIGHT,
	PLAYER_STATE_MAX		
};

enum PlayerDirection {
	PLAYER_DIRECTION_UP=0,
	PLAYER_DIRECTION_DOWN,
	PLAYER_DIRECTION_LEFT,
	PLAYER_DIRECTION_RIGHT,
	PLAYER_DIRECTION_MAX
};

struct Player {
	int x,y;
	GL2D_FLIP_MODE flip;
	int baseFrame;
	int frame;
	int numFrames;
	int distance;
	int moveDistance;
	int speed;
	bool hold;
	int frameDelay;
	int frameDelayCount;
	PlayerDirection direction;
	PlayerState state;
};

Player *Player_New(int x,int y);
void Player_Free(Player *player);
void Player_Draw(Player *player);
void Player_Update(Player *player);

void Player_UpdateIdle(Player *player);
void Player_UpdateMoveUp(Player *player);
void Player_UpdateMoveDown(Player *player);
void Player_UpdateMoveLeft(Player *player);
void Player_UpdateMoveRight(Player *player);

#endif