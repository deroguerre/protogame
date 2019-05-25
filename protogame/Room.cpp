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

	//TilemapXmlParser* mTilemapXmlParser = new TilemapXmlParser("dungeon_map");

	//cree la liste des rectangles depuis la texture fournis
	mLayerRects = this->createTilesetRectangles(mTileset);

	//std::vector<int> allTiles = mTilemapXmlParser->getTiles();

	this->loadTmx();
	this->createRoom();

	std::vector<int> tileCollide = { 1,2,3,4,5,6,11,16,21,26,31,36,41,42,43,44,45,46,51,52,53,54,55,56,69,79 };
	this->setCollisionTiles(tileCollide);

	//this->generateRandomWall();
}

std::pair<int, int> Room::getRoomPosition() {
	return mPosition;
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

	std::cout << "nombre de colliders : " << mCollisionTiles.size() << std::endl;
	//colliderOptimizer();
	std::cout << "nombre de colliders : " << mCollisionTiles.size() << std::endl << std::endl;
	colliderOptimizer();
}

void Room::colliderOptimizer() {

	bool needNextRound = false;

	try
	{
		for (unsigned int i = 0; i < mCollisionTiles.size(); i++)
		{
			int lCurrentX = (int)mCollisionTiles[i].x + (int)mCollisionTiles[i].width;
			int lCurrentY = (int)mCollisionTiles[i].y + (int)mCollisionTiles[i].height;

			if (lCurrentX == mCollisionTiles[i + 1].x) {
				mCollisionTiles[i].width += TILE_SIZE;
				mCollisionTiles.erase(mCollisionTiles.begin() + i + 1);
				//needNextRound = true;
			}
		}
	}
	catch (const std::exception&)
	{
		std::cout << "Optimisation impossible";
	}

	//if (needNextRound) {
	//	this->colliderOptimizer();
	//}
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

	lXMLFile.LoadFile(mTilemap.c_str());
	XMLElement* lDoorNode = lXMLFile.FirstChildElement("objectgroup");

	Rectangle lTextureRectangle;

	if (mDoorsFlags & ROOM_DOOR_TOP) {
		lTextureRectangle = { 192, 192, 64, 32 };
		Tile* lDoorTile = new Tile(0, mTileset, Rectangle{ 608, 32, 64, 32 }, lTextureRectangle);
		mActiveDoors.insert(std::make_pair("topDoor", lDoorTile));
		mCollisionDoors.push_back(Rectangle{ 608, 32, 64, 32 });
	}
	if (mDoorsFlags & ROOM_DOOR_BOTTOM) {
		lTextureRectangle = { 192, 192, 64, 32 };
		Tile* lDoorTile = new Tile(0, mTileset, Rectangle{ 608, 640, 64, 32 }, lTextureRectangle);
		mActiveDoors.insert(std::make_pair("downDoor", lDoorTile));
		mCollisionDoors.push_back(Rectangle{ 608, 640, 64, 32 });
	}
	if (mDoorsFlags & ROOM_DOOR_LEFT) {
		lTextureRectangle = { 256, 128, 32, 64 };
		Tile* lDoorTile = new Tile(0, mTileset, Rectangle{ 160, 320, 32, 64 }, lTextureRectangle);
		mActiveDoors.insert(std::make_pair("leftDoor", lDoorTile));
		mCollisionDoors.push_back(Rectangle{ 160, 320, 32, 64 });
	}
	if (mDoorsFlags & ROOM_DOOR_RIGHT) {
		lTextureRectangle = { 224, 128, 32, 64 };
		Tile* lDoorTile = new Tile(0, mTileset, Rectangle{ 1088, 320, 32, 64 }, lTextureRectangle);
		mActiveDoors.insert(std::make_pair("rightDoor", lDoorTile));
		mCollisionDoors.push_back(Rectangle{ 1088, 320, 32, 64 });
	}
}

Vector2 Room::getPlayerSpawn(int aPreviousDoor) {

	Vector2 lNewSpawnPoint = { NULL, NULL };

	switch (aPreviousDoor)
	{
	case 1://top
		lNewSpawnPoint = { 640, 128 };
		break;
	case 2://right
		lNewSpawnPoint = { 992, 352 };
		break;
	case 4://bottom
		lNewSpawnPoint = { 640, 576 };
		break;
	case 8://left
		lNewSpawnPoint = { 288, 352 };
		break;
	default:
		break;
	}

	return lNewSpawnPoint;
}

std::vector<XMLElement*> mPatternList;

