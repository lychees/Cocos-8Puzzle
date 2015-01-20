#include "PlayerSprite.h"
#include "MainLayer.h"
#include "ConstValue.h"
#include "cmath"

USING_NS_CC;

bool PlayerSprite::init() {
	if (!Sprite::init()) {
		return false;
	}

	this->timeCount = 0;
	this->speedX = RUN_SPEED_X;
	this->runState = RunState::Idle;

	sprite = Sprite::create("player.png");
	this->addPhysicsBody();
	this->addChild(sprite);

	return true;
}

void PlayerSprite::update(float dt) {
	float vy = this->getPhysicsBody()->getVelocity().y;
	if (std::fabs(vy) < 1e-3)
		this->isJumping = false;
	else
		this->isJumping = true;

	this->gridX = (int)this->getPositionX() / GRID_WIDTH;
	this->gridY = GRID_SIZE - 1 - int(this->getPositionY() / GRID_HEIGHT);

	timeCount++;
	if (timeCount % 10 != 0)
		return;
	if (this->runState == RunState::RunRight) {
		this->getPhysicsBody()->setVelocity(Vec2(speedX, vy));
	}
	else if (this->runState == RunState::RunLeft) {
		this->getPhysicsBody()->setVelocity(Vec2(-speedX, vy));
	}
	else if (this->runState == RunState::Idle) {
		this->getPhysicsBody()->setVelocity(Vec2(0, vy));
	}
}

void PlayerSprite::setVelocity(Vec2 v) {
	this->getPhysicsBody()->setVelocity(v);
}

void PlayerSprite::addPhysicsBody() {
	PhysicsBody *body = PhysicsBody::createBox(Size(20, 20), PHYSICSBODY_MATERIAL_PLAYER);
	body->setDynamic(true);
	body->setCategoryBitmask(ColliderTypePlayer);
	body->setContactTestBitmask(ColliderTypeBlock);
	body->setRotationEnable(false);
	body->setLinearDamping(0.0f);
	body->setGravityEnable(true);
	this->setPhysicsBody(body);
}

void PlayerSprite::moveGridPosition(int dir) {
	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, 1, -1 };
	float posX = this->getPositionX() + dx[dir] * GRID_WIDTH;
	float posY = this->getPositionY() - dy[dir] * GRID_HEIGHT;
	auto moveTo = MoveTo::create(0.3, Vec2(posX, posY));
	this->runAction(moveTo);
	this->gridX += dx[dir];
	this->gridY += dy[dir];
	//this->setPosition(Vec2(posX, posY));
}
