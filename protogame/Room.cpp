#include "Globals.h"
#include "room.h"
#include "TilemapXmlParser.h"

const int NB_COL_TILES = 32;
const int NB_ROW_TILES = 18;
const int TILE_SIZE = 32;

XMLDocument lXMLFile;

Room::Room(std::string aTilemap, Texture2D aTileset) {

	mTilemap = aTilemap;
	mTileset = aTileset;

	//TilemapXmlParser* mTilemapXmlParser = new TilemapXmlParser("room_map");

	//crée la liste des rectangles depuis la texture fournis
	mLayerRects = this->createTilesetRectangles(mTileset);

	this->loadTmx();
	this->createRoom();
}

void Room::loadTmx() {
	//recupère les calques et les ajoutes à une liste
	lXMLFile.LoadFile(mTilemap.c_str());
	XMLElement* lMapNode = lXMLFile.FirstChildElement("map");

	if (lMapNode == NULL) {
		throw std::exception();
		std::cout << "impossible de lire le fichier";
	}

	for (XMLElement* lCurrentLayer = lMapNode->FirstChildElement("layer"); lCurrentLayer != NULL; lCurrentLayer = lCurrentLayer->NextSiblingElement("layer")) {

		for (XMLElement* lCurrentCSV = lCurrentLayer->FirstChildElement("data"); lCurrentCSV != NULL; lCurrentCSV = lCurrentCSV->NextSiblingElement("data")) {

			std::vector<int> lCurrentLayer = this->csvLineParser((std::string)lCurrentCSV->GetText());
			mLayerList.push_back(lCurrentLayer);
		}
	}
}

std::vector<Rectangle> Room::createTilesetRectangles(Texture2D aTileset) {

	std::vector<Rectangle> lListOfRect;

	float nbCol = (float)aTileset.width / TILE_SIZE;
	float nbRow = (float)aTileset.height / TILE_SIZE;
	float nbTile = nbCol * nbRow;

	float nextCol = 0;
	float nextRow = 0;

	for (int i = 0; i < nbRow; i++) {

		for (int j = 0; j < nbCol; j++) {

			Rectangle lTempRec = { nextCol, nextRow, (float)mTileset.width / nbCol, (float)mTileset.height / nbRow };
			lListOfRect.push_back(lTempRec);

			nextCol += TILE_SIZE;
		}
		nextCol = 0;
		nextRow += TILE_SIZE;
	}

	return lListOfRect;
}

void Room::createRoom() {

	int lIterator = 0;
	Vector2 lOrigin = { 0, 0 };

	for (int itRow = 0; itRow < NB_ROW_TILES; itRow++) {

		for (int itCol = 0; itCol < NB_COL_TILES; itCol++) {
			
			for (auto currLayer : mLayerList) {

				Rectangle lTextureRectangle = { 0, 0, 0, 0 };

				if (currLayer[lIterator] != 0) {

					lTextureRectangle = mLayerRects[currLayer[lIterator]-1];

					Rectangle lMapRectangle = { lOrigin.x, lOrigin.y, TILE_SIZE, TILE_SIZE };
					Tile *lCurrentTile = new Tile(currLayer[lIterator], mTileset, lMapRectangle, lTextureRectangle);

					mTiles.push_back(*lCurrentTile);
				}
			}
			lOrigin.x += TILE_SIZE;
			lIterator++;
		}
		lOrigin.x = 0;
		lOrigin.y += TILE_SIZE;
	}
	lIterator = 0;
	lOrigin.x = 0;
	lOrigin.y = 0;
}

std::vector<Rectangle> Room::getCollisionTiles() {
	return mCollisionTiles;
}

std::vector<Rectangle> Room::getCollisionDoors() {
	return mCollisionDoors;
}

void Room::setCollisionTiles(std::vector<int> aTileIds) {
	for (auto lCurrentTile : mTiles) {
		for (auto lBlockId : aTileIds) {
			if (lCurrentTile.mTiledId == lBlockId) {
				mCollisionTiles.push_back(lCurrentTile.mMapRectangle);
			}
		}
	}
}

void Room::setCollisionDoors(std::vector<int> aDoorIds) {
	for (auto lCurrentTile : mTiles) {
		for (auto lDoorId : aDoorIds) {
			if (lCurrentTile.mTiledId == lDoorId) {
				mCollisionDoors.push_back(lCurrentTile.mMapRectangle);
			}
		}
	}
}

void Room::drawDoors() {
	Rectangle topDoor = { 480, 0, 64, 32 };
	Rectangle downDoor = { 480, 544, 64, 32 };
	Rectangle leftDoor = { 96, 256, 32, 64 };
	Rectangle rightDoor = { 896, 256, 32, 64 };

	mCollisionDoors.push_back(topDoor);
	mCollisionDoors.push_back(downDoor);
	mCollisionDoors.push_back(leftDoor);
	mCollisionDoors.push_back(rightDoor);

	if (Globals::DEBUG) {
		DrawRectangleLines((int)topDoor.x, (int)topDoor.y, (int)topDoor.width, (int)topDoor.height, BLUE);
		DrawRectangleLines((int)downDoor.x, (int)downDoor.y, (int)downDoor.width, (int)downDoor.height, BLUE);
		DrawRectangleLines((int)leftDoor.x, (int)leftDoor.y, (int)leftDoor.width, (int)leftDoor.height, BLUE);
		DrawRectangleLines((int)rightDoor.x, (int)rightDoor.y, (int)rightDoor.width, (int)rightDoor.height, BLUE);
	}
}

void Room::draw() {

	//dessine chaque tile de la liste
	for (auto currentTile : mTiles) {
		currentTile.draw();
		DrawTextureRec(mTileset, currentTile.mTextureRectangle, currentTile.mPosition, WHITE);
	}

	this->drawDoors();

	if (Globals::DEBUG) {
		//show blocks tiles
		for (auto block : mCollisionTiles) {
			DrawRectangleLines((int)block.x, (int)block.y, (int)block.width, (int)block.height, YELLOW);
		}
	}
}
//parse csv to vector
std::vector<int> Room::csvLineParser(std::string aLayer) {

	std::vector<int> lCurrentLayer;

	std::stringstream  lineStream(aLayer);
	std::string        cell;
	while (std::getline(lineStream, cell, ',')) {
		//parse to int and add to vector
		lCurrentLayer.push_back(std::stoi(cell));
	}

	return lCurrentLayer;
}

Room::~Room()
{
}