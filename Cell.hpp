#ifndef CELL_HPP
#define CELL_HPP

class Cell {
private:
	bool life;
	float *color;
public:
	Cell(bool life) : life(life) {}

	void set(bool life)
		{ this->life = life; }
	int get()
		{ return this->life; }

	GLfloat *getColor()
		{ return this->color; }

	int isLiving()
		{ return this->get() == true; }
};

#endif
