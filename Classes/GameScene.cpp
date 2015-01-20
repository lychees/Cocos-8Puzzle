#include "GameScene.h"
#include "MainLayer.h"
#include "ConstValue.h"

USING_NS_CC;

bool GameScene::init() {
	if (!Scene::init()) {
		return false;
	}

	this->initWithPhysics();
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(0, GRAVITY_Y));

	auto mainLayer = MainLayer::create();
	this->addChild(mainLayer);

	mainLayer->initContent();

	return true;
}
