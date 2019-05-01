#pragma once
#include "raylib.h"

namespace Globals
{
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	const bool DEBUG = false;
}

namespace Sides {
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
	UPLEFT,
	UPRIGHT,
	DOWN,
	DOWNLEFT,
	DOWNRIGHT
};

enum {
	ROOM_DOOR_TOP = 0x01,
	ROOM_DOOR_RIGHT = 0x02,
	ROOM_DOOR_BOTTOM = 0x04,
	ROOM_DOOR_LEFT = 0x08,
	ROOM_VISITED = 0x10
};

bool isMouseOver(Rectangle aCheckedRectangle);