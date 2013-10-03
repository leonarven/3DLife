#ifndef GAME_HPP
#define GAME_HPP

#include "Map.hpp"
#include "Life.hpp"
#include "Cell.hpp"

struct View {
	double mk = 85.0;
	double mx = 0.0;
	double my = 0.0;
	double mz = 0.0;

	double k = 5.0;
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
};

struct Pointer {
	int x = 0,
		y = 0,
		z = 0;
	float color[3] = { 1.0f, 1.0f, 0.0f };
};

class Game{
private:
	int  updates;
	Life life;
public:
	Map  *map;
	Pointer pointer;
	View view;
	bool updating;

	Game(int w, int h, int d) : life(Life()), map(new Map(w, h, d)) {
		updates = 0;
		updating = true;
		printf("Game constructed\n");
	}
	void update() {
		if (this->updating) {
			this->updates++;
			this->life.update(map);
		}
	}
	void draw() {

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glLoadIdentity();
		glTranslatef(-8, -8, -80);

		if (rules::followMouse) {
			glRotatef(this->view.mx*this->view.mk, 1, 0, 0);
			glRotatef(this->view.my*this->view.mk, 0, 1, 0);
		}

		glRotatef(this->view.x*this->view.k, 1, 0, 0);
		glRotatef(this->view.y*this->view.k, 0, 1, 0);
		glRotatef(this->view.z*this->view.k, 0, 0, 1);

		glTranslatef(-8, -8, -16);

		float s = 0.5f;
		float  r = 1.0f;

		this->map->draw(s, r, this->updating);

		if (!this->updating) {
			glColor3fv(pointer.color);
			glBegin( GL_QUADS );
				glVertex3f(r * this->pointer.x-s,r * this->pointer.y-s,r * this->pointer.z-s); glVertex3f(r * this->pointer.x+s,r * this->pointer.y-s,r * this->pointer.z-s); glVertex3f(r * this->pointer.x+s,r * this->pointer.y+s,r * this->pointer.z-s); glVertex3f(r * this->pointer.x-s,r * this->pointer.y+s,r * this->pointer.z-s);
				glVertex3f(r * this->pointer.x-s,r * this->pointer.y-s,r * this->pointer.z-s); glVertex3f(r * this->pointer.x-s,r * this->pointer.y-s,r * this->pointer.z+s); glVertex3f(r * this->pointer.x-s,r * this->pointer.y+s,r * this->pointer.z+s); glVertex3f(r * this->pointer.x-s,r * this->pointer.y+s,r * this->pointer.z-s);
				glVertex3f(r * this->pointer.x+s,r * this->pointer.y-s,r * this->pointer.z+s); glVertex3f(r * this->pointer.x+s,r * this->pointer.y-s,r * this->pointer.z-s); glVertex3f(r * this->pointer.x+s,r * this->pointer.y+s,r * this->pointer.z-s); glVertex3f(r * this->pointer.x+s,r * this->pointer.y+s,r * this->pointer.z+s);
				glVertex3f(r * this->pointer.x-s,r * this->pointer.y-s,r * this->pointer.z-s); glVertex3f(r * this->pointer.x+s,r * this->pointer.y-s,r * this->pointer.z-s); glVertex3f(r * this->pointer.x+s,r * this->pointer.y-s,r * this->pointer.z+s); glVertex3f(r * this->pointer.x-s,r * this->pointer.y-s,r * this->pointer.z+s);
				glVertex3f(r * this->pointer.x-s,r * this->pointer.y-s,r * this->pointer.z+s); glVertex3f(r * this->pointer.x+s,r * this->pointer.y-s,r * this->pointer.z+s); glVertex3f(r * this->pointer.x+s,r * this->pointer.y+s,r * this->pointer.z+s); glVertex3f(r * this->pointer.x-s,r * this->pointer.y+s,r * this->pointer.z+s);
				glVertex3f(r * this->pointer.x-s,r * this->pointer.y+s,r * this->pointer.z+s); glVertex3f(r * this->pointer.x-s,r * this->pointer.y+s,r * this->pointer.z-s); glVertex3f(r * this->pointer.x+s,r * this->pointer.y+s,r * this->pointer.z-s); glVertex3f(r * this->pointer.x+s,r * this->pointer.y+s,r * this->pointer.z+s);
			glEnd();
		}
	}
};

#endif
