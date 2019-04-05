#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include <list>

class Tile
{
public:
	int mId;
	Rectangle mMapRectangle;
	Rectangle mTextureRectangle;

	Tile(int aId, Rectangle aMapRectangle, Rectangle aTextureRectangle);
	~Tile();
};

