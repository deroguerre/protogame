#include "tile.h"

Tile::Tile(int aTiledId, Vector2 aOrigin, Rectangle aTextureRectangle)
{
	tiledId = aTiledId;
	origin = aOrigin;
	mapRectangle = { origin.x, origin.y, aTextureRectangle.width, aTextureRectangle.height };
	textureRectangle = aTextureRectangle;
}

Tile::Tile(Texture2D aTileset, Vector2 aPosition, Rectangle aTileRec)
{
	mTileset = aTileset;
	origin = aPosition;
	mapRectangle = aTileRec;
}


Tile::~Tile()
{
}