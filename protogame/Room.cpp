#include "Room.h"
#include <raylib.h>
#include "globals.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

int nbColTiles = 0;
int nbRowTiles = 0;

Texture2D mTileset;

Vector2 origin = { 0, 0 };
Rectangle mCurrRectangle;

Rectangle topDoor, downDoor, leftDoor, rightDoor;

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

std::vector<Rectangle> Room::BlockListCreator(std::vector<int> blockIds) {

	int lIterator = 0;


	for (size_t itRow = 0; itRow < nbRowTiles; itRow++)			//each row
	{
		for (size_t itCol = 0; itCol < nbColTiles; itCol++)		//each col
		{
			for (auto currLayer : mLayerList) {					//each layer

				if (currLayer[lIterator] != -1) {				//filter

					for (auto tile : blockIds) {				//each block id

						if (currLayer[lIterator] == tile) {		//filter
							blockList.push_back(_layerRectangles[currLayer[lIterator]]);
						}					
					}			
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

	return blockList;
}

//void Room::DrawDoors() {
//	Rectangle topDoor = { (nbColTiles / 2) * 32, 32, 32, 32 };
//	Rectangle downDoor = { (nbColTiles / 2) * 32, (nbRowTiles * 32) - 64, 32, 32 };
//	Rectangle leftDoor = { 0, (nbRowTiles/2) * 32, 32, 32 };
//	Rectangle rightDoor = { (nbColTiles * 32) - 32, (nbRowTiles/2) * 32, 32, 32 };
//	if (GLOBALS::DEBUG) {
//		DrawRectangle(topDoor.x, topDoor.y, topDoor.width, topDoor.height, RED);
//		DrawRectangle(downDoor.x, downDoor.y, downDoor.width, downDoor.height, RED);
//		DrawRectangle(leftDoor.x, leftDoor.y, leftDoor.width, leftDoor.height, RED);
//		DrawRectangle(rightDoor.x, rightDoor.y, rightDoor.width, rightDoor.height, RED);
//	}
//}


void Room::Draw() {

	int lIterator = 0;

	for (size_t itRow = 0; itRow < nbRowTiles; itRow++)
	{
		for (size_t itCol = 0; itCol < nbColTiles; itCol++)
		{
			for (auto currLayer : mLayerList) {
				// on ignore -1 qui représente une tuile vide
				if (currLayer[lIterator] != -1) {

					mCurrRectangle = _layerRectangles[currLayer[lIterator]];
					DrawTextureRec(mTileset, mCurrRectangle, origin, WHITE);
					//this->DrawDoors();

					if (GLOBALS::DEBUG) {
						DrawRectangleLines(origin.x, origin.y, 32, 32, RED);
					}

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
