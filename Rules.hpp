#ifndef RULES_HPP
#define RULES_HPP

namespace rules {
	bool loopMap = false;

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
}

#endif

