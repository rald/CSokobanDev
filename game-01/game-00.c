#include <GL/glfw.h>
#include <GL/gl2d.h>

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define GAME_TITLE "CSokoban"

#define TILE_WIDTH_MAX 32
#define TILE_HEIGHT_MAX 32

#define BOARD_WIDTH_MAX 20
#define BOARD_HEIGHT_MAX 20

#define SCREEN_WIDTH (TILE_WIDTH_MAX*BOARD_WIDTH_MAX)
#define SCREEN_HEIGHT (TILE_HEIGHT_MAX*BOARD_HEIGHT_MAX)

typedef enum TileType TileType;
 
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

double sgn(double x) {
	return x<0?-1:x>0?1:0;
}

int main(int argc, char *argv[]) {

	glImage tileImages[TILE_TYPE_MAX];
	GLuint tileTextures[TILE_TYPE_MAX];

	TileType board[BOARD_WIDTH_MAX][BOARD_HEIGHT_MAX];
	int boardWidth=20,boardHeight=20;

	double timeStart=0;
	bool quit=false;
	int i,j;
	double x=0,y=0;
	double dx=x,dy=y;

	srand(time(NULL));

	glScreenInit(SCREEN_WIDTH,SCREEN_HEIGHT);

	glfwSetWindowTitle(GAME_TITLE);

	glfwSwapInterval(1);

	glBlendMode(GL2D_ALPHA);

	tileTextures[TILE_TYPE_NONE]=glLoadSprite("images/none.tga",&tileImages[TILE_TYPE_NONE],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_FLOOR]=glLoadSprite("images/floor.tga",&tileImages[TILE_TYPE_FLOOR],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_PLAYER]=glLoadSprite("images/player.tga",&tileImages[TILE_TYPE_PLAYER],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_PLAYER_ON_GOAL]=glLoadSprite("images/player_on_goal.tga",&tileImages[TILE_TYPE_PLAYER_ON_GOAL],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_BOX]=glLoadSprite("images/box.tga",&tileImages[TILE_TYPE_BOX],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_BOX_ON_GOAL]=glLoadSprite("images/box_on_goal.tga",&tileImages[TILE_TYPE_BOX_ON_GOAL],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_GOAL]=glLoadSprite("images/goal.tga",&tileImages[TILE_TYPE_GOAL],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_WALL]=glLoadSprite("images/wall.tga",&tileImages[TILE_TYPE_WALL],32,32,GL_NEAREST);

	for(j=0;j<boardHeight;j++) {
		for(i=0;i<boardWidth;i++) {
			board[j][i]=rand()%(TILE_TYPE_MAX-3)+3;
		}
	}
		
	while(!quit) {

		glClearScreen();
	
		for(j=0;j<boardHeight;j++) {
			for(i=0;i<boardWidth;i++) {
				glSprite(i*32,j*32,GL2D_FLIP_NONE,&tileImages[TILE_TYPE_FLOOR]);
				glSprite(i*32,j*32,GL2D_FLIP_NONE,&tileImages[board[j][i]]);
			}			
		}			

		glSprite(x,y,GL2D_FLIP_NONE,&tileImages[TILE_TYPE_PLAYER]);	
	
		if(x==dx && y==dy) {
			if(glfwGetKey(GLFW_KEY_UP)         == GLFW_PRESS) { if(dy-32>=0)            dy-=32; }	
			else if(glfwGetKey(GLFW_KEY_DOWN)  == GLFW_PRESS) { if(dy+32<SCREEN_HEIGHT) dy+=32; }	
			else if(glfwGetKey(GLFW_KEY_LEFT)  == GLFW_PRESS) { if(dx-32>=0)            dx-=32; }	
			else if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) { if(dx+32<SCREEN_WIDTH)  dx+=32; }	
		} else {
			if(fabs(dx-x)>=1) x+=(dx-x)/3; else x=dx;
			if(fabs(dy-y)>=1) y+=(dy-y)/3; else y=dy;
		}
		
		glfwSwapBuffers();

		timeStart = glfwGetTime();
		while(glfwGetTime()-timeStart < 1.0/60.0) {};

		quit = glfwGetKey(GLFW_KEY_ESC) | !glfwGetWindowParam(GLFW_OPENED);

	}

	glfwTerminate();

	return 0;
}
