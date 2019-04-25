#include "TilemapXmlParser.h"
#include <sstream>
#include <iostream>

TilemapXmlParser::TilemapXmlParser(const std::string aTilemapName) {
	parseTilemap(aTilemapName);
}

void TilemapXmlParser::parseTilemap(std::string aTilemap) {
	XMLDocument lTilemapDoc;
	std::stringstream lStrStream;
	lStrStream << "maps/" << aTilemap << ".tmx";
	lTilemapDoc.LoadFile(lStrStream.str().c_str());
	XMLElement* lMapNode = lTilemapDoc.FirstChildElement("map");

	if (lMapNode == NULL) {
		throw std::exception();
		std::cout << "impossible de lire le fichier";
	}

	//Get the width and the height of the tilemap
	lMapNode->QueryFloatAttribute("width", &mTilemapSize.x);
	lMapNode->QueryFloatAttribute("height", &mTilemapSize.y);

	//Get the width and the height of the tiles
	lMapNode->QueryFloatAttribute("tilewidth", &mTileSize.x);
	lMapNode->QueryFloatAttribute("tileheight", &mTileSize.y);

	parseTilesets(lMapNode);
	parseTiles(lMapNode);
	parseObject(lMapNode);
}

void TilemapXmlParser::parseTilesets(XMLElement* aMapNode) {
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

void TilemapXmlParser::parseTiles(XMLElement* aMapNode) {
	//Loading the layers
	XMLElement* lLayerNode = aMapNode->FirstChildElement("layer");
	if (lLayerNode != NULL) {
		while (lLayerNode) {
			//Loading the data element
			XMLElement* lDataNode = lLayerNode->FirstChildElement("data");
			if (lDataNode != NULL) {
				while (lDataNode) {
					const char* lEncoding = lDataNode->Attribute("encoding");
					
					if (lEncoding != NULL) {
						std::stringstream lStrStream;
						lStrStream << lEncoding;
						if (lStrStream.str() == "csv") {
							const char* lTiles = lDataNode->GetText();
							std::stringstream lStrStream;
							lStrStream << lTiles;

							std::string lGid;
							while (std::getline(lStrStream, lGid, ',')) {
								//Cast to int and add to vector
								mTiles.push_back(std::stoi(lGid));
							}
						}
					}
					else {
						//Loading the tile element
						XMLElement* lTileNode = lDataNode->FirstChildElement("tile");
						if (lTileNode != NULL) {
							while (lTileNode) {
								mTiles.push_back(lTileNode->IntAttribute("gid"));

								lTileNode = lTileNode->NextSiblingElement("tile");
							}
						}
					}

					lDataNode = lDataNode->NextSiblingElement("data");
				}
			}
			lLayerNode = lLayerNode->NextSiblingElement("layer");
		}
	}
}

void TilemapXmlParser::parseObject(XMLElement * aMapNode) {

	//Parse object group
	XMLElement* lObjectGroupNode = aMapNode->FirstChildElement("objectgroup");
	if (lObjectGroupNode != NULL) {
		while (lObjectGroupNode) {
			const char* lName = lObjectGroupNode->Attribute("name");
			std::string lObjectGroupName;

			if (lName != NULL) {
				std::stringstream lStrStream;
				lStrStream << lName;
				lObjectGroupName = lStrStream.str();
			}

			XMLElement* lObjectNode = lObjectGroupNode->FirstChildElement("object");
			if (lObjectNode != NULL) {

				std::vector<Object> lObjects;

				while (lObjectNode) {

					float lX = lObjectNode->FloatAttribute("x");
					float lY = lObjectNode->FloatAttribute("y");
					float lWidth = lObjectNode->FloatAttribute("width");
					float lHeight = lObjectNode->FloatAttribute("height");

					const char* lName = lObjectNode->Attribute("name");
					std::string lObjectName;

					if (lName != NULL) {
						std::stringstream lStrStream;
						lStrStream << lName;

						lObjectName = lStrStream.str();
					}

					lObjects.push_back(Object(lObjectName, lX, lY, lWidth, lHeight));

					lObjectNode = lObjectNode->NextSiblingElement("object");
				}

				mObjects.push_back(ObjectGroup(lObjectGroupName, lObjects));
			}

			lObjectGroupNode = lObjectGroupNode->NextSiblingElement("objectgroup");
		}
	}
}

Vector2 TilemapXmlParser::getTilemapSize() {
	return mTilemapSize;
}

Vector2 TilemapXmlParser::getTileSize() {
	return mTileSize;
}

std::vector<Tileset> TilemapXmlParser::getTilesets() {
	return mTilesets;
}

std::vector<int> TilemapXmlParser::getTiles() {
	return mTiles;
}

void TilemapXmlParser::getTiles(std::vector<Tile*>* aTiles) {

	int lTileCounter = 0;

	//Build each individual tile here
	for (auto lGid : getTiles()) {

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
				Vector2 lTilePosition = Vector2{ (float)lTileX, (float)lTileY };


				//Calculate the position of the tile in the tileset
				Vector2 lTilesetPosition = this->getTilesetPosition(lTileset, lGid, mTileSize.x, mTileSize.y);

				Rectangle lTileRec = Rectangle{ lTilesetPosition.x, lTilesetPosition.y, (float)mTileSize.x, (float)mTileSize.y };

				Tile* lTile = new Tile(lTileset.mTexture, lTilePosition, lTileRec);
				aTiles->push_back(lTile);
			}

		}

		lTileCounter++;
		// If lTileCounter >= (mTilemapSize.x * mTilemapSize.y) we have to reset lTileCounter because we are on a new Layer.
		if (lTileCounter >= (mTilemapSize.x * mTilemapSize.y))
			lTileCounter = 0;
	}
	
}

