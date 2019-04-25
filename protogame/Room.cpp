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
	//recupere les calques et les ajoutes a une liste
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
				else if (lStrStream.str() == "door") {
					createDoors(lObjectGroupNode);
				}
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

std::vector<std::string> mAvailableDoors = {
	"topDoor",
	"downDoor",
	"leftDoor",
	"rightDoor"
};

void Room::createDoors(XMLElement * aObjectGroupNode) {

	XMLElement* lObjectNode = aObjectGroupNode->FirstChildElement("object");
	if (lObjectNode != NULL) {
		while (lObjectNode) {
			float lX, lY, lWidth, lHeight;
			std::string lName = lObjectNode->Attribute("name");
			lX = lObjectNode->FloatAttribute("x");
			lY = lObjectNode->FloatAttribute("y");
			lWidth = lObjectNode->FloatAttribute("width");
			lHeight = lObjectNode->FloatAttribute("height");

			for (auto lDoor : mAvailableDoors) {
				if (lDoor == lName) {

					mCollisionDoors.push_back(Rectangle{ lX, lY, lWidth, lHeight });

					Rectangle lTextureRectangle;

					if (lDoor == "topDoor")
						lTextureRectangle = {192, 192, 64, 32};
					if (lDoor == "downDoor")
						lTextureRectangle = { 192, 192, 64, 32 };
					if (lDoor == "leftDoor")
						lTextureRectangle = { 256, 128, 32, 64 };
					if (lDoor == "rightDoor")
						lTextureRectangle = { 224, 128, 32, 64 };

					Tile* lDoor = new Tile(0, mTileset, Rectangle{ lX, lY, lWidth, lHeight }, lTextureRectangle);
					mDoors.push_back(lDoor);
				}
			}

			lObjectNode = lObjectNode->NextSiblingElement("object");
		}
	}
}

void Room::drawDoors() {

	if (mDoorsFlags & ROOM_DOOR_TOP) {
		// 0010 & 0010
	}

	for (auto lDoor : mDoors) {
		DrawTextureRec(mTileset, lDoor->mTextureRectangle, lDoor->mPosition, WHITE);
	}

	//mDoors.push_back();

	//DrawTextureRec(mTileset, currentTile.mTextureRectangle, currentTile.mPosition, WHITE);

	if (Globals::DEBUG) {
		for (auto door : mCollisionDoors) {
			DrawRectangleLines(door.x, door.y, door.width, door.height, GREEN);
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