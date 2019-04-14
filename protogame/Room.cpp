#include "globals.h"
#include "Room.h"

Room::Room(std::string aTilemap, std::pair<int, int> aPosition) {
	mPosition = aPosition;
	mTilemap = aTilemap;
}

std::vector<Rectangle> Room::getCollisionTiles() {
	return mCollisionTiles;
}

std::vector<Rectangle> Room::getCollisionDoors() {
	std::vector<Rectangle> lDoors;
	for (auto lDoor : mDoors) {
		lDoors.push_back(lDoor.mCollisionRect);
	}
	return lDoors;
}

Vector2 Room::getPlayerSpawn(int aDoor) {
	return aDoor & ROOM_DOOR_TOP ? mPlayerSpawns["north_spawn"] :
		aDoor & ROOM_DOOR_LEFT ? mPlayerSpawns["west_spawn"] :
		aDoor & ROOM_DOOR_BOTTOM ? mPlayerSpawns["south_spawn"] :
		aDoor & ROOM_DOOR_RIGHT ? mPlayerSpawns["east_spawn"] :
		Vector2{ 0, 0 };
}

void Room::setDoors(int aDoors) {
	mDoorsFlags = aDoors;
}

void Room::loadMap() {
	//Parse the .tmx file
	XMLDocument lTilemap;
	std::stringstream lStrStream;
	lStrStream << "maps/" << mTilemap << ".tmx";
	lTilemap.LoadFile(lStrStream.str().c_str());

	XMLElement* lMapNode = lTilemap.FirstChildElement("map");

	//Get the width and the height of the tilemap
	lMapNode->QueryFloatAttribute("width", &mTilemapSize.x);
	lMapNode->QueryFloatAttribute("height", &mTilemapSize.y);

	//Get the width and the height of the tiles
	lMapNode->QueryFloatAttribute("tilewidth", &mTileSize.x);
	lMapNode->QueryFloatAttribute("tileheight", &mTileSize.y);

	createTilesets(lMapNode);
	createTiles(lMapNode);

	//Parse object group
	XMLElement* lObjectGroupNode = lMapNode->FirstChildElement("objectgroup");
	if (lObjectGroupNode != NULL) {
		while (lObjectGroupNode) {
			const char* lName = lObjectGroupNode->Attribute("name");
			std::stringstream lStrStream;
			lStrStream << lName;
			
			if (lStrStream.str() == "wall")
				createWallCollision(lObjectGroupNode);
			else if (lStrStream.str() == "door")
				createDoors(lObjectGroupNode);
			else if (lStrStream.str() == "spawn")
				createSpawn(lObjectGroupNode);

			lObjectGroupNode = lObjectGroupNode->NextSiblingElement("objectgroup");
		}
	}
}

void Room::createTilesets(XMLElement* aMapNode) {
	//Loading the tilesets
	XMLElement* lTilesetNode = aMapNode->FirstChildElement("tileset");
	if (lTilesetNode != NULL) {
		while (lTilesetNode) {
			int lFirstGid;
			const char* lTilesetSource = lTilesetNode->Attribute("source");

			//Parse .tsx file
			XMLDocument lTileset;
			std::stringstream lStrStream;
			lStrStream << "maps/" << lTilesetSource;
			lTileset.LoadFile(lStrStream.str().c_str());

			const char* lImageSource = lTileset.FirstChildElement("tileset")->FirstChildElement("image")->Attribute("source");

			lImageSource += 3; // to remove the ../

			lTilesetNode->QueryIntAttribute("firstgid", &lFirstGid);
			Texture2D lTexture = LoadTextureFromImage(LoadImage(lImageSource));
			mTilesets.push_back(Tileset(lTexture, lFirstGid));
			lTilesetNode = lTilesetNode->NextSiblingElement("tileset");
		}
	}
}

