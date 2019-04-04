#include "Room.h"
#include <raylib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

int nbColTiles = 0;
int nbRowTiles = 0;

Texture2D mTileset;
std::vector<int> mLayer1, mLayer2;

Vector2 origin = { 0, 0 };
Rectangle mCurrRectangle;

Room::Room(Texture2D aDungeonTileset, std::vector<std::string> aLayerList,  int aNbCol, int aNbRow)
{
	mTileset = aDungeonTileset;
	nbColTiles = aNbCol;
	nbRowTiles = aNbRow;

	//crée la liste des rectangles depuis la texture fournis (only 32x32)
	_layerRectangles = this->RectangleListCreator(mTileset);

	//recupère les calques et les ajoutes à une liste 
	for (size_t i = 0; i < aLayerList.size(); i++)
	{
		std::vector<int> lCurrentLayer = this->CSVParser(aLayerList[i]);
		mLayerList.push_back(lCurrentLayer);
	}

}

void Room::Draw() {

	int lIterator = 0;

	for (size_t itRow = 0; itRow < 20; itRow++)
	{
		for (size_t itCol = 0; itCol < 40; itCol++)
		{
			for (auto item : mLayerList) {

				// on ignore -1 qui représente une tuile vide
				if (item[lIterator] != -1) {
					mCurrRectangle = _layerRectangles[item[lIterator]];
					DrawTextureRec(mTileset, mCurrRectangle, origin, WHITE);
				}
			}
			origin.x += 32;
			lIterator++;
		}
		origin.x = 0;
		origin.y += 32;
	}
	lIterator = 0;
	origin.x = 0;
	origin.y = 0;
}

std::vector<Rectangle> Room::RectangleListCreator(Texture2D aTileset) {

	std::vector<Rectangle> lListOfRect;

	int tileSilze = 32;

	float nbCol = (float)aTileset.width / 32;
	float nbRow = (float)aTileset.height / 32;
	float nbTile = nbCol * nbRow;

	float nextCol = 0;
	float nextRow = 0;

	for (size_t i = 0; i < nbRow; i++)
	{
		for (size_t j = 0; j < nbCol; j++)
		{
			Rectangle lTempRec = { nextCol, nextRow, (float)mTileset.width / nbCol, (float)mTileset.height / nbRow };
			lListOfRect.push_back(lTempRec);

			nextCol += 32;
		}
		nextCol = 0;
		nextRow += 32;
	}

	return lListOfRect;
}

//parse csv to vector
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
			//parse to int and add to vector
			lCurrentLayer.push_back(std::stoi(cell));
		}
	}

	return lCurrentLayer;
}

Room::~Room()
{
}
