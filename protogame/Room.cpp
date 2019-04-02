#include "Room.h"
#include <raylib.h>
#include <iostream>

Texture2D dungeonTile;
Rectangle gtl;

Room::Room(Texture2D dungeonTileset)
{
	dungeonTile = dungeonTileset;

	//gtl groundTopLeft
	gtl = { 0.0f, 0.0f, (float)dungeonTile.width / 8, (float)dungeonTile.height / 8 };
}

void Room::Draw() {
	//DrawTexture(dungeonTile, 0, 0, WHITE);
	Vector2 origin = { 0, 0 };
	DrawTextureRec(dungeonTile, gtl, origin, WHITE);
}


Room::~Room()
{
}
