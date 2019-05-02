#include "Globals.h"

//CORE CUSTOM
//---------------------------------------------------------------------------------------------------------------------
bool isMouseOver(Rectangle aRectangle)
{
	bool isOver = false;
	Vector2 lMousePosition = GetMousePosition();

	if (lMousePosition.x >= aRectangle.x && lMousePosition.x <= aRectangle.x + aRectangle.width &&
		lMousePosition.y >= aRectangle.y && lMousePosition.y <= aRectangle.y + aRectangle.height)
	{
			isOver = true;
	}
	else {
		isOver = false;
	}

	return isOver;
}
//---------------------------------------------------------------------------------------------------------------------