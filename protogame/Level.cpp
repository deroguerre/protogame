#include "Level.h"
#include <set>
#include "globals.h"

float mTinyMapWidth = 128.0f;
float mTinyMapHeight = 96.0f;
Vector2 mTinyMapOffset;

Level::Level(int aRoomNumber, Texture2D aTileset, vector<string> aLayerList, vector<int> aTileCollisions, vector<int> aDoorCollisions) {
	mMazeWidth = sqrt(aRoomNumber) + 1;
	mMazeHeight = sqrt(aRoomNumber) + 1;
	mRoomNumber = aRoomNumber;
	mRoomWidth = 800;
	mRoomHeight = 600;
	mTinyMapOffset = {mRoomWidth - mTinyMapWidth, 0.0f};

	mTileset = aTileset;
	mLayers = aLayerList;
	mTileCollisions = aTileCollisions;
	mDoorCollisions = aDoorCollisions;

	generateMaze();
}

void Level::update() {
	if (IsKeyPressed(KEY_ENTER)) {
		generateMaze();
	}
}

void Level::draw() {

	mCurrentRoom->draw();

	// Draw the mini map
	DrawRectangle(mTinyMapOffset.x, mTinyMapOffset.y, mTinyMapWidth, mTinyMapHeight, Fade(RAYWHITE, 0.4f));
	DrawRectangleLines(mTinyMapOffset.x, mTinyMapOffset.y, mTinyMapWidth, mTinyMapHeight, Fade(BLACK, 0.5f));
	for (int i = 0; i < mRooms.size(); i++) {

		DrawRectangle(
			(mTinyMapOffset.x + mRooms[i]->getPosition().first * (mTinyMapWidth / mMazeWidth)),
			(mTinyMapOffset.y + mRooms[i]->getPosition().second * (mTinyMapHeight / mMazeHeight)),
			mTinyMapWidth / mMazeWidth,
			mTinyMapHeight / mMazeHeight,
			Fade(BLACK, 0.4f));

		DrawRectangle(
			(mTinyMapOffset.x + mFarestRoom.first * (mTinyMapWidth / mMazeWidth)),
			(mTinyMapOffset.y + mFarestRoom.second * (mTinyMapHeight / mMazeHeight)),
			mTinyMapWidth / mMazeWidth,
			mTinyMapHeight / mMazeHeight,
			Fade(RED, 0.1f));

		DrawRectangle(
			(mTinyMapOffset.x + mRooms[0]->getPosition().first * (mTinyMapWidth / mMazeWidth)),
			(mTinyMapOffset.y + mRooms[0]->getPosition().second * (mTinyMapHeight / mMazeHeight)),
			mTinyMapWidth / mMazeWidth,
			mTinyMapHeight / mMazeHeight,
			Fade(DARKGREEN, 0.1f));

		DrawRectangle(
			(mTinyMapOffset.x + mCurrentRoom->getPosition().first * (mTinyMapWidth / mMazeWidth)),
			(mTinyMapOffset.y + mCurrentRoom->getPosition().second * (mTinyMapHeight / mMazeHeight)),
			mTinyMapWidth / mMazeWidth,
			mTinyMapHeight / mMazeHeight,
			Fade(RAYWHITE, 0.1f));

		DrawRectangleLinesEx(
			{ (mTinyMapOffset.x + mRooms[i]->getPosition().first * (mTinyMapWidth / mMazeWidth)),
			(mTinyMapOffset.y + mRooms[i]->getPosition().second * (mTinyMapHeight / mMazeHeight)),
			mTinyMapWidth / mMazeWidth,
			mTinyMapHeight / mMazeHeight },
			1,
			Fade(BLACK, 0.5f));

		if (mRooms[i]->getDoors() & ROOM_DOOR_TOP) {
			DrawRectangle(
				(mTinyMapOffset.x + mRooms[i]->getPosition().first * (mTinyMapWidth / mMazeWidth)) + ((mTinyMapWidth / mMazeWidth) / 2) - 2.0f,
				mTinyMapOffset.y + mRooms[i]->getPosition().second * (mTinyMapHeight / mMazeHeight),
				4.0f,
				4.0f,
				Fade(BLACK, 0.7f));
		}

		if (mRooms[i]->getDoors() & ROOM_DOOR_LEFT) {
			DrawRectangle(
				mTinyMapOffset.x + mRooms[i]->getPosition().first * (mTinyMapWidth / mMazeWidth),
				(mTinyMapOffset.y + mRooms[i]->getPosition().second * (mTinyMapHeight / mMazeHeight)) + ((mTinyMapHeight / mMazeHeight) / 2) - 2.0f,
				4.0f,
				4.0f,
				Fade(BLACK, 0.7f));
		}

		if (mRooms[i]->getDoors() & ROOM_DOOR_RIGHT) {
			DrawRectangle(
				(mTinyMapOffset.x + mRooms[i]->getPosition().first * (mTinyMapWidth / mMazeWidth)) + (mTinyMapWidth / mMazeWidth) - 4.0f,
				(mTinyMapOffset.y + mRooms[i]->getPosition().second * (mTinyMapHeight / mMazeHeight)) + ((mTinyMapHeight / mMazeHeight) / 2) - 2.0f,
				4.0f,
				4.0f,
				Fade(BLACK, 0.7f));
		}

		if (mRooms[i]->getDoors() & ROOM_DOOR_BOTTOM) {
			DrawRectangle(
				(mTinyMapOffset.x + mRooms[i]->getPosition().first * (mTinyMapWidth / mMazeWidth)) + ((mTinyMapWidth / mMazeWidth) / 2) - 2.0f,
				(mTinyMapOffset.y + mRooms[i]->getPosition().second * (mTinyMapHeight / mMazeHeight)) + (mTinyMapHeight / mMazeHeight) - 4.0f,
				4.0f,
				4.0f,
				Fade(BLACK, 0.7f));
		}

	}

}

