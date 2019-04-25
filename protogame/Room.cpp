#include "Globals.h"
#include "TilemapXmlParser.h"
#include "Room.h"

const int NB_COL_TILES = 40;
const int NB_ROW_TILES = 23;
const int TILE_SIZE = 32;

XMLDocument lXMLFile;

Room::Room(std::string aTilemap, Texture2D aTileset, std::pair<int, int> aPosition) {

	mTilemap = aTilemap;
	mTileset = aTileset;
	mPosition = aPosition;

	//TilemapXmlParser* mTilemapXmlParser = new TilemapXmlParser("room_map");

	//cree la liste des rectangles depuis la texture fournis
	mLayerRects = this->createTilesetRectangles(mTileset);

	this->loadTmx();
	this->createRoom();
}

std::pair<int, int> Room::getPosition() {
	return mPosition;
}

void Room::loadTmx() {
	//recup�re les calques et les ajoutes � une liste
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

		XMLElement* lObjectGroupNode = lMapNode->FirstChildElement("objectgroup");
		if (lObjectGroupNode != NULL) {
			while (lObjectGroupNode) {
				const char* lName = lObjectGroupNode->Attribute("name");
				std::stringstream lStrStream;
				lStrStream << lName;
			
				if (lStrStream.str() == "wall") {
					createWallCollision(lObjectGroupNode);
				}
				//else if (lStrStream.str() == "door")
				//	createDoors(lObjectGroupNode);
				//else if (lStrStream.str() == "spawn")
				//	createSpawn(lObjectGroupNode);

				lObjectGroupNode = lObjectGroupNode->NextSiblingElement("objectgroup");
			}
		}
}

void Room::createWallCollision(XMLElement * aObjectGroupNode) {
	XMLElement* lObjectNode = aObjectGroupNode->FirstChildElement("object");
	if (lObjectNode != NULL) {
		while (lObjectNode) {
			float lX, lY, lWidth, lHeight;
			lX = lObjectNode->FloatAttribute("x");
			lY = lObjectNode->FloatAttribute("y");
			lWidth = lObjectNode->FloatAttribute("width");
			lHeight = lObjectNode->FloatAttribute("height");

			mCollisionTiles.push_back(Rectangle{ lX, lY, lWidth, lHeight });

			lObjectNode = lObjectNode->NextSiblingElement("object");
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

void Room::setDoors(int aDoors) {
	mDoorsFlags = aDoors;
}

void Room::drawDoors() {
	Rectangle topDoor = { 480, 0, 64, 32 };
	Rectangle downDoor = { 480, 544, 64, 32 };
	Rectangle leftDoor = { 96, 256, 32, 64 };
	Rectangle rightDoor = { 896, 256, 32, 64 };

	if (mDoorsFlags & ROOM_DOOR_TOP) {
		// 0010 & 0010
	}

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