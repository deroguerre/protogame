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

enum {
	ROOM_DOOR_TOP = 0x01,
	ROOM_DOOR_RIGHT = 0x02,
	ROOM_DOOR_BOTTOM = 0x04,
	ROOM_DOOR_LEFT = 0x08,
	ROOM_VISITED = 0x10
};

#endif