void Room::loadTmx() {
	//recupere les calques et les ajoutes a une liste
	lXMLFile.LoadFile(mTilemap.c_str());
	XMLElement* lMapNode = lXMLFile.FirstChildElement("map");

	if (lMapNode == NULL) {
		throw std::exception();
		std::cout << "impossible de lire le fichier";
	}

	//recupere la liste des layers
	for (XMLElement* lLayer = lMapNode->FirstChildElement("layer"); lLayer != NULL; lLayer = lLayer->NextSiblingElement("layer")) {
		for (XMLElement* lCSV = lLayer->FirstChildElement("data"); lCSV != NULL; lCSV = lCSV->NextSiblingElement("data")) {

			std::vector<int> lCurrentLayer = this->csvLineParser((std::string)lCSV->GetText());
			mLayerList.push_back(lCurrentLayer);

		}
	}

	std::vector<int> lTempPatternLayers;

	int lRandChoice = GetRandomValue(0, 1);
	int lPatternItterator = 0;

	for (XMLElement* lGroup = lMapNode->FirstChildElement("group"); lGroup != NULL; lGroup = lGroup->NextSiblingElement("group")) {
		for (XMLElement* lLayer = lGroup->FirstChildElement("layer"); lLayer != NULL; lLayer = lLayer->NextSiblingElement("layer")) {

			if (lRandChoice == lPatternItterator) {

				for (XMLElement* lCSV = lLayer->FirstChildElement("data"); lCSV != NULL; lCSV = lCSV->NextSiblingElement("data")) {

					std::vector<int> lCurrentLayer = this->csvLineParser((std::string)lCSV->GetText());
					mLayerList.push_back(lCurrentLayer);
				}
			}
			lPatternItterator++;
		}
	}
	lPatternItterator = 0;

	//recupere les objets
	XMLElement* lObjectGroupNode = lMapNode->FirstChildElement("objectgroup");
	if (lObjectGroupNode != NULL) {
		while (lObjectGroupNode) {
			const char* lName = lObjectGroupNode->Attribute("name");
			std::stringstream lStrStream;
			lStrStream << lName;
			
			if (lStrStream.str() == "wall") {
				//createWallCollision(lObjectGroupNode);
			}
			else if (lStrStream.str() == "door") {
				//createDoors(lObjectGroupNode);
			}
			else if (lStrStream.str() == "surface") {

				XMLElement* lObjectNode = lObjectGroupNode->FirstChildElement("object");
				if (lObjectNode != NULL) {
					//float lX, lY, lWidth, lHeight;
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

void Room::drawDoors() {

	for (auto lDoor : mActiveDoors) {
		DrawTextureRec(mTileset, lDoor.second->mTextureRectangle, lDoor.second->mPosition, WHITE);
	}

	if (Globals::DEBUG) {
		for (auto door : mCollisionDoors) {
			DrawRectangleLines((int)door.x, (int)door.y, (int)door.width, (int)door.height, GREEN);
		}

		DrawRectangleLines((int)mRoomSurface.x, (int)mRoomSurface.y, (int)mRoomSurface.width, (int)mRoomSurface.height, BLUE);
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

void Room::draw() {

	//background
	DrawRectangle(0, 0, Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT, CLITERAL{ 37, 19, 26, 255 });

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

//void Room::generateRandomWall() {
//
//	Rectangle lPitTexture = { 256, 224, TILE_SIZE, TILE_SIZE };
//
//	int minX = mRoomSurface.x;
//	int minY = mRoomSurface.y;
//	int maxX = mRoomSurface.x + mRoomSurface.width;
//	int maxY = mRoomSurface.y + mRoomSurface.height;
//
//	int randNumWall = GetRandomValue(0, 14);
//
//	for (size_t i = 0; i < randNumWall; i++)
//	{
//
//		int randNumX = GetRandomValue(minX, maxX);
//		int randNumY = GetRandomValue(minY, maxY);
//
//		while (randNumX % 32 != 0) {
//			randNumX--;
//		}
//
//		while (randNumY % 32 != 0) {
//			randNumY--;
//		}
//
//		Rectangle lPitCollision = { randNumX, randNumY, TILE_SIZE, TILE_SIZE };
//
//		Tile* lTile = new Tile(NULL, mTileset, lPitCollision, lPitTexture);
//		mTiles.push_back(*lTile);
//
//		mCollisionTiles.push_back(lPitCollision);
//
//	}
//}

Room::~Room()
{
}