void Room::createTiles(XMLElement* aMapNode) {
	//Loading the layers
	XMLElement* lLayerNode = aMapNode->FirstChildElement("layer");
	if (lLayerNode != NULL) {
		while (lLayerNode) {
			//Loading the data element
			XMLElement* lDataNode = lLayerNode->FirstChildElement("data");
			if (lDataNode != NULL) {
				while (lDataNode) {
					//Loading the tile element
					XMLElement* lTileNode = lDataNode->FirstChildElement("tile");
					if (lTileNode != NULL) {
						int lTileCounter = 0;
						while (lTileNode) {
							//Build each individual tile here
							//If gid is 0, no tile should be drawn. Continue loop
							if (lTileNode->IntAttribute("gid") == 0) {
								lTileCounter++;
								if (lTileNode->NextSiblingElement("tile")) {
									lTileNode = lTileNode->NextSiblingElement("tile");
									continue;
								}
								else {
									break;
								}
							}

							//Get the tileset for this specific gid
							int lGid = lTileNode->IntAttribute("gid");
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

							if (lTileset.mFirstGid == -1) {
								//No tileset was found for this gid
								lTileCounter++;
								if (lTileNode->NextSiblingElement("tile")) {
									lTileNode = lTileNode->NextSiblingElement("tile");
									continue;
								}
								else {
									break;
								}
							}

							//Get the position of the tile in the screen
							int lTileX = 0;
							int lTileY = 0;
							lTileX = lTileCounter % (int)mTilemapSize.x;
							lTileX *= mTileSize.x;
							lTileY += mTileSize.y * (lTileCounter / (int)mTilemapSize.x);
							Vector2 lTilePosition = Vector2{ (float)lTileX, (float)lTileY };

							//Calculate the position of the tile in the tileset
							Vector2 lTilesetPosition = this->getTilesetPosition(lTileset, lGid, mTileSize.x, mTileSize.y);

							Rectangle lTileRec = Rectangle{ lTilesetPosition.x, lTilesetPosition.y, (float)mTileSize.x, (float)mTileSize.y };

							Tile* lTile = new Tile(lTileset.mTexture, lTilePosition, lTileRec);
							mTiles.push_back(lTile);

							lTileCounter++;
							lTileNode = lTileNode->NextSiblingElement("tile");
						}
					}

					lDataNode = lDataNode->NextSiblingElement("data");
				}
			}

			lLayerNode = lLayerNode->NextSiblingElement("layer");
		}
	}
}

void Room::createDoors(XMLElement * aObjectGroupNode) {
	XMLElement* lObjectNode = aObjectGroupNode->FirstChildElement("object");
	if (lObjectNode != NULL) {
		while (lObjectNode) {
			float lX, lY, lWidth, lHeight;
			const char* lName = lObjectNode->Attribute("name");
			std::stringstream lStrStream;
			lStrStream << lName;
			lX = lObjectNode->FloatAttribute("x");
			lY = lObjectNode->FloatAttribute("y");
			lWidth = lObjectNode->FloatAttribute("width");
			lHeight = lObjectNode->FloatAttribute("height");

			mCollisionTiles.push_back(Rectangle{ lX, lY, lWidth, lHeight });

			if (lStrStream.str() == "north_door" && mDoorsFlags & ROOM_DOOR_TOP) {
				Vector2 lTilePosition1 = Vector2{ lX, lY };
				Vector2 lTilePosition2 = Vector2{ lX + lWidth / 2, lY };

				Vector2 lTilesetPosition1 = this->getTilesetPosition(mTilesets[0], NORTH_DOOR_1, mTileSize.x, mTileSize.y, 0);
				Vector2 lTilesetPosition2 = this->getTilesetPosition(mTilesets[0], NORTH_DOOR_2, mTileSize.x, mTileSize.y, 0);

				Rectangle lTileRec1 = Rectangle{ lTilesetPosition1.x, lTilesetPosition1.y, (float)mTileSize.x, (float)mTileSize.y };
				Rectangle lTileRec2 = Rectangle{ lTilesetPosition2.x, lTilesetPosition2.y, (float)mTileSize.x, (float)mTileSize.y };

				Tile* lTile1 = new Tile(mTilesets[0].mTexture, lTilePosition1, lTileRec1);
				Tile* lTile2 = new Tile(mTilesets[0].mTexture, lTilePosition2, lTileRec2);

				Door lDoor = Door(lX, lY, lWidth, lHeight, lTile1, lTile2);
				mDoors.push_back(lDoor);

			}
			else if (lStrStream.str() == "west_door" && mDoorsFlags & ROOM_DOOR_LEFT) {
				Vector2 lTilePosition1 = Vector2{ lX, lY };
				Vector2 lTilePosition2 = Vector2{ lX, lY + lHeight / 2 };

				Vector2 lTilesetPosition1 = this->getTilesetPosition(mTilesets[0], WEST_DOOR_1, mTileSize.x, mTileSize.y, 0);
				Vector2 lTilesetPosition2 = this->getTilesetPosition(mTilesets[0], WEST_DOOR_2, mTileSize.x, mTileSize.y, 0);

				Rectangle lTileRec1 = Rectangle{ lTilesetPosition1.x, lTilesetPosition1.y, (float)mTileSize.x, (float)mTileSize.y };
				Rectangle lTileRec2 = Rectangle{ lTilesetPosition2.x, lTilesetPosition2.y, (float)mTileSize.x, (float)mTileSize.y };

				Tile* lTile1 = new Tile(mTilesets[0].mTexture, lTilePosition1, lTileRec1);
				Tile* lTile2 = new Tile(mTilesets[0].mTexture, lTilePosition2, lTileRec2);

				Door lDoor = Door(lX, lY, lWidth, lHeight, lTile1, lTile2);
				mDoors.push_back(lDoor);
			}
			else if (lStrStream.str() == "south_door" && mDoorsFlags & ROOM_DOOR_BOTTOM) {
				Vector2 lTilePosition1 = Vector2{ lX, lY };
				Vector2 lTilePosition2 = Vector2{ lX + lWidth / 2, lY };

				Vector2 lTilesetPosition1 = this->getTilesetPosition(mTilesets[0], SOUTH_DOOR_1, mTileSize.x, mTileSize.y, 0);
				Vector2 lTilesetPosition2 = this->getTilesetPosition(mTilesets[0], SOUTH_DOOR_2, mTileSize.x, mTileSize.y, 0);

				Rectangle lTileRec1 = Rectangle{ lTilesetPosition1.x, lTilesetPosition1.y, (float)mTileSize.x, (float)mTileSize.y };
				Rectangle lTileRec2 = Rectangle{ lTilesetPosition2.x, lTilesetPosition2.y, (float)mTileSize.x, (float)mTileSize.y };

				Tile* lTile1 = new Tile(mTilesets[0].mTexture, lTilePosition1, lTileRec1);
				Tile* lTile2 = new Tile(mTilesets[0].mTexture, lTilePosition2, lTileRec2);

				Door lDoor = Door(lX, lY, lWidth, lHeight, lTile1, lTile2);
				mDoors.push_back(lDoor);
			}
			else if (lStrStream.str() == "east_door" && mDoorsFlags & ROOM_DOOR_RIGHT) {
				Vector2 lTilePosition1 = Vector2{ lX, lY };
				Vector2 lTilePosition2 = Vector2{ lX, lY + lHeight / 2 };

				Vector2 lTilesetPosition1 = this->getTilesetPosition(mTilesets[0], EAST_DOOR_1, mTileSize.x, mTileSize.y, 0);
				Vector2 lTilesetPosition2 = this->getTilesetPosition(mTilesets[0], EAST_DOOR_2, mTileSize.x, mTileSize.y, 0);

				Rectangle lTileRec1 = Rectangle{ lTilesetPosition1.x, lTilesetPosition1.y, (float)mTileSize.x, (float)mTileSize.y };
				Rectangle lTileRec2 = Rectangle{ lTilesetPosition2.x, lTilesetPosition2.y, (float)mTileSize.x, (float)mTileSize.y };

				Tile* lTile1 = new Tile(mTilesets[0].mTexture, lTilePosition1, lTileRec1);
				Tile* lTile2 = new Tile(mTilesets[0].mTexture, lTilePosition2, lTileRec2);

				Door lDoor = Door(lX, lY, lWidth, lHeight, lTile1, lTile2);
				mDoors.push_back(lDoor);
			}

			lObjectNode = lObjectNode->NextSiblingElement("object");
		}
	}
}