void Level::generateMaze() {
	mMaze = new int[mMazeWidth * mMazeHeight];
	
	//fill mMaze with 0;
	memset(mMaze, 0x00, mMazeWidth * mMazeHeight * sizeof(int));

	mRooms.clear();

	//Choose a random position for the first room.
	mCurrentRoom = generateRoom(make_pair(rand() % mMazeWidth, rand() % mMazeHeight));

	mRooms.push_back(mCurrentRoom);
	mMaze[mCurrentRoom->getPosition().second * mMazeWidth + mCurrentRoom->getPosition().first] |= ROOM_VISITED;

	createRooms(mCurrentRoom->getPosition());

	// Set doors for our Rooms
	for (auto lRoom : mRooms) {
		lRoom->setDoors(mMaze[lRoom->getPosition().second * mMazeWidth + lRoom->getPosition().first]);
		printf("\nPosition: (%d, %d) Doors: %d", lRoom->getPosition().first, lRoom->getPosition().second, lRoom->getDoors());
	}

	findFarestRoom();
}

void Level::createRooms(pair<int, int> aPosition) {
	// Little lambda function to calculate index in a readable way
	auto offset = [&](int x, int y)
	{
		return (aPosition.second + y) * mMazeWidth + (aPosition.first + x);
	};

	vector<int> lNeighbours = this->getNeighbours(aPosition, false);

	// Are there any neighbours available?
	if (!lNeighbours.empty()) {
		// Choose one available neighbour at random
		int lNextCellDirection = lNeighbours[rand() % lNeighbours.size()];

		World* lNewRoom;
		// Create a path between the neighbour and the current cell
		switch (lNextCellDirection) {
		case 0: // North
			mMaze[offset(0, -1)] |= ROOM_VISITED | ROOM_DOOR_BOTTOM;
			mMaze[offset(0, 0)] |= ROOM_DOOR_TOP;
			lNewRoom = generateRoom(make_pair((aPosition.first + 0), (aPosition.second - 1)));
			break;

		case 1: // East
			mMaze[offset(+1, 0)] |= ROOM_VISITED | ROOM_DOOR_LEFT;
			mMaze[offset(0, 0)] |= ROOM_DOOR_RIGHT;
			lNewRoom = generateRoom(make_pair((aPosition.first + 1), (aPosition.second + 0)));
			break;

		case 2: // South
			mMaze[offset(0, +1)] |= ROOM_VISITED | ROOM_DOOR_TOP;
			mMaze[offset(0, 0)] |= ROOM_DOOR_BOTTOM;
			lNewRoom = generateRoom(make_pair((aPosition.first + 0), (aPosition.second + 1)));
			break;

		case 3: // West
			mMaze[offset(-1, 0)] |= ROOM_VISITED | ROOM_DOOR_RIGHT;
			mMaze[offset(0, 0)] |= ROOM_DOOR_LEFT;
			lNewRoom = generateRoom(make_pair((aPosition.first - 1), (aPosition.second + 0)));
			break;
		}

		if (&lNewRoom != NULL) {
			mRooms.push_back(lNewRoom);
		}

		lNeighbours.clear();
	}

	if (mRooms.size() < mRoomNumber) {

		pair<int, int> lNewCase;

		int lMaxNeighbours = 0;
		int lMaxNeighboursAt = 0;
		vector<int> lNeighboursAt;

		for (int i = 0; i < mRooms.size(); i++) {
			lNeighboursAt = getNeighbours(mRooms[i]->getPosition(), false);
			if (lNeighboursAt.size() >= lMaxNeighbours)	{
				lMaxNeighbours = lNeighboursAt.size();
				lMaxNeighboursAt = i;
			}	
		}

		int lRandomChoice = rand() % 10;

		if (lRandomChoice % 2 == 0)
			lNewCase = mRooms[lMaxNeighboursAt]->getPosition();
		else 
			lNewCase = mRooms[rand() % mRooms.size()]->getPosition();

		createRooms(make_pair(lNewCase.first, lNewCase.second));
	}
}

	World* Level::generateRoom(pair<int, int> aPosition) {
	World* lRoom = new World(aPosition, mTileset, mLayers);
	lRoom->setCollisionTiles(mTileCollisions);
	lRoom->setCollisionDoors(mDoorCollisions);
	return lRoom;
}

