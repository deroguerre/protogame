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
	Texture2D mTileset;

	Tile(int aTiledId, Texture2D aTileset, Rectangle aMapRetcangle, Rectangle aTextureRectangle);
	Tile(Texture2D aTileset, Vector2 aPosition, Rectangle aTileRec);
	void draw();
	~Tile();

private:

};