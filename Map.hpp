#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include "Rules.hpp"
#include "Cell.hpp"

using namespace std;

void drawCube(double x, double y, double z, double s) {
	glBegin( GL_QUADS );
		glVertex3f(x-s,y-s,z-s);
		glVertex3f(x+s,y-s,z-s);
		glVertex3f(x+s,y+s,z-s);
		glVertex3f(x-s,y+s,z-s);

		glVertex3f(x-s,y-s,z-s);
		glVertex3f(x-s,y-s,z+s);
		glVertex3f(x-s,y+s,z+s);
		glVertex3f(x-s,y+s,z-s);

		glVertex3f(x+s,y-s,z+s);
		glVertex3f(x+s,y-s,z-s);
		glVertex3f(x+s,y+s,z-s);
		glVertex3f(x+s,y+s,z+s);

		glVertex3f(x-s,y-s,z-s);
		glVertex3f(x+s,y-s,z-s);
		glVertex3f(x+s,y-s,z+s);
		glVertex3f(x-s,y-s,z+s);

		glVertex3f(x-s,y-s,z+s);
		glVertex3f(x+s,y-s,z+s);
		glVertex3f(x+s,y+s,z+s);
		glVertex3f(x-s,y+s,z+s);

		glVertex3f(x-s,y+s,z+s);
		glVertex3f(x-s,y+s,z-s);
		glVertex3f(x+s,y+s,z-s);
		glVertex3f(x+s,y+s,z+s);
	glEnd();


}

class Map {
private:
	int width;
	int height;
	int depth;
	std::vector<std::vector<std::vector<Cell> > > map;
public:
	Map(Map *tmap) : width(tmap->getWidth()), height(tmap->getHeight()), depth(tmap->getDepth()) {
		for(int z = 0; z < depth;  z++) {
			std::vector<std::vector<Cell> > tmpz;
			for(int y = 0; y < height; y++) {
				std::vector<Cell> tmpy;
				for(int x = 0; x < width;  x++) {
					tmpy.push_back(Cell(tmap->getLife(x, y, z)));
				}
				tmpz.push_back(tmpy);
			}
			map.push_back(tmpz);
		}
	}
	Map(int w, int h, int d) : width(w), height(h), depth(d) {
		if (!( w > 0 && h > 0 && d > 0)) {
			printf("Invalid dimension\n");
			return;
		}

		printf("Map constructed\n");

		for(int z = 0; z < depth;  z++) {
			std::vector<std::vector<Cell> > tmpz;
			for(int y = 0; y < height; y++) {
				std::vector<Cell> tmpy;
				for(int x = 0; x < width;  x++) tmpy.push_back(Cell(false));
				tmpz.push_back(tmpy);
			}
			map.push_back(tmpz);
		}

		this->randomize();
		printf("Map initialized\n");
	}
	void randomize() {
		for(int z = 0; z < this->depth;  z++)
			for(int y = 0; y < this->height; y++)
				for(int x = 0; x < this->width;  x++)
					this->map[z][y][x].set(rand() % 2);
	}
	void fill(bool life) {
		for(int z = 0; z < this->depth;  z++)
			for(int y = 0; y < this->height; y++)
				for(int x = 0; x < this->width;  x++)
					this->map[z][y][x].set(life);
	}
	void draw() {

		float s = 0.5f;
		float r = 1.0f;
		int w = this->width;
		int h = this->height;
		int d = this->depth;

		for(int z = 0; z < d; z++) {
		for(int y = 0; y < h; y++) {
		for(int x = 0; x < w; x++) {
			if (this->getLife(x, y, z)) {
				if (this->getNeighbours(x,y,z) > 9) continue;
				rules::pointColor(x,y,z,w,h,d, this->getNeighbours(x,y,z));
				drawCube(x*r,y*r,z*r, s);
			} else {
			}
		}
		}
		}
		w = w * r;
		h = h * r;
		d = d * r;

		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
			glVertex3f(-r, -r, -r); glVertex3f(-r, -r, d);
			glVertex3f(-r,  h, -r); glVertex3f(-r,  h, d);
			glVertex3f( w, -r, -r); glVertex3f( w, -r, d);
			glVertex3f( w,  h, -r); glVertex3f( w,  h, d);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex3f(-r, h, -r); glVertex3f(-r, -r, -r); glVertex3f(w, -r, -r); glVertex3f(w, h, -r);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex3f(-r, h, d); glVertex3f(-r, -r, d); glVertex3f(w, -r, d); glVertex3f(w, h, d);
		glEnd();

	}
	void setLife(int x, int y, int z, bool life)
		{ this->map[z][y][x].set(life); }
	Cell get(int x, int y, int z)     { return this->map[z][y][x]; }
	bool getLife(int x, int y, int z) { return this->get(x, y, z).get(); }

	void setNeighbours(int x, int y, int z, int neighbours)
		{ this->map[z][y][x].setNeighbours(neighbours); }
	int getNeighbours(int x, int y, int z)
		{ return this->map[z][y][x].getNeighbours(); }

	int getWidth()  { return this->width;  }
	int getHeight() { return this->height; }
	int getDepth()  { return this->depth;  }

	int D(int d, int s) { // d piste, s sivu
		if (rules::loopMap) {
			if (d >= s) return d - s;
			else if (d < 0) return s + d;
			else return d;
		} else {
			if (d >= s) return s-1;
			else if (d < 0) return 0;
			else return d;
		}
	}
	int X(int x) { return this->D(x, this->width);  }
	int Y(int y) { return this->D(y, this->height); }
	int Z(int z) { return this->D(z, this->depth);  }
};

#endif

