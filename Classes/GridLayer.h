#pragma once

#include "cocos2d.h"

class GridLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GridLayer);

	int _index;
	int _gridX;
	int _gridY;

	cocos2d::TMXTiledMap* _map;

	bool findObjPosition(const char *name, cocos2d::Vec2 &res);

	void initContent(int index);
	void setGridPosition(int x, int y);
	void moveGridPosition(int dir);
};