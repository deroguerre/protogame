#include "tile.h"

Tile::Tile(int aTiledId, Vector2 aOrigin, Rectangle aTextureRectangle)
{
	tiledId = aTiledId;
	origin = aOrigin;
	mapRectangle = { origin.x, origin.y, aTextureRectangle.width, aTextureRectangle.height };
	textureRectangle = aTextureRectangle;
}


Tile::~Tile()
{
}
