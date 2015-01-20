#include "cocos2d.h"

const int GRID_SIZE = 3;
const float LOCAL_VIEW_SCALE = 2.5;
const float GRID_WIDTH = 200;
const float GRID_HEIGHT = 200;

const float VIEW_WIDTH = GRID_WIDTH * GRID_SIZE;
const float VIEW_HEIGHT = GRID_WIDTH * GRID_SIZE;

const int ColliderTypePlayer = 1;
const int ColliderTypeBlock = 2;
const cocos2d::PhysicsMaterial PHYSICSBODY_MATERIAL_PLAYER(0.1f, 0.0f, 0.0f);
const cocos2d::PhysicsMaterial PHYSICSBODY_MATERIAL_BLOCK(0.1f, 0.0f, 0.0f);
const float GRAVITY_Y = -1000;
const float JUMP_SPEED_Y = 600;
const float RUN_SPEED_X = 200;
