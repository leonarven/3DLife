#ifndef GAME_HPP
#define GAME_HPP

#include "Map.hpp"
#include "Life.hpp"
#include "Cell.hpp"

class Game{
private:
	Map  *map;
	int  updates;
	Life life;
public:
	Game(int w, int h, int d) : map(new Map(w, h, d)), life(Life()) {
		updates = 0;
		printf("Game constructed\n");
	}
	void update() {
		this->updates++;
		this->life.update(map);
	}
	void draw() {

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glLoadIdentity();
		glTranslatef(-32, -32, -150);
		glRotatef(this->updates * 0.1, 1, 1, 1);

		this->map->draw();

		SDL_GL_SwapBuffers();
	}
	void reset() {
		this->map->randomize();
	}
};

#endif
