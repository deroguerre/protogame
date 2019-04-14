#ifndef LEVEL_H
#define LEVEL_H
#include <raylib.h>
#include <stack>
#include "room.h"

using namespace std;

class Level {
public:
	Level();
	Level(int aRoomNumber, const char* aTilemap);
	~Level();

	// Update the current scene
	void update();
	// Draw the current scene
	void draw();

	void nextRoom(int aDoor);

	Room* getCurrentRoom() { return mCurrentRoom; }

private:
	int mMazeWidth;
	int mMazeHeight;
	float mRoomWidth;
	float mRoomHeight;
	int mRoomNumber;
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

#endif