void Room::createSpawn(XMLElement * aObjectGroupNode) {
	XMLElement* lObjectNode = aObjectGroupNode->FirstChildElement("object");
	if (lObjectNode != NULL) {
		while (lObjectNode) {
			float lX = lObjectNode->FloatAttribute("x");
			float lY = lObjectNode->FloatAttribute("y");
			const char* lName = lObjectNode->Attribute("name");
			std::stringstream lStrStream;
			lStrStream << lName;
			mPlayerSpawns[lStrStream.str()] = Vector2{ lX, lY };
			lObjectNode = lObjectNode->NextSiblingElement("object");
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

Vector2 Room::getTilesetPosition(Tileset aTileset, int aGid, int aTileWidth, int aTileHeight, int aTilesetXoffset) {

	int lTilesetWidth = aTileset.mTexture.width;
	int lTilesetHeight = aTileset.mTexture.height;

	int lTilesetX = aGid % (lTilesetWidth / aTileWidth) - aTilesetXoffset;
	lTilesetX *= aTileWidth;

	int lTilesetY = 0;
	int lAmount = ((aGid - aTileset.mFirstGid) / (lTilesetWidth / aTileWidth));

	lTilesetY = aTileHeight * lAmount;
	Vector2 lTilesetPosition = Vector2{ (float)lTilesetX, (float)lTilesetY };
	return lTilesetPosition;
}

void Room::draw() {

	for (auto lTile : mTiles) {
		DrawTextureRec(lTile->getTileset(), lTile->getTileRec(), lTile->getPosition(), RAYWHITE);
	}

	for (auto lDoor : mDoors) {
		lDoor.mTiles.first->draw();
		lDoor.mTiles.second->draw();
	}
}

Room::~Room()
{
}