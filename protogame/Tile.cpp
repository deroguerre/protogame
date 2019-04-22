#include "tile.h"

Tile::Tile(int aTiledId, Texture2D aTileset, Rectangle aMapRectangle, Rectangle aTextureRectangle)
{
	mTiledId = aTiledId;
	mTileset = aTileset;
	mMapRectangle = aMapRectangle;
	mTextureRectangle = aTextureRectangle;

	mPosition = { aMapRectangle.x, aMapRectangle.y };
}

void Tile::draw() {
	DrawTextureRec(mTileset, mTextureRectangle, mPosition, WHITE);
}

Tile::~Tile()
{
}