#include <GL/glfw.h>
#include <GL/gl2d.h>

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define GAME_TITLE "CSokoban"

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

#define BOARD_WIDTH_MAX 20
#define BOARD_HEIGHT_MAX 20

#define SCREEN_WIDTH (TILE_WIDTH*BOARD_WIDTH_MAX)
#define SCREEN_HEIGHT (TILE_HEIGHT*BOARD_HEIGHT_MAX)

typedef enum TileType TileType;
typedef enum Direction Direction;
 
enum TileType {
	TILE_TYPE_NONE=0,	
	TILE_TYPE_PLAYER,
	TILE_TYPE_PLAYER_ON_GOAL,		
	TILE_TYPE_FLOOR,
	TILE_TYPE_BOX,
	TILE_TYPE_BOX_ON_GOAL,
	TILE_TYPE_GOAL,
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

	glImage tileImages[TILE_TYPE_MAX];
	GLuint tileTextures[TILE_TYPE_MAX];

	TileType board[BOARD_WIDTH_MAX][BOARD_HEIGHT_MAX];
	int boardWidth=20,boardHeight=20;

	bool quit=false;
	double timeStart;
	int i,j;
	double x=0,y=0;
	double dx=x,dy=y;
	double speed=32;
	Direction direction=DIRECTION_NONE;

	srand(time(NULL));

	glScreenInit(SCREEN_WIDTH,SCREEN_HEIGHT);
	glfwSetWindowTitle(GAME_TITLE);
	glfwSwapInterval(1);
	glBlendMode(GL2D_SOLID);

	tileTextures[TILE_TYPE_NONE]		=	glLoadSprite("images/none.tga",&tileImages[TILE_TYPE_NONE],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_FLOOR]		=	glLoadSprite("images/floor.tga",&tileImages[TILE_TYPE_FLOOR],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_PLAYER]		=	glLoadSprite("images/player.tga",&tileImages[TILE_TYPE_PLAYER],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_PLAYER_ON_GOAL]	=	glLoadSprite("images/player_on_goal.tga",&tileImages[TILE_TYPE_PLAYER_ON_GOAL],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_BOX]		=	glLoadSprite("images/box.tga",&tileImages[TILE_TYPE_BOX],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_BOX_ON_GOAL]	=	glLoadSprite("images/box_on_goal.tga",&tileImages[TILE_TYPE_BOX_ON_GOAL],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_GOAL]		=	glLoadSprite("images/goal.tga",&tileImages[TILE_TYPE_GOAL],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_WALL]		=	glLoadSprite("images/wall.tga",&tileImages[TILE_TYPE_WALL],32,32,GL_NEAREST);

	while(!quit) {
		glClearScreen();
	
		glSprite(x,y,GL2D_FLIP_NONE,&tileImages[TILE_TYPE_PLAYER]);	

		if(direction==DIRECTION_NONE) {
			if(glfwGetKey(GLFW_KEY_UP)         == GLFW_PRESS) { if(y-speed>=0)                         { dy=y-speed; direction=DIRECTION_UP;    } }
			else if(glfwGetKey(GLFW_KEY_DOWN)  == GLFW_PRESS) { if(y+speed<=SCREEN_HEIGHT-TILE_HEIGHT) { dy=y+speed; direction=DIRECTION_DOWN;  } }
			else if(glfwGetKey(GLFW_KEY_LEFT)  == GLFW_PRESS) { if(x-speed>=0)                         { dx=x-speed; direction=DIRECTION_LEFT;  } }
			else if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) { if(x+speed<=SCREEN_WIDTH-TILE_WIDTH)   { dx=x+speed; direction=DIRECTION_RIGHT; } }
		} else {
			if(fabs(dx-x)>=4) x+=sgn(dx-x)*4; else x=dx;
			if(fabs(dy-y)>=4) y+=sgn(dy-y)*4; else y=dy;
			if(x==dx && y==dy) direction=DIRECTION_NONE;
		}

		timeStart = glfwGetTime();
		while(glfwGetTime()-timeStart < 1.0/60.0) {};
				
		glfwSwapBuffers();

		quit = glfwGetKey(GLFW_KEY_ESC) | !glfwGetWindowParam(GLFW_OPENED);
	}

	glDeleteTextures(TILE_TYPE_MAX,tileTextures);

	glfwTerminate();

	return 0;
}
