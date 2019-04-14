#include "tile.h"

Tile::Tile(int aTiledId, Vector2 aPosition, Rectangle aTextureRectangle)
{
	mTileId = aTiledId;
	mPosition = aPosition;
	mTileRec = { mPosition.x, mPosition.y, aTextureRectangle.width, aTextureRectangle.height };
	textureRectangle = aTextureRectangle;
}

Tile::Tile(Texture2D aTileset, Vector2 aPosition, Rectangle aTileRec) {
	mTileset = aTileset;
	mPosition = aPosition;
	mTileRec = aTileRec;
}


Tile::~Tile()
{
}

int Tile::getTileId() {
	return mTileId;
}

Texture2D Tile::getTileset() {
	return mTileset;
}

Vector2 Tile::getPosition() {
	return mPosition;
}

Rectangle Tile::getTileRec() {
	return mTileRec;
}

void Tile::draw() {
	DrawTextureRec(mTileset, mTileRec, mPosition, RAYWHITE);
}
