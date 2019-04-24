#include "ItemDatabase.h"

ItemDatabase::ItemDatabase()
{
	this->Build();
}

std::map<int, Item*> ItemDatabase::getItems() {
	return mItems;
}

void ItemDatabase::Build() {

	mItems.insert(std::make_pair(0, new Item(
		"sword1",
		"tape fort !"
	)));
}


ItemDatabase::~ItemDatabase()
{
}
