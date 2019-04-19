#include "tile.h"

Tile::Tile(int aTiledId, Vector2 aOrigin, Rectangle aTextureRectangle)
{
	mTiledId = aTiledId;
	mTextureRectangle = aTextureRectangle;

	mPosition = { aTextureRectangle.x, aTextureRectangle.y };
}

Tile::Tile(Texture2D aTileset, Vector2 aPosition, Rectangle aTileRec)
{
	mTileset = aTileset;
	mPosition = aPosition;
	mMapRectangle = aTileRec;
}

void Tile::draw() {
	DrawTextureRec(mTileset, mTextureRectangle, mPosition, WHITE);
}


Tile::~Tile()
{
}