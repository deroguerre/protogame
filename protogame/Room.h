#ifndef ROOM_H
#define ROOM_H

#include <raylib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include "Globals.h"
#include "Tile.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class Room
{
public:
	Room(std::string aTilemap, Texture2D aTexture, std::pair<int, int> aPosition);
	std::vector<int> csvLineParser(std::string aLayer);
	~Room();
	void draw();

	std::list<std::vector<int>>  mLayerList;

	std::map<std::string, Tile*> getDoorTiles();
	std::vector<Rectangle> getCollisionTiles();
	std::vector<Rectangle> getCollisionDoors();

	void setCollisionTiles(std::vector<int> aTileIds);
	void setCollisionDoors(std::vector<int> aDoorIds);

	void createWallCollision(XMLElement * aObjectGroupNode);
	void createDoors(XMLElement * aObjectGroupNode);

	std::pair<int, int> getPosition();

	int getDoors() { return mDoorsFlags; }
	void setDoors(int aDoors);

	Vector2 getPlayerSpawn(int aPreviousDoor);

private:
	std::string mTilemap;
	Texture2D mTileset;
	std::vector<Tile> mTiles;
	std::map<std::string, Tile*> mActiveDoors;
	std::vector<Rectangle> mCollisionTiles;
	std::vector<Rectangle> mCollisionDoors;
	std::vector<Rectangle> mLayerRects;
	std::pair<int, int> mPosition;
	int mDoorsFlags;

	std::vector<Rectangle> createTilesetRectangles(Texture2D aDungeonTile);
	void loadTmx();
	void createRoom();
	void drawDoors();
};

#endif

