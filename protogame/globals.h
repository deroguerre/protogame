#ifndef GLOBALS_H
#define GLOBALS_H

namespace GLOBALS 
{
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 608;
	const bool DEBUG = true;
}

namespace sides {
	enum Side {
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		NONE
	};

	inline Side getOppositeSide(Side side) {
		return
			side == TOP ? BOTTOM :
			side == BOTTOM ? TOP :
			side == LEFT ? RIGHT :
			side == RIGHT ? LEFT :
			NONE;
	}
}

enum Direction 
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

#endif
