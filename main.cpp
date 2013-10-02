#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "Game.hpp"

#define SDL_FLAGS     SDL_INIT_VIDEO

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP    16
#define SCREEN_FLAGS  SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE | SDL_HWSURFACE

SDL_Surface *screen;
bool running = false;
Game *game;

bool init() {
	if ( SDL_Init( SDL_FLAGS ) < 0 ) {
		printf( "Unable to init SDL: %s\n", SDL_GetError() );
		return true;
	} else printf( "Initializing SDL\n");

    atexit(SDL_Quit);

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SCREEN_FLAGS);
    if ( !screen ) {
		printf("Unable to set 640x480 video: %s\n", SDL_GetError());
		return true;
	} else printf( "Initializing screen\n");

    glShadeModel( GL_SMOOTH );

    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    glClearDepth( 1.0f );

    glEnable( GL_DEPTH_TEST );

    glDepthFunc( GL_LEQUAL );

    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    GLfloat ratio = ( GLfloat )SCREEN_WIDTH / ( GLfloat )SCREEN_HEIGHT;
    glViewport( 0, 0, ( GLsizei )SCREEN_WIDTH, ( GLsizei )SCREEN_HEIGHT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    gluPerspective( 45.0f, ratio, 0.1f, 200.0f );

    glMatrixMode( GL_MODELVIEW );

    glLoadIdentity( );

	GLenum glError = glGetError();
    if( glError != GL_NO_ERROR ) {
        printf("Error initializing OpenGL! %s\n", gluErrorString(glError));
        return true;
    } else printf("OpenGL initialized\n");

	running = true;
	return false;
}

void events() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT: running = false; break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_ESCAPE:
						running = false;
						break;
					case SDLK_SPACE:
						game->reset();
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

int main ( int argc, char** argv ) {
	if (init()) {
		printf("Terminating..");
		return EXIT_FAILURE;
	}

	game = new Game(32, 32, 32);

    while (running) {
		events();

		game->update();
		game->draw();

		SDL_GL_SwapBuffers();
    }

    printf("Exited cleanly\n");
	return EXIT_SUCCESS;
}
