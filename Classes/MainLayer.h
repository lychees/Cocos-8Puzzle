#pragma once

#include "cocos2d.h"
#include "GridLayer.h"
#include "PlayerSprite.h"

class MainLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(MainLayer);

	PlayerSprite* _playerSprite;
	cocos2d::Vector<GridLayer*> _gridLayers;

	void createGideLayers();
	void createPlayerSprite();

	void initContent();

	int _emptyGridX;
	int _emptyGridY;
	void setEmptyGrid(int x, int y);
	void moveEmptyGrid(int dir);

	bool isFullView;
	void setLocalView();
	void setFullView();
	void setPlayerView();

	cocos2d::Vec2 findObjPosition(const char* name);

	void listenKeyboardEvent();
	void onKeyPressed2(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* evt);
	void onKeyReleased2(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* evt);

	void setIsFullView(bool flag);
	void update(float dt);
};