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
	std::list<std::vector<int>>  mLayerList;
	std::vector<Rectangle> mBlockList;

	Room(Texture2D texture, std::vector<std::string> aLayerList, int aNbCol, int aNbRow);
	~Room();

	void Draw();
	std::vector<Rectangle> BlockListCreator(std::vector<int> blockIds);

private:
	void RoomCreator();
	void DrawDoors();

	std::vector<Rectangle> _layerRectangles;
	std::vector<Rectangle> RectangleListCreator(Texture2D aDungeonTile);
	std::vector<int> CSVParser(std::string layerPath);
};

