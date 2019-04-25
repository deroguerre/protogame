#ifndef WORLD_H
#define WORLD_H

#include <string>
#include "TilemapXmlParser.h"
#include "Tile.h"

namespace WorldHelper {
	const std::string TILEMAP = "world_map";
}

class World {

public:
	World();
	void update(Vector2 aOffset);
	void draw();

private:
	TilemapXmlParser* mTilemapXmlParser = NULL;
	std::vector<Tile*> mTiles;

};
#endif
