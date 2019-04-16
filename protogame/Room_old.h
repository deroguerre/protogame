#ifndef ROOM_H
#define ROOM_H

#include <raylib.h>
#include "tinyxml2.h"
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "Tile.h"

using namespace tinyxml2;

struct Tileset;
struct Door;

class Room
{
public:
	Room(std::string aTilemap, std::pair<int, int> aPosition);
	~Room();
	void draw();

	std::vector<Rectangle> getCollisionTiles();
	std::vector<Rectangle> getCollisionDoors();

	std::pair<int, int> getPosition() { return mPosition; }

	int getDoors() { return mDoorsFlags; }
	void setDoors(int aDoors);

	void loadMap();
	Vector2 getPlayerSpawn(int aDoor);

private:
	std::string mTilemap;
	std::pair<int, int> mPosition;
	int mDoorsFlags;
	std::vector<Rectangle> mCollisionTiles;
	std::vector<Door> mDoors;
	Vector2 mTilemapSize;
	Vector2 mTileSize;
	std::vector<Tileset> mTilesets;
	std::vector<Tile*> mTiles;
	std::map<std::string, Vector2> mPlayerSpawns;

	void createTilesets(XMLElement* aMapNode);
	void createTiles(XMLElement* aMapNode);
	void createDoors(XMLElement* aObjectGroupNode);
	void createSpawn(XMLElement* aObjectGroupNode);
	void createWallCollision(XMLElement* aObjectGroupNode);

	Vector2 getTilesetPosition(Tileset aTileset, int aGid, int aTileWidth, int aTileHeight, int aTilesetXoffset = 1);

	enum {
		NORTH_DOOR_1 = 36,
		NORTH_DOOR_2 = 37,
		WEST_DOOR_1 = 48,
		WEST_DOOR_2 = 58,
		SOUTH_DOOR_1 = 36,
		SOUTH_DOOR_2 = 37,
		EAST_DOOR_1 = 47,
		EAST_DOOR_2 = 57
	};
};

struct Tileset {
	Texture2D mTexture;
	int mFirstGid;

	Tileset() {
		mFirstGid = -1;
	}

	Tileset(Texture2D aTexture, int aFirstGid) {
		mTexture = aTexture;
		mFirstGid = aFirstGid;
	}
};

struct Door {
public:
	Rectangle mCollisionRect;
	std::pair<Tile*, Tile*> mTiles;

	Door(float aX, float aY, float aWidth, float aHeight, Tile* aTile1, Tile* aTile2) {
		mCollisionRect = Rectangle{ aX, aY, aWidth, aHeight };
		mTiles = std::make_pair(aTile1, aTile2);
	}
};

#endif

