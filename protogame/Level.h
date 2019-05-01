#pragma once
#include <raylib.h>
#include <stack>
#include <set>
#include "Globals.h"
#include "Room.h"
using namespace std;

class Level {
public:
	Level();
	Level(int aRoomNumber, const char* aTilemap);
	~Level();

	void update();
	void draw();

	void nextRoom(int aDoor);

	Room* getCurrentRoom() { return mCurrentRoom; }

private:
	int mMazeWidth;
	int mMazeHeight;
	unsigned int mRoomNumber;
	int* mMaze;
	Room* mCurrentRoom;
	vector<Room*> mRooms;
	pair<int, int> mFarestRoom;

	void generateMaze();
	void createRooms(pair<int, int> aPosition);
	vector<int> getNeighbours(pair<int, int> aPosition, bool aVisited);
	vector<int> getRoomDoors(int* aMaze, pair<int, int> aPosition);
	vector<stack<pair<int, int>>> findAllPaths();
	void findFarestRoom();

	const char* mTilemap;
};
