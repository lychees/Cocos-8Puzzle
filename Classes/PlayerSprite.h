#pragma once

#include "cocos2d.h"

class PlayerSprite : public cocos2d::Sprite {
public:
	enum class RunState {
		Idle,
		RunLeft,
		RunRight
	};

	virtual bool init();
	CREATE_FUNC(PlayerSprite);

	int timeCount;

	Sprite* sprite;
	RunState runState;
	float speedX;
	bool isJumping;

	int gridX;
	int gridY;

	void addPhysicsBody();
	void setVelocity(cocos2d::Vec2 v);
	void moveGridPosition(int dir);

	void update(float dt);
};