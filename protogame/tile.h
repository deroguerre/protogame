#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include <list>

class Tile
{
public:
	int mTiledId;
	Vector2 mPosition;
	Rectangle mMapRectangle;
	Rectangle mTextureRectangle;

	Tile(int aTiledId, Texture2D aTileset, Rectangle aMapRetcangle, Rectangle aTextureRectangle);
	void draw();
	~Tile();

private:
	Texture2D mTileset;

};