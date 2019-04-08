#pragma once
#include <raylib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "tile.h"

class Room
{
public:
	Room(std::pair<int, int> aPosition, Texture2D aTexture, std::vector<std::string> aLayerList);
	~Room();
	void draw();

	std::list<std::vector<int>>  mLayerList;
	
	std::vector<Rectangle> getCollisionTiles();
	std::vector<Rectangle> getCollisionDoors();

	void setCollisionTiles(std::vector<int> aTileIds);
	void setCollisionDoors(std::vector<int> aDoorIds);
	
	std::pair<int, int> getPosition() { return mPosition; }
	
	int getDoors() { return mDoors; }
	void setDoors(int aDoors) {mDoors = aDoors;	}

private:
	void roomCreator();
	void drawDoors();
	int mDoors;
	std::vector<Tile> mTiles;
	Texture2D mTileset;
	std::vector<Rectangle> mCollisionTiles;
	std::vector<Rectangle> mCollisionDoors;
	std::pair<int, int> mPosition;
	std::vector<Rectangle> mLayerRects;
	std::vector<Rectangle> rectangleListCreator(Texture2D aDungeonTile);
	std::vector<int> csvParser(std::string layerPath);
};

