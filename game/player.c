#include "player.h"

Player *Player_New(int x,int y) {
	Player *player=malloc(sizeof(Player));
	if(player) {
		player->x=x;
		player->y=y;
		player->flip=GL2D_FLIP_NONE;
		player->baseFrame=4;
		player->frame=0;
		player->numFrames=4;
		player->state=PLAYER_STATE_IDLE;
		player->distance=0;
		player->moveDistance=64;
		player->speed=4;
		player->direction=PLAYER_DIRECTION_RIGHT;
		player->hold=false;
		player->frameDelay=4;
		player->frameDelayCount=0;
	}
	return player;	
}

void Player_Free(Player *player) {
	free(player);
	player=NULL;	
}

void Player_Draw(Player *player) {
	glSprite(player->x,player->y,player->flip,&tiles[player->baseFrame+player->frame]);
}

void Player_Update(Player *player) {
	switch(player->state) {
		case PLAYER_STATE_IDLE: Player_UpdateIdle(player); break;
		case PLAYER_STATE_MOVE_UP: Player_UpdateMoveUp(player); break;
		case PLAYER_STATE_MOVE_DOWN: Player_UpdateMoveDown(player); break;
		case PLAYER_STATE_MOVE_LEFT: Player_UpdateMoveLeft(player); break;
		case PLAYER_STATE_MOVE_RIGHT: Player_UpdateMoveRight(player); break;
		default: break;
	}
}

void Player_UpdateIdle(Player *player) {

	if(glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) {
		if(player->y>0) {
			player->baseFrame=0;
			player->numFrames=4;
			player->flip=GL2D_FLIP_NONE;
			player->distance=player->moveDistance;
		player->state=PLAYER_STATE_MOVE_UP;
		}
	} else if(glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
		if(player->y<SCREEN_HEIGHT-64) {
			player->baseFrame=0;
			player->numFrames=4;
			player->flip=GL2D_FLIP_V;
			player->distance=player->moveDistance;
			player->state=PLAYER_STATE_MOVE_DOWN;
		}
	} else if(glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
		if(player->x>0) {
			player->baseFrame=4;
			player->numFrames=4;
			player->flip=GL2D_FLIP_H;
			player->distance=player->moveDistance;
			player->state=PLAYER_STATE_MOVE_LEFT;
		}
	} else if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
		if(player->x<SCREEN_WIDTH-64) {
			player->baseFrame=4;
			player->numFrames=4;
			player->flip=GL2D_FLIP_NONE;
			player->distance=player->moveDistance;
			player->state=PLAYER_STATE_MOVE_RIGHT;
		}
	}

}

void Player_UpdateMoveUp(Player *player) {

	if(player->distance>0) { 

		if(player->distance>=player->speed) { 
			player->y-=player->speed; 
			player->distance-=player->speed; 
		} else {
			player->y-=player->distance; 		
			player->distance-=0; 
		}

		player->frameDelayCount++;
		if(player->frameDelayCount>=player->frameDelay) {
			player->frameDelayCount=0;
			player->frame=(player->frame+1)%player->numFrames;	
		}
		
	} else { 
		player->state=PLAYER_STATE_IDLE;
	}
}

void Player_UpdateMoveDown(Player *player) {

	if(player->distance>0) { 

		if(player->distance>=player->speed) { 
			player->y+=player->speed; 
			player->distance-=player->speed; 
		} else {
			player->y+=player->distance; 		
			player->distance-=0; 
		}

		player->frameDelayCount++;
		if(player->frameDelayCount>=player->frameDelay) {
			player->frameDelayCount=0;
			player->frame=(player->frame+1)%player->numFrames;	
		}

	} else { 
		player->state=PLAYER_STATE_IDLE;
	}
}

void Player_UpdateMoveLeft(Player *player) {

	if(player->distance>0) { 

		if(player->distance>=player->speed) { 
			player->x-=player->speed; 
			player->distance-=player->speed; 
		} else {
			player->x-=player->distance; 		
			player->distance-=0; 
		}

		player->frameDelayCount++;
		if(player->frameDelayCount>=player->frameDelay) {
			player->frameDelayCount=0;
			player->frame=(player->frame+1)%player->numFrames;	
		}

	} else { 
		player->state=PLAYER_STATE_IDLE;
	}
}

void Player_UpdateMoveRight(Player *player) {

	if(player->distance>0) { 

		if(player->distance>=player->speed) { 
			player->x+=player->speed; 
			player->distance-=player->speed; 
		} else {
			player->x+=player->distance; 		
			player->distance-=0; 
		}

		player->frameDelayCount++;
		if(player->frameDelayCount>=player->frameDelay) {
			player->frameDelayCount=0;
			player->frame=(player->frame+1)%player->numFrames;	
		}

	} else { 
		player->state=PLAYER_STATE_IDLE;
	}
}
