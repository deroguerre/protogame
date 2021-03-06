#include "Level.h"

int mTinyMapWidth = 128;
int mTinyMapHeight = 96;
Vector2 mTinyMapOffset;

Texture2D lTileset;

Level::Level(int aRoomNumber, const char* aTilemap) {

	lTileset = LoadTexture("assets/room_tileset.png");

	mMazeWidth = (int)sqrt(aRoomNumber) + 1;
	mMazeHeight = (int)sqrt(aRoomNumber) + 1;
	mRoomNumber = aRoomNumber;
	mTinyMapOffset = { (float)Globals::SCREEN_WIDTH - (float)mTinyMapWidth, 0.0f };

	mTilemap = aTilemap;
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
	//DrawRectangle(mTinyMapOffset.x, mTinyMapOffset.y, mTinyMapWidth, mTinyMapHeight, Fade(RAYWHITE, 0.4f));
	DrawRectangleLines((int)mTinyMapOffset.x, (int)mTinyMapOffset.y, mTinyMapWidth, mTinyMapHeight, Fade(BLACK, 0.5f));

	for (unsigned int i = 0; i < mRooms.size(); i++) {

		DrawRectangle(
			((int)mTinyMapOffset.x + mRooms[i]->getRoomPosition().first * (mTinyMapWidth / mMazeWidth)),
			((int)mTinyMapOffset.y + mRooms[i]->getRoomPosition().second * (mTinyMapHeight / mMazeHeight)),
			mTinyMapWidth / mMazeWidth,
			mTinyMapHeight / mMazeHeight,
			Fade(DARKGRAY, 0.4f));

		DrawRectangle(
			((int)mTinyMapOffset.x + mFarestRoom.first * (mTinyMapWidth / mMazeWidth)),
			((int)mTinyMapOffset.y + mFarestRoom.second * (mTinyMapHeight / mMazeHeight)),
			mTinyMapWidth / mMazeWidth,
			mTinyMapHeight / mMazeHeight,
			Fade(RED, 0.1f));

		DrawRectangle(
			((int)mTinyMapOffset.x + mRooms[0]->getRoomPosition().first * (mTinyMapWidth / mMazeWidth)),
			((int)mTinyMapOffset.y + mRooms[0]->getRoomPosition().second * (mTinyMapHeight / mMazeHeight)),
			mTinyMapWidth / mMazeWidth,
			mTinyMapHeight / mMazeHeight,
			Fade(DARKGREEN, 0.1f));

		DrawRectangle(
			((int)mTinyMapOffset.x + mCurrentRoom->getRoomPosition().first * (mTinyMapWidth / mMazeWidth)),
			((int)mTinyMapOffset.y + mCurrentRoom->getRoomPosition().second * (mTinyMapHeight / mMazeHeight)),
			mTinyMapWidth / mMazeWidth,
			mTinyMapHeight / mMazeHeight,
			Fade(RAYWHITE, 0.1f));


		Rectangle lRectangle = {
			(mTinyMapOffset.x + (float)(mRooms[i]->getRoomPosition().first * (mTinyMapWidth / mMazeWidth))),
			(mTinyMapOffset.y + (float)(mRooms[i]->getRoomPosition().second * (mTinyMapHeight / mMazeHeight))),
			(float)mTinyMapWidth / (float)mMazeWidth,
			(float)mTinyMapHeight / (float)mMazeHeight
		};
		DrawRectangleLinesEx(lRectangle, 1, Fade(RAYWHITE, 0.5f));

		if (mRooms[i]->getDoors() & ROOM_DOOR_TOP) {
			DrawRectangle(
				((int)mTinyMapOffset.x + mRooms[i]->getRoomPosition().first * (mTinyMapWidth / mMazeWidth)) + ((mTinyMapWidth / mMazeWidth) / 2) - 2,
				(int)mTinyMapOffset.y + mRooms[i]->getRoomPosition().second * (mTinyMapHeight / mMazeHeight),
				4,
				4,
				Fade(BLACK, 0.7f));
		}

		if (mRooms[i]->getDoors() & ROOM_DOOR_LEFT) {
			DrawRectangle(
				(int)mTinyMapOffset.x + mRooms[i]->getRoomPosition().first * (mTinyMapWidth / mMazeWidth),
				((int)mTinyMapOffset.y + mRooms[i]->getRoomPosition().second * (mTinyMapHeight / mMazeHeight)) + ((mTinyMapHeight / mMazeHeight) / 2) - 2,
				4,
				4,
				Fade(BLACK, 0.7f));
		}

		if (mRooms[i]->getDoors() & ROOM_DOOR_RIGHT) {
			DrawRectangle(
				((int)mTinyMapOffset.x + mRooms[i]->getRoomPosition().first * (mTinyMapWidth / mMazeWidth)) + (mTinyMapWidth / mMazeWidth) - 4,
				((int)mTinyMapOffset.y + mRooms[i]->getRoomPosition().second * (mTinyMapHeight / mMazeHeight)) + ((mTinyMapHeight / mMazeHeight) / 2) - 2,
				4,
				4,
				Fade(BLACK, 0.7f));
		}

		if (mRooms[i]->getDoors() & ROOM_DOOR_BOTTOM) {
			DrawRectangle(
				((int)mTinyMapOffset.x + mRooms[i]->getRoomPosition().first * (mTinyMapWidth / mMazeWidth)) + ((mTinyMapWidth / mMazeWidth) / 2) - 2,
				((int)mTinyMapOffset.y + mRooms[i]->getRoomPosition().second * (mTinyMapHeight / mMazeHeight)) + (mTinyMapHeight / mMazeHeight) - 4,
				4,
				4,
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
	mCurrentRoom = new Room(mTilemap, lTileset, make_pair(rand() % mMazeWidth, rand() % mMazeHeight));

	mRooms.push_back(mCurrentRoom);
	mMaze[mCurrentRoom->getRoomPosition().second * mMazeWidth + mCurrentRoom->getRoomPosition().first] |= ROOM_VISITED;

	createRooms(mCurrentRoom->getRoomPosition());

	// Set doors for our Rooms and load map
	for (auto lRoom : mRooms) {
		lRoom->setDoors(mMaze[lRoom->getRoomPosition().second * mMazeWidth + lRoom->getRoomPosition().first]);
		//lRoom->loadMap();
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

		// Create a path between the neighbour and the current cell
		switch (lNextCellDirection) {
		case 0: // North
			mMaze[offset(0, -1)] |= ROOM_VISITED | ROOM_DOOR_BOTTOM;
			mMaze[offset(0, 0)] |= ROOM_DOOR_TOP;
			mRooms.push_back(new Room(mTilemap, lTileset, make_pair((aPosition.first + 0), (aPosition.second - 1))));
			break;

		case 1: // East
			mMaze[offset(+1, 0)] |= ROOM_VISITED | ROOM_DOOR_LEFT;
			mMaze[offset(0, 0)] |= ROOM_DOOR_RIGHT;
			mRooms.push_back(new Room(mTilemap, lTileset, make_pair((aPosition.first + 1), (aPosition.second + 0))));
			break;

		case 2: // South
			mMaze[offset(0, +1)] |= ROOM_VISITED | ROOM_DOOR_TOP;
			mMaze[offset(0, 0)] |= ROOM_DOOR_BOTTOM;
			mRooms.push_back(new Room(mTilemap, lTileset, make_pair((aPosition.first + 0), (aPosition.second + 1))));
			break;

		case 3: // West
			mMaze[offset(-1, 0)] |= ROOM_VISITED | ROOM_DOOR_RIGHT;
			mMaze[offset(0, 0)] |= ROOM_DOOR_LEFT;
			mRooms.push_back(new Room(mTilemap, lTileset, make_pair((aPosition.first - 1), (aPosition.second + 0))));
			break;
		}

		lNeighbours.clear();
	}

	if (mRooms.size() < mRoomNumber) {

		pair<int, int> lNewCase;

		unsigned int lMaxNeighbours = 0;
		int lMaxNeighboursAt = 0;
		vector<int> lNeighboursAt;

		for (unsigned int i = 0; i < mRooms.size(); i++) {
			lNeighboursAt = getNeighbours(mRooms[i]->getRoomPosition(), false);
			if (lNeighboursAt.size() >= lMaxNeighbours) {
				lMaxNeighbours = lNeighboursAt.size();
				lMaxNeighboursAt = i;
			}
		}

		int lRandomChoice = rand() % 10;

		if (lRandomChoice % 2 == 0)
			lNewCase = mRooms[lMaxNeighboursAt]->getRoomPosition();
		else
			lNewCase = mRooms[rand() % mRooms.size()]->getRoomPosition();

		createRooms(make_pair(lNewCase.first, lNewCase.second));
	}
}

vector<int> Level::getNeighbours(pair<int, int> aPosition, bool aVisited)
{
	// Little lambda function to calculate index in a readable way
	auto offset = [&](int x, int y) {
		return (aPosition.second + y) * mMazeWidth + (aPosition.first + x);
	};

	vector<int> lNeighbours;

	// North neighbour
	if (aPosition.second > 0)
		if ((mMaze[offset(0, -1)] & ROOM_VISITED) == (int)aVisited)
			lNeighbours.push_back(0);

	// East neighbour
	if (aPosition.first < mMazeWidth - 1)
		if ((mMaze[offset(1, 0)] & ROOM_VISITED) == (int)aVisited)
			lNeighbours.push_back(1);

	// South neighbour
	if (aPosition.second < mMazeHeight - 1)
		if ((mMaze[offset(0, 1)] & ROOM_VISITED) == (int)aVisited)
			lNeighbours.push_back(2);

	// West neighbour
	if (aPosition.first > 0)
		if ((mMaze[offset(-1, 0)] & ROOM_VISITED) == (int)aVisited)
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
		lTempMaze[lRoom->getRoomPosition().second * mMazeWidth + lRoom->getRoomPosition().first] = mMaze[lRoom->getRoomPosition().second * mMazeWidth + lRoom->getRoomPosition().first];

	lStack.push(mRooms[0]->getRoomPosition());
	lPath.push(lStack.top());
	lVisitedCase.insert(mRooms[0]->getRoomPosition());

	while (lVisitedCase.size() < mRooms.size()) {

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

	delete lTempMaze;
	return lAllPaths;
}

void Level::findFarestRoom() {
	vector<stack<pair<int, int>>> lAllPaths = this->findAllPaths();
	unsigned int lMax = 0;
	for (unsigned int i = 0; i < lAllPaths.size(); i++)
	{
		if (lMax < lAllPaths.at(i).size()) {
			lMax = lAllPaths.at(i).size();
			mFarestRoom = lAllPaths.at(i).top();
		}
	}
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
			lNewPosition = make_pair(mCurrentRoom->getRoomPosition().first, mCurrentRoom->getRoomPosition().second - 1);
			break;
		case ROOM_DOOR_RIGHT:
			lNewPosition = make_pair(mCurrentRoom->getRoomPosition().first + 1, mCurrentRoom->getRoomPosition().second);
			break;
		case ROOM_DOOR_LEFT:
			lNewPosition = make_pair(mCurrentRoom->getRoomPosition().first - 1, mCurrentRoom->getRoomPosition().second);
			break;
		case ROOM_DOOR_BOTTOM:
			lNewPosition = make_pair(mCurrentRoom->getRoomPosition().first, mCurrentRoom->getRoomPosition().second + 1);
			break;
		}

		for (auto lRoom : mRooms) {
			if (lRoom->getRoomPosition().first == lNewPosition.first && lRoom->getRoomPosition().second == lNewPosition.second) {
				mCurrentRoom = lRoom;
				break;
			}
		}
	}
}

Level::Level() {}
Level::~Level() {}
