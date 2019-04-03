#include "Room.h"
#include <raylib.h>
#include <iostream>

#include <sstream>
#include <fstream>
#include <string>

#include <vector>

Texture2D mDungeonTile;
Rectangle	t0, t21, t51;

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
	t51 = { 352.0f, 64.0f, (float)mDungeonTile.width / 20, (float)mDungeonTile.height / 12 };

	mLayer1 = this->CSVParser("maps/1-map_Calque1.csv");
	mLayer2 = this->CSVParser("maps/1-map_Calque2.csv");

}

Vector2 origin = { 0, 0 };
Rectangle tempRec, tempRec2;

void Room::Draw() {

	int lDataId = 0;

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 40; j++)
		{

			tempRec = this->getTextureRectangle(mLayer1, lDataId);
			tempRec2 = this->getTextureRectangle(mLayer2, lDataId);

			DrawTextureRec(mDungeonTile, tempRec, origin, WHITE);
			DrawTextureRec(mDungeonTile, tempRec2, origin, WHITE);

			origin.x += 32;
			lDataId++;
		}
		origin.x = 0;
		origin.y += 32;
	}
	lDataId = 0;
	origin.x = 0;
	origin.y = 0;
}

Rectangle Room::getTextureRectangle(std::vector<int> aLayer, int aId) {

	Rectangle lTempRec = { 0,0,0,0 };

	switch (aLayer[aId])
	{
	case 0: lTempRec = t0;
		break;
	case 21: lTempRec = t21;
		break;
	case 51: lTempRec = t51;
		break;
	default:
		break;
	}

	return lTempRec;
}

Room::~Room()
{
}
