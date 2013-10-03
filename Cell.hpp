#ifndef CELL_HPP
#define CELL_HPP

class Cell {
private:
	bool life;
	int neighbours;
public:

	Cell(bool life) : life(life) {}

	void set(bool life)
		{ this->life = life; }
	bool get()
		{ return this->life; }

	void setNeighbours(int neighbours)
		{ this->neighbours = neighbours; }
	int getNeighbours()
		{ return this->neighbours; }


	int isLiving()
		{ return this->get() == true; }
};

#endif
