#include "Room.h"
//#include "TilemapXmlParser.h"

const int NB_COL_TILES = 40;
const int NB_ROW_TILES = 23;
const int TILE_SIZE = 32;

XMLDocument lXMLFile;

Rectangle mRoomSurface = { 256, 96, 768, 512 };

Room::Room(std::string aTilemap, Texture2D aTileset, std::pair<int, int> aPosition) {

	mTilemap = aTilemap;
	mTileset = aTileset;
	mPosition = aPosition;

	//TilemapXmlParser* mTilemapXmlParser = new TilemapXmlParser("room_map");

	//cree la liste des rectangles depuis la texture fournis
	mLayerRects = this->createTilesetRectangles(mTileset);

	this->loadTmx();
	this->createRoom();
	//this->generateRandomWall();
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
			else if (lStrStream.str() == "surface") {

				XMLElement* lObjectNode = lObjectGroupNode->FirstChildElement("object");
				if (lObjectNode != NULL) {
					float lX, lY, lWidth, lHeight;
					mRoomSurface.x = lObjectNode->FloatAttribute("x");
					mRoomSurface.y = lObjectNode->FloatAttribute("y");
					mRoomSurface.width = lObjectNode->FloatAttribute("width");
					mRoomSurface.height = lObjectNode->FloatAttribute("height");
				}
			}

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

void Room::generateRandomWall() {

	Rectangle lPitTexture = { 256, 224, TILE_SIZE, TILE_SIZE };

	int minX = mRoomSurface.x;
	int minY = mRoomSurface.y;
	int maxX = mRoomSurface.x + mRoomSurface.width;
	int maxY = mRoomSurface.y + mRoomSurface.height;

	int randNumWall = GetRandomValue(0, 14);

	for (size_t i = 0; i < randNumWall; i++)
	{

		int randNumX = GetRandomValue(minX, maxX);
		int randNumY = GetRandomValue(minY, maxY);

		while (randNumX % 32 != 0) {
			randNumX--;
		}

		while (randNumY % 32 != 0) {
			randNumY--;
		}

		Rectangle lPitCollision = { randNumX, randNumY, TILE_SIZE, TILE_SIZE };

		Tile* lTile = new Tile(NULL, mTileset, lPitCollision, lPitTexture);
		mTiles.push_back(*lTile);

		mCollisionTiles.push_back(lPitCollision);

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

					Rectangle lTextureRectangle;

					if (lDoor == "topDoor")
						lTextureRectangle = {192, 192, 64, 32};
					if (lDoor == "downDoor")
						lTextureRectangle = { 192, 192, 64, 32 };
					if (lDoor == "leftDoor")
						lTextureRectangle = { 256, 128, 32, 64 };
					if (lDoor == "rightDoor")
						lTextureRectangle = { 224, 128, 32, 64 };

					Tile* lDoorTile = new Tile(0, mTileset, Rectangle{ lX, lY, lWidth, lHeight }, lTextureRectangle);
					mActiveDoors.insert(make_pair(lDoor, lDoorTile));

					mCollisionDoors.push_back(Rectangle{ lX, lY, lWidth, lHeight });
				}
			}

			lObjectNode = lObjectNode->NextSiblingElement("object");
		}
	}
}

void Room::drawDoors() {

	for (auto lDoor : mActiveDoors) {
		DrawTextureRec(mTileset, lDoor.second->mTextureRectangle, lDoor.second->mPosition, WHITE);
	}

	if (Globals::DEBUG) {
		for (auto door : mCollisionDoors) {
			DrawRectangleLines(door.x, door.y, door.width, door.height, GREEN);
		}

		DrawRectangleLines(mRoomSurface.x, mRoomSurface.y, mRoomSurface.width, mRoomSurface.height, BLUE);
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

void Room::setCollisionTiles(std::vector<int> aTileIds) {
	for (auto lCurrentTile : mTiles) {
		for (auto lBlockId : aTileIds) {
			if (lCurrentTile.mTiledId == lBlockId) {
				mCollisionTiles.push_back(lCurrentTile.mMapRectangle);
			}
		}
	}
}

std::map<std::string, Tile*> Room::getDoorTiles() {
	return mActiveDoors;
}

std::vector<Rectangle> Room::getCollisionDoors() {
	return mCollisionDoors;
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

Vector2 Room::getPlayerSpawn(int aPreviousDoor) {
	
	Vector2 lNewSpawnPoint = { NULL, NULL };

	switch (aPreviousDoor)
	{
		case 1 ://top
			lNewSpawnPoint = { 640, 128 };
			break;
		case 2 ://right
			lNewSpawnPoint = { 992, 352 };
			break;
		case 4 ://bottom
			lNewSpawnPoint = { 640, 576 };
			break;
		case 8 ://left
			lNewSpawnPoint = { 288, 352 };
			break;
		default:
			break;
	}

	return lNewSpawnPoint;
}

void Room::draw() {

	//dessine chaque tile de la liste
	for (auto lCurrentTile : mTiles) {
		lCurrentTile.draw();
		DrawTextureRec(mTileset, lCurrentTile.mTextureRectangle, lCurrentTile.mPosition, WHITE);
	}

	this->drawDoors();

	if (Globals::DEBUG) {
		//show blocks tiles
		for (auto lcurrBlockTile : mCollisionTiles) {
			DrawRectangleLines((int)lcurrBlockTile.x, (int)lcurrBlockTile.y, (int)lcurrBlockTile.width, (int)lcurrBlockTile.height, YELLOW);
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