vector<int> Level::getNeighbours(pair<int, int> aPosition, bool aVisited)
{
	// Little lambda function to calculate index in a readable way
	auto offset = [&](int x, int y)	{
		return (aPosition.second + y) * mMazeWidth + (aPosition.first + x);
	};

	vector<int> lNeighbours;

	// North neighbour
	if (aPosition.second > 0)
		if ((mMaze[offset(0, -1)] & ROOM_VISITED) == aVisited)
			lNeighbours.push_back(0);

	// East neighbour
	if (aPosition.first < mMazeWidth - 1)
		if ((mMaze[offset(1, 0)] & ROOM_VISITED) == aVisited)
			lNeighbours.push_back(1);

	// South neighbour
	if (aPosition.second < mMazeHeight - 1)
		if ((mMaze[offset(0, 1)] & ROOM_VISITED) == aVisited)
			lNeighbours.push_back(2);

	// West neighbour
	if (aPosition.first > 0)
		if ((mMaze[offset(-1, 0)] & ROOM_VISITED) == aVisited)
			lNeighbours.push_back(3);

	return lNeighbours;
}

vector<stack<pair<int, int>>> Level::findAllPaths() {
	stack<pair<int, int>> lStack;
	vector<int> lDoors;
	set<pair<int, int>> lVisitedCase;
	vector<stack<pair<int, int>>> lAllPaths;
	stack<pair<int, int>> lPath;
	int* lTempMaze = new int[mMazeWidth * mMazeHeight];
	memset(lTempMaze, 0x00, mMazeWidth * mMazeHeight * sizeof(int));;

	for (auto lRoom : mRooms)
		lTempMaze[lRoom->getPosition().second * mMazeWidth + lRoom->getPosition().first] = mMaze[lRoom->getPosition().second * mMazeWidth + lRoom->getPosition().first];

	lStack.push(mRooms[0]->getPosition());
	lPath.push(lStack.top());
	lVisitedCase.insert(mRooms[0]->getPosition());

	while (lVisitedCase.size() < mRooms.size())	{		
		printf("\n(%d, %d) : ", lStack.top().first, lStack.top().second);
		for (int i = 0; i < lDoors.size(); i++)
			printf("\n%d  ", lDoors.at(i));

		lDoors = getRoomDoors(lTempMaze, lStack.top());

		if (!lDoors.empty())
		{
			// Choose one available neighbour at random
			int lNextCellDirection = lDoors[rand() % lDoors.size()];

			switch (lNextCellDirection)
			{
			case 0: // North
				lTempMaze[lStack.top().second * mMazeWidth + lStack.top().first] -= ROOM_DOOR_TOP;
				lStack.push(make_pair((lStack.top().first + 0), (lStack.top().second - 1)));
				lTempMaze[lStack.top().second * mMazeWidth + lStack.top().first] -= ROOM_DOOR_BOTTOM;
				break;

			case 1: // East
				lTempMaze[lStack.top().second * mMazeWidth + lStack.top().first] -= ROOM_DOOR_RIGHT;
				lStack.push(make_pair((lStack.top().first + 1), (lStack.top().second + 0)));
				lTempMaze[lStack.top().second * mMazeWidth + lStack.top().first] -= ROOM_DOOR_LEFT;
				break;

			case 2: // South
				lTempMaze[lStack.top().second * mMazeWidth + lStack.top().first] -= ROOM_DOOR_BOTTOM;
				lStack.push(make_pair((lStack.top().first + 0), (lStack.top().second + 1)));
				lTempMaze[lStack.top().second * mMazeWidth + lStack.top().first] -= ROOM_DOOR_TOP;
				break;

			case 3: // West
				lTempMaze[lStack.top().second * mMazeWidth + lStack.top().first] -= ROOM_DOOR_LEFT;
				lStack.push(make_pair((lStack.top().first - 1), (lStack.top().second + 0)));
				lTempMaze[lStack.top().second * mMazeWidth + lStack.top().first] -= ROOM_DOOR_RIGHT;
				break;
			}

			lPath.push(lStack.top());

			if (getRoomDoors(lTempMaze, lStack.top()).empty()) {
				lAllPaths.push_back(lStack);
			}				

			lVisitedCase.insert(lStack.top());
		}
		else {
			lPath.pop();
			lStack.pop();			
		}		

		lDoors.clear();
	} 

	printf("\nNb of path = %d", lAllPaths.size());
	for (int i = 0; i < lAllPaths.size(); i++)
		printf("\n%d : %d", i, lAllPaths.at(i).size());

	delete lTempMaze;
	return lAllPaths;
}

