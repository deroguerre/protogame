#include "World.h"
#include "globals.h"

struct Tileset;
World::World() {
	mTilemapXmlParser = new TilemapXmlParser(WorldHelper::TILEMAP);
	mTilemapSize = mTilemapXmlParser->getTilemapSize();
	mTileSize = mTilemapXmlParser->getTileSize();
	mTilesets = mTilemapXmlParser->getTilesets();
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
			for (int i = 0; i < mTilesets.size(); i++) {
				if (mTilesets[i].mFirstGid <= lGid) {
					if (mTilesets[i].mFirstGid > lClosest) {
						lClosest = mTilesets[i].mFirstGid;
						lTileset = mTilesets.at(i);
					}
				}
			}

			if (lTileset.mFirstGid > -1) {
				//Get the position of the tile in the screen
				int lTileX = 0;
				int lTileY = 0;
				lTileX = lTileCounter % (int)mTilemapSize.x;
				lTileX *= mTileSize.x;
				lTileY += mTileSize.y * (lTileCounter / (int)mTilemapSize.x);
				//Vector2 lTilePosition = Vector2{ (float)lTileX, (float)lTileY };
				Rectangle lTilePosition = { (float)lTileX, (float)lTileY , 32, 32};

				//Calculate the position of the tile in the tileset
				Vector2 lTilesetPosition = this->getTilesetPosition(lTileset, lGid, mTileSize.x, mTileSize.y);

				Rectangle lTileRec = Rectangle{ lTilesetPosition.x, lTilesetPosition.y, (float)mTileSize.x, (float)mTileSize.y };

				Tile* lTile = new Tile(lGid, lTileset.mTexture, lTilePosition, lTileRec);
				this->mTiles.push_back(lTile);
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
	for (int i = 0; i < this->mTiles.size(); i++) {
		if (this->mTiles[i]->mPosition.x >= aOffset.x && this->mTiles[i]->mPosition.y >= aOffset.y && this->mTiles[i]->mPosition.x < Globals::SCREEN_WIDTH + aOffset.x && this->mTiles[i]->mPosition.y < Globals::SCREEN_HEIGHT + aOffset.y)
			mChunk.push_back(this->mTiles[i]);
	}
}

void World::draw() {
	for (int i = 0; i < mChunk.size(); i++) {
		DrawTextureRec(mChunk[i]->mTileset, mChunk[i]->mMapRectangle, mChunk[i]->mPosition, RAYWHITE);
	}
		
}