#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include <list>

class Room
{
public:
	std::list<std::vector<int>>  mLayerList;
	std::vector<Rectangle> blockList;

	Room(Texture2D texture, std::vector<std::string> aLayerList, int aNbCol, int aNbRow);
	std::vector<Rectangle> CreateBlockList();
	~Room();

	void Draw();
	std::vector<Rectangle> CreateBlockList(Texture2D aTileset);
private:
	std::vector<Rectangle> RectangleListCreator(Texture2D aDungeonTile);
	std::vector<int> CSVParser(std::string layerPath);
	std::vector<Rectangle> _layerRectangles;
};

