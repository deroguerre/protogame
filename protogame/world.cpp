#include "World.h"
#include "globals.h"

World::World() {
	mTilemapXmlParser = new TilemapXmlParser(WorldHelper::TILEMAP);
	createTiles();
}

void World::createTiles() {
	int lTileCounter = 0;

	//Build each individual tile here

	for (auto lGid : mTilemapXmlParser->getTiles()) {

		//If gid is 0, no tile should be drawn. Continue loop
		if (lGid > 0) {
			//Get the tileset for this specific gid
			Tileset lTileset;
			int lClosest = 0;
			for (int i = 0; i < mTilemapXmlParser->getTilesets().size(); i++) {
				if (mTilemapXmlParser->getTilesets()[i].mFirstGid <= lGid) {
					if (mTilemapXmlParser->getTilesets()[i].mFirstGid > lClosest) {
						lClosest = mTilemapXmlParser->getTilesets()[i].mFirstGid;
						lTileset = mTilemapXmlParser->getTilesets().at(i);
					}
				}
			}

			if (lTileset.mFirstGid > -1) {
				//Get the position of the tile in the screen
				int lTileX = 0;
				int lTileY = 0;
				lTileX = lTileCounter % (int)mTilemapXmlParser->getTilemapSize().x;
				lTileX *= mTilemapXmlParser->getTileSize().x;
				lTileY += mTilemapXmlParser->getTileSize().y * (lTileCounter / (int)mTilemapXmlParser->getTilemapSize().x);
				Vector2 lTilePosition = Vector2{ (float)lTileX, (float)lTileY };

				//Calculate the position of the tile in the tileset
				Vector2 lTilesetPosition = this->getTilesetPosition(lTileset, lGid, mTilemapXmlParser->getTileSize().x, mTilemapXmlParser->getTileSize().y);

				Rectangle lTileRec = Rectangle{ lTilesetPosition.x, lTilesetPosition.y, (float)mTilemapXmlParser->getTileSize().x, (float)mTilemapXmlParser->getTileSize().y };

				Tile* lTile = new Tile(lTileset.mTexture, lTilePosition, lTileRec);
				mTiles.push_back(lTile);
			}

		}

		lTileCounter++;
	}
}

Vector2 World::getTilesetPosition(Tileset aTileset, int aGid, int aTileWidth, int aTileHeight) {
	
	int lTilesetWidth = aTileset.mTexture.width;
	int lTilesetHeight = aTileset.mTexture.height;
	
	int lTilesetX = aGid % (lTilesetWidth / aTileWidth) - 1;
	lTilesetX *= aTileWidth;
	
	int lTilesetY = 0;
	int lAmount = ((aGid - aTileset.mFirstGid) / (lTilesetWidth / aTileWidth));
	
	lTilesetY = aTileHeight * lAmount;
	Vector2 lTilesetPosition = Vector2{ (float)lTilesetX, (float)lTilesetY };
	return lTilesetPosition;
}

std::vector<Tile*> mChunk;
void World::update(Vector2 aOffset) {
	mChunk.clear();
	for (int i = 0; i < mTiles.size(); i++) {
		if (mTiles[i]->origin.x >= aOffset.x && mTiles[i]->origin.y >= aOffset.y && mTiles[i]->origin.x < Globals::SCREEN_WIDTH + aOffset.x && mTiles[i]->origin.y < Globals::SCREEN_HEIGHT + aOffset.y)
			mChunk.push_back(mTiles[i]);
	}
}

void World::draw() {
	for (int i = 0; i < mChunk.size(); i++) {
		DrawTextureRec(mChunk[i]->mTileset, mChunk[i]->mapRectangle, mChunk[i]->origin, RAYWHITE);
	}
		
}