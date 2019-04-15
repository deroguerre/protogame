//#include "WorldMapScene.h"
//#include "SceneManager/SceneManager.h"
//#include "Globals.h"
//#include "World.h"
//#include <charconv>
//#include "Level.h"
//#include "Player.h"
//
//World* objWorld;
//Player* mPlayer;
//
//WorldMapScene::WorldMapScene()
//{
//	Texture2D lTileset = LoadTexture("assets/overworld_tileset_grass.png");
//
//	std::vector<std::string> lLayers = {
//		"maps/world-map_Calque1.csv",
//		"maps/world-map_Calque2.csv",
//		"maps/world-map_Calque3.csv"
//	};
//
//	std::pair<int, int> aPosition = { 0,0 };
//
//	objWorld = new World(aPosition, lTileset, lLayers, 16);
//
//	mPlayer = new Player(Vector2{ Globals::SCREEN_WIDTH / 2, Globals::SCREEN_HEIGHT / 2 });
//}
//
//
//WorldMapScene::~WorldMapScene() {
//}
//
//void WorldMapScene::load() {
//}
//
//void WorldMapScene::update() {
//	mPlayer->update(GetFrameTime());
//}
//
//void WorldMapScene::draw() {
//	objWorld->draw();
//	mPlayer->draw();
//}
//
//void WorldMapScene::unload() {
//}
