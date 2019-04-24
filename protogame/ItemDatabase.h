#pragma once
#include <map>
#include "Item.h"

using namespace std;

class ItemDatabase
{
public:
	ItemDatabase();
	std::map<int, Item*> getItems();
	void Build();
	~ItemDatabase();
private:
	std::map<int, Item*> mItems;
};

