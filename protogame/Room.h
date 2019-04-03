#pragma once
#include <raylib.h>
#include <string>
#include <vector>
class Room
{
public:
	std::vector<int> CSVParser(std::string layerPath);
	Room(Texture2D texture);
	void Draw();
	~Room();
};

