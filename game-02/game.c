#include <GL/glfw.h>
#include <GL/gl2d.h>

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "uvcoord_tiles.h"

#define GAME_TITLE "CSokoban"

#define TILE_WIDTH 64
#define TILE_HEIGHT 64

#define BOARD_WIDTH_MAX 10
#define BOARD_HEIGHT_MAX 10

#define SCREEN_WIDTH (TILE_WIDTH*BOARD_WIDTH_MAX)
#define SCREEN_HEIGHT (TILE_HEIGHT*BOARD_HEIGHT_MAX)

typedef enum TileType TileType;
typedef enum Direction Direction;
 
enum TileType {
	TILE_TYPE_FLOOR=8,
	TILE_TYPE_GOAL,
	TILE_TYPE_BOX,
	TILE_TYPE_BOX_ON_GOAL,
	TILE_TYPE_WALL,
	TILE_TYPE_MAX
};

enum Direction {
	DIRECTION_NONE=0,
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_MAX
};

double sgn(double x) {
	return x<0?-1:x>0?1:0;
}

int main(int argc, char *argv[]) {

	bool quit=false;
	double timeStart;
	int i,j;
	double x=0,y=0;
	double dx=x,dy=y;
	double speed=64;
	Direction direction=DIRECTION_NONE;
	
	glImage tiles[TILES_NUM_IMAGES];
	GLuint tileTexture;
	
	GL2D_FLIP_MODE flip=GL2D_FLIP_NONE;
	int baseFrame=0;
	int frame=0;
	int numFrames=4;
	int frameDelay=3;
	int frameDelayCounter=0;
	
	TileType board[BOARD_HEIGHT_MAX][BOARD_WIDTH_MAX];
	int boardWidth=BOARD_WIDTH_MAX,boardHeight=BOARD_HEIGHT_MAX;	
	
	srand(time(NULL));

	glScreenInit(SCREEN_WIDTH,SCREEN_HEIGHT);
	glfwSetWindowTitle(GAME_TITLE);
	glfwSwapInterval(1);
	glBlendMode(GL2D_ALPHA);

	tileTexture = glLoadSpriteSet	(	"images/sokoban.tga",
						tiles,
						TILES_BITMAP_WIDTH,
						TILES_BITMAP_HEIGHT,
						TILES_NUM_IMAGES,
						tiles_texcoords,
						GL_NEAREST
					);
					
	for(j=0;j<boardWidth;j++) {
		for(i=0;i<boardWidth;i++) {
			board[j][i]=rand()%(TILE_TYPE_MAX-8)+8;
		}
	}

	while(!quit) {
		glClearScreen();
		
		for(j=0;j<boardWidth;j++) {
			for(i=0;i<boardWidth;i++) {
				glSprite(i*TILE_WIDTH,j*TILE_HEIGHT,GL2D_FLIP_NONE,&tiles[board[j][i]]);				
			}
		}
		
	
		glSprite(x,y,flip,&tiles[baseFrame+frame]);

		if(direction==DIRECTION_NONE) {
			if(glfwGetKey(GLFW_KEY_UP)         == GLFW_PRESS) { if(y-speed>=0)                         { dy=y-speed; direction=DIRECTION_UP;    baseFrame=0; numFrames=4; flip=GL2D_FLIP_NONE; } }
			else if(glfwGetKey(GLFW_KEY_DOWN)  == GLFW_PRESS) { if(y+speed<=SCREEN_HEIGHT-TILE_HEIGHT) { dy=y+speed; direction=DIRECTION_DOWN;  baseFrame=0; numFrames=4; flip=GL2D_FLIP_V;    } }
			else if(glfwGetKey(GLFW_KEY_LEFT)  == GLFW_PRESS) { if(x-speed>=0)                         { dx=x-speed; direction=DIRECTION_LEFT;  baseFrame=4; numFrames=4; flip=GL2D_FLIP_H;    } }
			else if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) { if(x+speed<=SCREEN_WIDTH-TILE_WIDTH)   { dx=x+speed; direction=DIRECTION_RIGHT; baseFrame=4; numFrames=4; flip=GL2D_FLIP_NONE; } }
		} else {

			frameDelayCounter++;
			if(frameDelayCounter>=frameDelay) {
				frameDelayCounter=0;
				frame=(frame+1)%numFrames;
			}
		
			if(fabs(dx-x)>=4) x+=sgn(dx-x)*4; else x=dx;
			if(fabs(dy-y)>=4) y+=sgn(dy-y)*4; else y=dy;
			if(x==dx && y==dy) { direction=DIRECTION_NONE; }
		}

		timeStart = glfwGetTime();
		while(glfwGetTime()-timeStart < 1.0/60.0) {};
				
		glfwSwapBuffers();

		quit = glfwGetKey(GLFW_KEY_ESC) | !glfwGetWindowParam(GLFW_OPENED);
	}

	glDeleteTextures(1,tileTexture);

	glfwTerminate();

	return 0;
}
