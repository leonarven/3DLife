#ifndef LIFE_HPP
#define LIFE_HPP

#include "Cell.hpp"
#include "Map.hpp"
#include "Rules.hpp"

class Life {
private:
public:
	Life() {
		printf("Life constructed\n");
	}
	void update(Map *map) {
		Map *sourcemap = new Map(*map);
		map->fill(false);

		for(int z = 0; z < sourcemap->getDepth(); z++) {
		for(int y = 0; y < sourcemap->getHeight(); y++) {
		for(int x = 0; x < sourcemap->getWidth(); x++) {

			int neighbours = 0;

			int xp = sourcemap->X(x+1);
			int xm = sourcemap->X(x-1);
			int yp = sourcemap->Y(y+1);
			int ym = sourcemap->Y(y-1);
			int zp = sourcemap->Z(z+1);
			int zm = sourcemap->Z(z-1);

			neighbours += sourcemap->getLife(xp, yp, zp);
			neighbours += sourcemap->getLife(xp, y , zp);
			neighbours += sourcemap->getLife(xp, ym, zp);
			neighbours += sourcemap->getLife(x , yp, zp);
			neighbours += sourcemap->getLife(x , y , zp);
			neighbours += sourcemap->getLife(x , ym, zp);
			neighbours += sourcemap->getLife(xm, yp, zp);
			neighbours += sourcemap->getLife(xm, y , zp);
			neighbours += sourcemap->getLife(xm, ym, zp);
			neighbours += sourcemap->getLife(xp, yp, zm);
			neighbours += sourcemap->getLife(xp, y , zm);
			neighbours += sourcemap->getLife(xp, ym, zm);
			neighbours += sourcemap->getLife(x , yp, zm);
			neighbours += sourcemap->getLife(x , y , zm);
			neighbours += sourcemap->getLife(x , ym, zm);
			neighbours += sourcemap->getLife(xm, yp, zm);
			neighbours += sourcemap->getLife(xm, y , zm);
			neighbours += sourcemap->getLife(xm, ym, zm);
			neighbours += sourcemap->getLife(xp, yp, z);
			neighbours += sourcemap->getLife(xp, y , z);
			neighbours += sourcemap->getLife(xp, ym, z);
			neighbours += sourcemap->getLife(x , yp, z);
			neighbours += sourcemap->getLife(x , ym, z);
			neighbours += sourcemap->getLife(xm, yp, z);
			neighbours += sourcemap->getLife(xm, y , z);
			neighbours += sourcemap->getLife(xm, ym, z);

			if (sourcemap->getLife(x, y, z) == true) {
				if (rules::willStayAlive(neighbours)) map->setLife(x, y, z, true);
				else map->setLife(x, y, z, false);
			} else {
				if (rules::willReincarnate(neighbours)) map->setLife(x, y, z, true);
				else map->setLife(x, y, z, false);
			}
		}
		}
		}
	}
};

#endif
