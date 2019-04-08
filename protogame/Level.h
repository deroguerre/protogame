#ifndef LEVEL_H
#define LEVEL_H
#include <raylib.h>
#include<stack>
#include <vector>
#include "Room.h"

using namespace std;

class Level {
public:
	Level();
	Level(int aRoomNumber, Texture2D aTileset, std::vector<std::string> aLayerList);
	~Level();

	// Update the current scene
	void update();
	// Draw the current scene
	void draw();

	void generateMaze() ;

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

	void createRoom(pair<int, int> aPosition);
	vector<int> getNeighbours(pair<int, int> aPosition, bool aVisited);
	vector<int> getRoomDoors(int* aMaze, pair<int, int> aPosition);
	vector<stack<pair<int, int>>> findAllPaths();
	void findFarestRoom();
	void nextRoom(int aDoor);

	enum {
		ROOM_DOOR_TOP = 0x01,
		ROOM_DOOR_RIGHT = 0x02,
		ROOM_DOOR_BOTTOM = 0x04,
		ROOM_DOOR_LEFT = 0x08,
		ROOM_VISITED = 0x10
	};

	Texture2D mTileset;
	vector<string> mLayers;
};

#endif
