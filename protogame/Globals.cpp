#include "Globals.h"

//CORE CUSTOM
//---------------------------------------------------------------------------------------------------------------------
bool isMouseOver(Rectangle aCheckedRectangle)
{
	bool isOver = false;
	Vector2 lMousePosition = GetMousePosition();

	if (lMousePosition.x >= aCheckedRectangle.x && lMousePosition.x <= aCheckedRectangle.x + aCheckedRectangle.width &&
		lMousePosition.y >= aCheckedRectangle.y && lMousePosition.y <= aCheckedRectangle.y + aCheckedRectangle.height)
	{
			isOver = true;
	}
	else {
		isOver = false;
	}

	return isOver;
}
//---------------------------------------------------------------------------------------------------------------------