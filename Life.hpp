#ifndef LIFE_HPP
#define LIFE_HPP

#include "Cell.hpp"
#include "Map.hpp"
#include "Rules.hpp"

struct Point3D {
	int x, y, z;
};

class Life {
private:
public:
	Life() {
		printf("Life constructed\n");
	}
	void update(Map *map) {
		std::vector<Point3D> lifeDelta;

		for(int z = 0; z < map->getDepth(); z++) {
		for(int y = 0; y < map->getHeight(); y++) {
		for(int x = 0; x < map->getWidth(); x++) {

			int neighbours = 0;

			int xp = map->X(x+1);
			int xm = map->X(x-1);
			int yp = map->Y(y+1);
			int ym = map->Y(y-1);
			int zp = map->Z(z+1);
			int zm = map->Z(z-1);

			neighbours += map->getLife(xp, yp, zp);
			neighbours += map->getLife(xp, y , zp);
			neighbours += map->getLife(xp, ym, zp);
			neighbours += map->getLife(x , yp, zp);
			neighbours += map->getLife(x , y , zp);
			neighbours += map->getLife(x , ym, zp);
			neighbours += map->getLife(xm, yp, zp);
			neighbours += map->getLife(xm, y , zp);
			neighbours += map->getLife(xm, ym, zp);
			neighbours += map->getLife(xp, yp, zm);
			neighbours += map->getLife(xp, y , zm);
			neighbours += map->getLife(xp, ym, zm);
			neighbours += map->getLife(x , yp, zm);
			neighbours += map->getLife(x , y , zm);
			neighbours += map->getLife(x , ym, zm);
			neighbours += map->getLife(xm, yp, zm);
			neighbours += map->getLife(xm, y , zm);
			neighbours += map->getLife(xm, ym, zm);
			neighbours += map->getLife(xp, yp, z);
			neighbours += map->getLife(xp, y , z);
			neighbours += map->getLife(xp, ym, z);
			neighbours += map->getLife(x , yp, z);
			neighbours += map->getLife(x , ym, z);
			neighbours += map->getLife(xm, yp, z);
			neighbours += map->getLife(xm, y , z);
			neighbours += map->getLife(xm, ym, z);

			if (map->getLife(x, y, z) == true && rules::willDie(neighbours)) {
				lifeDelta.emplace_back(Point3D{ x, y, z });
			} else if (map->getLife(x, y, z) == false && (rules::willReincarnate(neighbours))) {
				lifeDelta.emplace_back(Point3D{ x, y, z });
			}
		}
		}
		}

		for ( const Point3D& p : lifeDelta ) {
			map->setLife(p.x, p.y, p.z, !map->getLife(p.x, p.y, p.z));	
		}
	}
};

#endif
