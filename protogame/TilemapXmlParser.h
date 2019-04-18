#ifndef TILEMAPXMLPARSER_H
#define TILEMAPXMLPARSER_H

#include <raylib.h>
#include "tinyxml2.h"
#include <string>
#include <vector>
#include <map>

using namespace tinyxml2;

struct Tileset;
struct Object;
struct ObjectGroup;

class TilemapXmlParser {
public:
	TilemapXmlParser(std::string aTilemap);
	~TilemapXmlParser();

	Vector2 getTilemapSize();
	Vector2 getTileSize();
	std::vector<Tileset> getTilesets();
	std::vector<int> getTiles();
	void getObject(std::vector<Rectangle>* aRectangles, std::string aObjectGroupName = std::string());
	void getObject(std::vector<Vector2>* aPoint, std::string aObjectGroupName = std::string());
	void getObject(std::map<std::string, Rectangle>* aRectangles, std::string aObjectGroupName = std::string());
	void getObject(std::map<std::string, Vector2>* aPoint, std::string aObjectGroupName = std::string());

private:
	Vector2 mTilemapSize;
	Vector2 mTileSize;
	std::vector<Tileset> mTilesets;
	std::vector<int> mTiles;
	std::vector<ObjectGroup> mObjects;

	void parseTilemap(std::string aTilemap);
	void parseTilesets(XMLElement* aMapNode);
	void parseTiles(XMLElement* aMapNode);
	void parseObject(XMLElement* aMapNode);
};

struct Tileset {
	Texture2D mTexture;
	int mFirstGid;
	
	Tileset(Texture2D aTexture, int aFirstGid) {
		mTexture = aTexture;
		mFirstGid = aFirstGid;
	}
};

struct ObjectGroup {
	std::string mName;
	std::vector<Object> mObjects;

	ObjectGroup(std::string aName, std::vector<Object> aObjects) {
		mName = aName;
		mObjects = aObjects;
	}
};

struct Object {
	std::string mName;
	float mX;
	float mY;
	float mWidth;
	float mHeight;

	Object(std::string aName, float aX, float aY, float aWidth, float aHeight) {
		mName = aName;
		mX = aX;
		mY = aY;
		mWidth = aWidth;
		mHeight = aHeight;
	}
};


#endif