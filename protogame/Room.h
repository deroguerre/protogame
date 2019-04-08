#pragma once
#include <raylib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

class Room
{
public:
	Room(std::pair<int, int> aPosition, Texture2D texture, std::vector<std::string> aLayerList);
	~Room();

	std::list<std::vector<int>>  mLayerList;
	std::vector<Rectangle> mBlockList;

	void draw();
	std::vector<Rectangle> blockListCreator(std::vector<int> blockIds);
	std::pair<int, int> getPosition() { return mPosition; }
	int getDoors() { return mDoors; }
	void setDoors(int aDoors) {mDoors = aDoors;	}

private:
	void roomCreator();
	void drawDoors();

	std::pair<int, int> mPosition;
	int mDoors;
	std::vector<Rectangle> _layerRectangles;
	std::vector<Rectangle> rectangleListCreator(Texture2D aDungeonTile);
	std::vector<int> csvParser(std::string layerPath);
};

