#include "TestTileMap.h"

USING_NS_CC;

Scene* TestTileMap::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = TestTileMap::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
} 

// on "init" you need to initialize your instance
bool TestTileMap::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	std::string file = "tilemap.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	_tileMap = TMXTiledMap::createWithXML(str->getCString(), "");
	_background = _tileMap->layerNamed("Background");

	addChild(_tileMap, -1);

	return true;
}
