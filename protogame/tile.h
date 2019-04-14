#ifndef TILE_H
#define TILE_H

#include <raylib.h>

class Tile
{
public:
	Tile(int aTiledId, Vector2 aOrigin, Rectangle aTextureRectangle);
	Tile(Texture2D aTileset, Vector2 aPosition, Rectangle aTileRec);
	~Tile();

	Rectangle textureRectangle;

	int getTileId();
	Texture2D getTileset();
	Vector2 getPosition();
	Rectangle getTileRec();

	void draw();

private:
	int mTileId;
	Texture2D mTileset;
	Vector2 mPosition;
	Rectangle mTileRec;
};

#endif

