#ifndef GAME_HPP
#define GAME_HPP

#include "Map.hpp"
#include "Life.hpp"
#include "Cell.hpp"

struct View {
	double k = 64.0;
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
};

class Game{
private:
	Map  *map;
	int  updates;
	Life life;
public:
	View view;

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
		glTranslatef(-8, -8, -80);

		if (rules::followMouse) {
			glRotatef(this->view.x*this->view.k, 1, 0, 0);
			glRotatef(this->view.y*this->view.k, 0, 1, 0);
		}

		glTranslatef(-8, -8, -16);

		this->map->draw();
	}
	void reset() {
		this->map->randomize();
	}
};

#endif
