#include "Room.h"
#include <raylib.h>
#include <iostream>

#include <sstream>
#include <fstream>
#include <string>

#include <vector>

Texture2D mDungeonTile;
Rectangle	t0, t21;

std::vector<int> mLayer1, mLayer2;

std::vector<int> Room::CSVParser(std::string layerPath) {
	std::ifstream  data(layerPath);

	std::vector<int> lCurrentLayer;

	std::string line;
	while (std::getline(data, line))
	{
		std::stringstream  lineStream(line);
		std::string        cell;
		while (std::getline(lineStream, cell, ','))
		{
			//parse to int and add in vector array
			lCurrentLayer.push_back(std::stoi(cell));
		}
	}

	return lCurrentLayer;
}

Room::Room(Texture2D aDungeonTileset)
{
	mDungeonTile = aDungeonTileset;
	t0 = { 0.0f, 0.0f, (float)mDungeonTile.width / 20, (float)mDungeonTile.height / 12 };
	t21 = { 32.0f, 32.0f, (float)mDungeonTile.width / 20, (float)mDungeonTile.height / 12 };

	mLayer1 = this->CSVParser("maps/1-map_Calque1.csv");
	//mLayer2 = this->CSVParser("maps/1-map_Calque2.csv");
}

Vector2 origin = { 0, 0 };
Rectangle tempRec;

void Room::Draw() {

	int lDataId = 0;

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			switch (mLayer1[lDataId])
			{
			case 0: tempRec = t0;
				break;
			case 21: tempRec = t21;
				break;
			default:
				break;
			}
			lDataId++;

			DrawTextureRec(mDungeonTile, tempRec, origin, WHITE);
			origin.x += 32;
		}
		origin.x = 0;
		origin.y += 32;
	}
	lDataId = 0;
	origin.x = 0;
	origin.y = 0;
}

Room::~Room()
{
}
