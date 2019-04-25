#include "World.h"
#include "Globals.h"
#include <iostream>

struct Tileset;
World::World() {
	mTilemapXmlParser = new TilemapXmlParser(WorldHelper::TILEMAP);
	mTilemapXmlParser->getTiles(&mTiles);
}

void World::update(Vector2 aOffset) {
}

void World::draw() {
	for (int i = 0; i < mTiles.size(); i++) {
		DrawTextureRec(mTiles[i]->mTileset, mTiles[i]->mMapRectangle, mTiles[i]->mPosition, RAYWHITE);
	}		
}