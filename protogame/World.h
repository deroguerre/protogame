#ifndef WORLD_H
#define WORLD_H

#include <string>
#include "TilemapXmlParser.h"
#include "tile.h"

namespace WorldHelper {
	const std::string TILEMAP = "world_tilemap";
}

struct Tileset;

class World {
public:
	World();
	void update(Vector2 aOffset);
	void draw();
private:
	TilemapXmlParser* mTilemapXmlParser;
	std::vector<Tile*> mTiles;

	void createTiles();
	Vector2 getTilesetPosition(Tileset aTileset, int aGid, int aTileWidth, int aTileHeight);
};
#endif
