#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include <list>

class Room
{
public:
	std::list<std::vector<int>>  mLayerList;

	Room(Texture2D texture, std::vector<std::string> aLayerList, int aNbRow, int aNbCol);
	~Room();

	void Draw();
private:
	std::vector<Rectangle> RectangleListCreator(Texture2D aDungeonTile);
	std::vector<int> CSVParser(std::string layerPath);
	std::vector<Rectangle> layerRectangles;
};

