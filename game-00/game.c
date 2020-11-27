#include <GL/glfw.h>
#include <GL/gl2d.h>

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define GAME_TITLE "Sokoban"

#define SCREEN_WIDTH 32*16
#define SCREEN_HEIGHT 32*16

typedef enum TileType TileType;
 
enum TileType {
	TILE_TYPE_NONE=0,	
	TILE_TYPE_FLOOR,
	TILE_TYPE_PLAYER,
	TILE_TYPE_PLAYER_ON_MARK,		
	TILE_TYPE_BOX,
	TILE_TYPE_BOX_ON_MARK,
	TILE_TYPE_MARK,
	TILE_TYPE_WALL,
	TILE_TYPE_MAX
};

int main(int argc, char *argv[]) {

	glImage tileImages[TILE_TYPE_MAX];
	GLuint tileTextures[TILE_TYPE_MAX];
	TileType board[16][16];

	double timeStart=0;
	bool quit=false;
	int i,j;

	srand(time(NULL));

	glScreenInit(SCREEN_WIDTH,SCREEN_HEIGHT);

	glfwSetWindowTitle(GAME_TITLE);

	glfwSwapInterval(1);

	glBlendMode(GL2D_ALPHA);

	tileTextures[TILE_TYPE_NONE]=glLoadSprite("images/none.tga",&tileImages[TILE_TYPE_NONE],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_FLOOR]=glLoadSprite("images/floor.tga",&tileImages[TILE_TYPE_FLOOR],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_PLAYER]=glLoadSprite("images/player.tga",&tileImages[TILE_TYPE_PLAYER],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_PLAYER_ON_MARK]=glLoadSprite("images/player_on_mark.tga",&tileImages[TILE_TYPE_PLAYER_ON_MARK],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_BOX]=glLoadSprite("images/box.tga",&tileImages[TILE_TYPE_BOX],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_BOX_ON_MARK]=glLoadSprite("images/box_on_mark.tga",&tileImages[TILE_TYPE_BOX_ON_MARK],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_MARK]=glLoadSprite("images/mark.tga",&tileImages[TILE_TYPE_MARK],32,32,GL_NEAREST);
	tileTextures[TILE_TYPE_WALL]=glLoadSprite("images/wall.tga",&tileImages[TILE_TYPE_WALL],32,32,GL_NEAREST);

	glClearScreen();
	
	for(j=0;j<16;j++) {
		for(i=0;i<16;i++) {
			board[j][i]=rand()%TILE_TYPE_MAX;
		}
	}

	for(j=0;j<16;j++) {
		for(i=0;i<16;i++) {
			glSprite(i*32,j*32,GL2D_FLIP_NONE,&tileImages[TILE_TYPE_FLOOR]);
			glSprite(i*32,j*32,GL2D_FLIP_NONE,&tileImages[board[j][i]]);	
		}
	}

	while(!quit) {
	
		glfwSwapBuffers();

		timeStart = glfwGetTime();
		while(glfwGetTime()-timeStart < 1.0/60.0) {};

		quit = glfwGetKey(GLFW_KEY_ESC) | !glfwGetWindowParam(GLFW_OPENED);

	}

	glfwTerminate();

	return 0;
}