Vector2 TilemapXmlParser::getTilesetPosition(Tileset aTileset, int aGid, int aTileWidth, int aTileHeight) {

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

void TilemapXmlParser::getObject(std::vector<Rectangle>* aRectangles, std::string aObjectGroupName) {
	for (auto lObjectGroup : mObjects) {
		for (auto lObject : lObjectGroup.mObjects) {
			if (!aObjectGroupName.empty())
				if (!lObjectGroup.mName.empty())
					if (aObjectGroupName != lObjectGroup.mName)
						break;

			if (lObject.mWidth > 0 && lObject.mHeight > 0)
				aRectangles->push_back(Rectangle{ lObject.mX, lObject.mY, lObject.mWidth, lObject.mHeight });
		}
	}
}

void TilemapXmlParser::getObject(std::vector<Vector2>* aPoints, std::string aObjectGroupName) {
	for (auto lObjectGroup : mObjects) {
		for (auto lObject : lObjectGroup.mObjects) {
			if (!aObjectGroupName.empty())
				if (!lObjectGroup.mName.empty())
					if (aObjectGroupName != lObjectGroup.mName)
						break;

			if (lObject.mWidth == 0 && lObject.mHeight == 0)
				aPoints->push_back(Vector2{ lObject.mX, lObject.mY });
		}
	}
}

void TilemapXmlParser::getObject(std::map<std::string, Rectangle>* aRectangles, std::string aObjectGroupName) {
	for (auto lObjectGroup : mObjects) {
		for (auto lObject : lObjectGroup.mObjects) {
			if (!aObjectGroupName.empty())
				if (!lObjectGroup.mName.empty())
					if (aObjectGroupName != lObjectGroup.mName)
						break;

			if (lObject.mWidth > 0 && lObject.mHeight > 0)
				aRectangles->insert(std::make_pair(lObject.mName, Rectangle{ lObject.mX, lObject.mY, lObject.mWidth, lObject.mHeight }));
		}
	}
}

void TilemapXmlParser::getObject(std::map<std::string, Vector2>* aPoints, std::string aObjectGroupName) {
	for (auto lObjectGroup : mObjects) {
		for (auto lObject : lObjectGroup.mObjects) {
			if (!aObjectGroupName.empty())
				if (!lObjectGroup.mName.empty())
					if (aObjectGroupName != lObjectGroup.mName)
						break;

			if (lObject.mWidth == 0 && lObject.mHeight == 0)
				aPoints->insert(std::make_pair(lObject.mName, Vector2{ lObject.mX, lObject.mY }));
		}
	}
}

TilemapXmlParser::~TilemapXmlParser()
{
}



