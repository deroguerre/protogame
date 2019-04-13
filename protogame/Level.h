#ifndef LEVEL_H
#define LEVEL_H
#include <raylib.h>
#include <stack>
#include "world.h"

using namespace std;

class Level {
public:
	Level();
	Level(int aRoomNumber, Texture2D aTileset, vector<string> aLayerList, vector<int> aTileCollisions, vector<int> aDoorCollisions);
	~Level();

	// Update the current scene
	void update();
	// Draw the current scene
	void draw();

	void nextRoom(int aDoor);

	World* getCurrentRoom() { return mCurrentRoom; }

private:
	int mMazeWidth;
	int mMazeHeight;
	float mRoomWidth;
	float mRoomHeight;
	int mRoomNumber;
	int* mMaze;
	World* mCurrentRoom;
	vector<World*> mRooms;
	pair<int, int> mFarestRoom;

	void generateMaze();
	void createRooms(pair<int, int> aPosition);
	World* generateRoom(pair<int, int> aPosition);
	vector<int> getNeighbours(pair<int, int> aPosition, bool aVisited);
	vector<int> getRoomDoors(int* aMaze, pair<int, int> aPosition);
	vector<stack<pair<int, int>>> findAllPaths();
	void findFarestRoom();

	Texture2D mTileset;
	vector<string> mLayers;
	vector<int> mTileCollisions;
	vector<int> mDoorCollisions;
};

#endif
