#include "GridLayer.h"
#include "ConstValue.h"
USING_NS_CC;

bool GridLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	
	return true;
}

void GridLayer::setGridPosition(int x, int y) {
	this->_gridX = x;
	this->_gridY = y;
	y = GRID_SIZE - y - 1;
	this->setPosition(x * GRID_WIDTH, y * GRID_HEIGHT);
}

void GridLayer::initContent(int index) {
	this->setContentSize(Size(GRID_WIDTH, GRID_HEIGHT));
	this->setAnchorPoint(ccp(0, 0));
	this->_index = index;
	
	char filePath[100];
	sprintf_s(filePath, "map/map%d.tmx", index % 2);
	this->_map = TMXTiledMap::create(filePath);

	auto objectGroup = this->_map->objectGroupNamed("block")->getObjects();
	for (auto& obj : objectGroup) {
		ValueMap& dict = obj.asValueMap();
		float x = dict["x"].asFloat();
		float y = dict["y"].asFloat();
		float width = dict["width"].asFloat();
		float height = dict["height"].asFloat();
		auto body = PhysicsBody::createBox(Size(width, height), PHYSICSBODY_MATERIAL_BLOCK);
		body->setCategoryBitmask(ColliderTypeBlock);
		body->setCollisionBitmask(ColliderTypePlayer);
		body->setContactTestBitmask(ColliderTypePlayer);
		body->setDynamic(false);
		body->setLinearDamping(0.0f);

		auto edgeNode = Sprite::create();
		edgeNode->setPosition(Point(x + width / 2, y + height / 2));
		edgeNode->setPhysicsBody(body);
		this->addChild(edgeNode);
	}

	this->addChild(this->_map);
}

bool GridLayer::findObjPosition(const char *name, cocos2d::Vec2 &res) {
	auto objectGroup = this->_map->objectGroupNamed(name)->getObjects();
	if (objectGroup.size() > 0) {
		auto dict = objectGroup[0].asValueMap();
		float x = dict["x"].asFloat();
		float y = dict["y"].asFloat();
		res = ccp(x, y);
		return true;
	}
	else
		return false;
}

void GridLayer::moveGridPosition(int dir) {
	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, 1, -1 };
	float posX = this->getPositionX() + dx[dir] * GRID_WIDTH;
	float posY = this->getPositionY() - dy[dir] * GRID_HEIGHT;
	auto moveTo = MoveTo::create(0.3, Vec2(posX, posY));
	this->runAction(moveTo);
	this->_gridX += dx[dir];
	this->_gridY += dy[dir];
}