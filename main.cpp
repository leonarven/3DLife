#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "Game.hpp"
#include "Rules.hpp"

#define SDL_FLAGS     SDL_INIT_VIDEO

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define SCREEN_BPP    16
#define SCREEN_FLAGS  SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE | SDL_HWSURFACE

SDL_Surface *screen;
bool running  = false;
bool updating = true;
Game *game;

GLenum initGL() {
    glShadeModel( GL_SMOOTH );

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 200.0f);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    return glGetError();
}

bool init() {
	if ( SDL_Init( SDL_FLAGS ) < 0 ) {
		printf( "Unable to init SDL: %s\n", SDL_GetError() );
		return true;
	} else printf( "Initializing SDL\n");

    atexit(SDL_Quit);

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SCREEN_FLAGS);
    if ( !screen ) {
		printf("Unable to set %dx%d video: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		return true;
	} else printf( "Initializing screen\n");

	SDL_ShowCursor( 0 );

	GLenum glError = initGL();
    if( glError != GL_NO_ERROR ) {
        printf("Error initializing OpenGL! %s\n", gluErrorString(glError));
        return true;
    } else printf("OpenGL initialized\n");

    SDL_ShowCursor( 0 );

	running = true;
	return false;
}

void handleEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT: running = false; break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_ESCAPE:
						running = false;
						break;
					case SDLK_RETURN:
						updating = !updating;
						break;
					case SDLK_SPACE:
						game->reset();
						break;
					case SDLK_l:
						rules::loopMap = !rules::loopMap;
						break;
					default:
						break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch(event.button.button) {
					case SDL_BUTTON_LEFT:
						rules::followMouse = !rules::followMouse;
						SDL_ShowCursor( (int)(!rules::followMouse) );
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
}

void help() {
	printf("----------\n");
	printf("Näppäimet:\n");
	printf("    esc       Sammuttaa ohjelman\n");
	printf("    space     Alustaa kartan satunnaiseksi\n");
	printf("    return    Pause ON/OFF\n");
	printf("    l         Togglettaa kartan reunojen peilautuvuuden\n");
	printf("----------\n");
}

int main ( int argc, char** argv ) {
	if (init()) {
		printf("Terminating..");
		return EXIT_FAILURE;
	}

	game = new Game(32, 32, 32);

	help();

    while (running) {
		handleEvents();

		int mX, mY;
		SDL_GetMouseState(&mX, &mY);

		game->view.y = 2.0 * mX/(double)SCREEN_WIDTH  - 1.0;
		game->view.x = 2.0 * mY/(double)SCREEN_HEIGHT - 1.0;

		if (updating) game->update();
		game->draw();

		SDL_GL_SwapBuffers();
    }

    printf("Exited cleanly\n");
	return EXIT_SUCCESS;
}
