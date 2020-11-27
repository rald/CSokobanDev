#include <GL/glfw.h>
#include <GL/gl2d.h>

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "common.h"
#include "player.h"

#include "uvcoord_tiles.h"

glImage tiles[TILES_NUM_IMAGES];

int main(int argc, char *argv[]) {

	bool quit=false;
	double timeStart;
	
	GLuint tileTexture;
	
	Player *player=NULL;
	
			
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
					
	player=Player_New(0,0);					
					
	while(!quit) {
	
		glClearScreen();
		
		Player_Draw(player);
		
		Player_Update(player);
			
		timeStart = glfwGetTime();
		while(glfwGetTime()-timeStart < 1.0/60.0) {};
				
		glfwSwapBuffers();

		quit = glfwGetKey(GLFW_KEY_ESC) | !glfwGetWindowParam(GLFW_OPENED);
	}

	glDeleteTextures(1,&tileTexture);

	glfwTerminate();

	return 0;
}
