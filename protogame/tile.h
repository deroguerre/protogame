#ifndef TILE_H
#define TILE_H

#include <raylib.h>
#include <string>
#include <vector>
#include <list>

class Tile
{
public:

	Tile(int aTiledId, Vector2 aOrigin, Rectangle aTextureRectangle);
	Tile(Texture2D aTileset, Vector2 aOrigin, Rectangle aTextureRectangle);

	int mTiledId;
	Texture2D mTileset;
	Vector2 mPosition;
	Rectangle mMapRectangle;
	Rectangle mTextureRectangle;

	Tile(int aTiledId, Texture2D aTileset, Rectangle aMapRetcangle, Rectangle aTextureRectangle);
	void draw();

	~Tile();

private:
	

};

#endif