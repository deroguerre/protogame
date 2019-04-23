#ifndef TILE_H
#define TILE_H

#include <raylib.h>
#include <string>
#include <vector>
#include <list>

class Tile
{
public:

	Tile(int aTiledId, Texture2D aTileset, Rectangle aMapRectangle, Rectangle aTextureRectangle);
	Tile(Texture2D aTileset, Vector2 aOrigin, Rectangle aTextureRectangle);



	int mTiledId;
	Vector2 mPosition;
	Rectangle mMapRectangle;
	Rectangle mTextureRectangle;
	Texture2D mTileset;

	void draw();
	~Tile();

private:

};

#endif