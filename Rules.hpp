#ifndef RULES_HPP
#define RULES_HPP

namespace rules {
	bool loopMap     = true;
	bool followMouse = true;

	bool willReincarnate(int n) {
//		if (n == 3) return true;
		if (n == 8) return true;
		else return false;
	}
	// Joss on elossa
	bool willStayAlive(int n) {
//		if ( n >= 2 && n <= 3 ) return true;
		if ( n >= 7 && n <= 12 ) return true;
		else return false;
	}
	bool willDie(int n) {
		return !rules::willStayAlive(n);
	}
	void pointColor(int x, int y, int z, int w, int h, int d, int n) {
		glColor3f(	(n-3)/9.0,
					(n-3)/9.0,
					(n-3)/9.0);
	}
}

#endif