void Level::findFarestRoom() {
	vector<stack<pair<int, int>>> lAllPaths = this->findAllPaths();
	int lMax = 0;
	for (int i = 0; i < lAllPaths.size(); i++) 
	{
		if (lMax < lAllPaths.at(i).size()) {
			lMax = lAllPaths.at(i).size();
			mFarestRoom = lAllPaths.at(i).top();
		}
	}
	printf("\n Farest case: (%d, %d)", mFarestRoom.first, mFarestRoom.second);
}

vector<int> Level::getRoomDoors(int* aMaze, pair<int, int> aPosition) {
	vector<int> lDoors;
	if (aMaze[aPosition.second * mMazeWidth + aPosition.first] & ROOM_DOOR_TOP)
		lDoors.push_back(0);

	if (aMaze[aPosition.second * mMazeWidth + aPosition.first] & ROOM_DOOR_RIGHT)
		lDoors.push_back(1);

	if (aMaze[aPosition.second * mMazeWidth + aPosition.first] & ROOM_DOOR_BOTTOM)
		lDoors.push_back(2);

	if (aMaze[aPosition.second * mMazeWidth + aPosition.first] & ROOM_DOOR_LEFT)
		lDoors.push_back(3);

	return lDoors;
}

void Level::nextRoom(int aDoor) {
	if (mCurrentRoom->getDoors() & aDoor) {
		pair<int, int> lNewPosition;
		switch (aDoor) {
		case ROOM_DOOR_TOP:
			lNewPosition = make_pair(mCurrentRoom->getPosition().first, mCurrentRoom->getPosition().second - 1);
			break;
		case ROOM_DOOR_RIGHT:
			lNewPosition = make_pair(mCurrentRoom->getPosition().first + 1, mCurrentRoom->getPosition().second);
			break;
		case ROOM_DOOR_LEFT:
			lNewPosition = make_pair(mCurrentRoom->getPosition().first - 1, mCurrentRoom->getPosition().second);
			break;
		case ROOM_DOOR_BOTTOM:
			lNewPosition = make_pair(mCurrentRoom->getPosition().first, mCurrentRoom->getPosition().second + 1);
			break;
		}

		for (auto lRoom : mRooms) {
			if (lRoom->getPosition().first == lNewPosition.first && lRoom->getPosition().second == lNewPosition.second) {
				mCurrentRoom = lRoom;
				break;
			}
		}
	}
}

Level::Level() {}
Level::~Level() {}
