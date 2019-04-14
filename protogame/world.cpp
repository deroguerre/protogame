#include "globals.h"
#include "world.h"

const int NB_COL_TILES = 25;
const int NB_ROW_TILES = 18;

World::World(std::pair<int, int> aPosition, Texture2D aDungeonTileset, std::vector<std::string> aLayerList)
{
	mPosition = aPosition;
	mTileset = aDungeonTileset;

	//crée la liste des rectangles depuis la texture fournis (only 32x32)
	mLayerRects = this->rectangleListCreator(mTileset);

	//recupère les calques et les ajoutes à une liste 
	for (int i = 0; i < aLayerList.size(); i++) {
		std::vector<int> lCurrentLayer = this->csvParser(aLayerList[i]);
		mLayerList.push_back(lCurrentLayer);
	}

	this->roomCreator();
}

void World::roomCreator() {

	int lIterator = 0;
	Vector2 lOrigin = { 0, 0 };

	for (int itRow = 0; itRow < NB_ROW_TILES; itRow++)
	{
		for (int itCol = 0; itCol < NB_COL_TILES; itCol++)
		{
			for (auto currLayer : mLayerList) {

				Rectangle lCurrRectangle = { 0, 0, 0, 0 };
				Vector2 currOrigin = { lOrigin.x, lOrigin.y };

				if (currLayer[lIterator] != -1) {
					lCurrRectangle = mLayerRects[currLayer[lIterator]];
					Tile *lCurrentTile = new Tile(currLayer[lIterator], currOrigin, lCurrRectangle);
					mTiles.push_back(*lCurrentTile);
				}
			}
			lOrigin.x += 32;
			lIterator++;
		}
		lOrigin.x = 0;
		lOrigin.y += 32;
	}
	lIterator = 0;
	lOrigin.x = 0;
	lOrigin.y = 0;
}

std::vector<Rectangle> World::getCollisionTiles() {
	return mCollisionTiles;
}

std::vector<Rectangle> World::getCollisionDoors() {
	return mCollisionDoors;
}

void World::setCollisionTiles(std::vector<int> aTileIds) {
	for (auto lCurrentTile : mTiles) {
		for (auto lBlockId : aTileIds) {
			if (lCurrentTile.getTileId() == lBlockId) {
				mCollisionTiles.push_back(lCurrentTile.getTileRec());
			}
		}
	}
}

void World::setCollisionDoors(std::vector<int> aDoorIds) {
	for (auto lCurrentTile : mTiles) {
		for (auto lDoorId : aDoorIds) {
			if (lCurrentTile.getTileId() == lDoorId) {
				mCollisionDoors.push_back(lCurrentTile.getTileRec());
			}
		}
	}
}

void World::drawDoors() {
	Rectangle topDoor = { 384, 32, 32, 32 };
	Rectangle downDoor = { 384, 544, 32, 32 };
	Rectangle leftDoor = { 0, 288, 32, 32 };
	Rectangle rightDoor = { 768, 288, 32, 32 };

	if (GLOBALS::DEBUG) {
		DrawRectangleLines((int)topDoor.x, (int)topDoor.y, (int)topDoor.width, (int)topDoor.height, BLUE);
		DrawRectangleLines((int)downDoor.x, (int)downDoor.y, (int)downDoor.width, (int)downDoor.height, BLUE);
		DrawRectangleLines((int)leftDoor.x, (int)leftDoor.y, (int)leftDoor.width, (int)leftDoor.height, BLUE);
		DrawRectangleLines((int)rightDoor.x, (int)rightDoor.y, (int)rightDoor.width, (int)rightDoor.height, BLUE);
	}
}

void World::draw() {

	//dessine chaque tile de la liste
	for (auto currentTile : mTiles) {
		DrawTextureRec(mTileset, currentTile.textureRectangle, currentTile.getPosition(), WHITE);
	}

	this->drawDoors();

	if (GLOBALS::DEBUG) {

		//tiles counter
		//int lIterator = 0;
		//for (int itRow = 0; itRow < nbRowTiles; itRow++)
		//{
		//	for (int itCol = 0; itCol < nbColTiles; itCol++)
		//	{
		//		char buf[256];
		//		sprintf_s(buf, "%d", lIterator);
		//		DrawText(buf, itCol * 32, itRow * 32, 10, LIGHTGRAY);
		//		lIterator++;
		//	}
		//}
		//lIterator = 0;

		//show block l
		for (auto block : mCollisionTiles) {
			DrawRectangleLines((int)block.x, (int)block.y, (int)block.width, (int)block.height, YELLOW);
		}
	}
}

std::vector<Rectangle> World::rectangleListCreator(Texture2D aTileset) {

	std::vector<Rectangle> lListOfRect;

	int tileSilze = 32;

	float nbCol = (float)aTileset.width / 32;
	float nbRow = (float)aTileset.height / 32;
	float nbTile = nbCol * nbRow;

	float nextCol = 0;
	float nextRow = 0;

	for (int i = 0; i < nbRow; i++)
	{
		for (int j = 0; j < nbCol; j++)
		{
			Rectangle lTempRec = { nextCol, nextRow, (float)mTileset.width / nbCol, (float)mTileset.height / nbRow };
			lListOfRect.push_back(lTempRec);

			nextCol += 32;
		}
		nextCol = 0;
		nextRow += 32;
	}

	return lListOfRect;
}

//parse csv to vector
std::vector<int> World::csvParser(std::string layerPath) {
	std::ifstream  data(layerPath);

	std::vector<int> lCurrentLayer;

	std::string line;
	while (std::getline(data, line))
	{
		std::stringstream  lineStream(line);
		std::string        cell;
		while (std::getline(lineStream, cell, ','))
		{
			//parse to int and add to vector
			lCurrentLayer.push_back(std::stoi(cell));
		}
	}

	return lCurrentLayer;
}

World::~World()
{
}
