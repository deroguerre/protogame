#include "Tile.h"

Tile::Tile(int aTiledId, Texture2D aTileset, Rectangle aMapRectangle, Rectangle aTextureRectangle)
{
	mTiledId = aTiledId;
	mTileset = aTileset;
	mMapRectangle = aMapRectangle;
	mTextureRectangle = aTextureRectangle;

	mPosition = { aMapRectangle.x, aMapRectangle.y };
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