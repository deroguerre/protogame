#ifndef ROOM_H
#define ROOM_H

#include <raylib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "tile.h"
#include "tinyxml2.h"
#include <map>

using namespace tinyxml2;

class Room
{
public:
	Room(std::string aTilemap, Texture2D aTexture);
	std::vector<int> csvLineParser(std::string aLayer);
	~Room();
	void draw();

	std::list<std::vector<int>>  mLayerList;

	std::vector<Rectangle> getCollisionTiles();
	std::vector<Rectangle> getCollisionDoors();

	void setCollisionTiles(std::vector<int> aTileIds);
	void setCollisionDoors(std::vector<int> aDoorIds);

	std::pair<int, int> getPosition() { return mPosition; }

	int getDoors() { return mDoors; }
	void setDoors(int aDoors) { mDoors = aDoors; }

private:
	std::string mTilemap;
	Texture2D mTileset;
	std::vector<Tile> mTiles;
	std::vector<Rectangle> mCollisionTiles;
	std::vector<Rectangle> mCollisionDoors;
	std::vector<Rectangle> mLayerRects;
	std::pair<int, int> mPosition;
	int mDoors;

	std::vector<Rectangle> createTilesetRectangles(Texture2D aDungeonTile);
	std::vector<int> csvParser(std::string layerPath);
	void loadTmx();
	void createRoom();
	void drawDoors();
};

#endif