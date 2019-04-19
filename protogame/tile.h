#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include <list>

class Tile
{
public:
	int tiledId;
	Vector2 origin;
	Rectangle mapRectangle;
	Rectangle textureRectangle;
	Texture2D mTileset;

	Tile(int aTiledId, Vector2 aOrigin, Rectangle aTextureRectangle);
	Tile(Texture2D aTileset, Vector2 aOrigin, Rectangle aTextureRectangle);
	~Tile();
};