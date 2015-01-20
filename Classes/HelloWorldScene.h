#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace std;
USING_NS_CC;

class MainMenu : public Layer
{
public:
    static cocos2d::Scene* createScene();    
	void menuCallbackStart(Ref*);
	void menuCallbackOption(Ref*);
	void menuCallbackExit(Ref*);
	CREATE_FUNC(MainMenu ); virtual bool init();
};

class Puzzle : public Layer{
public:
	vector<int> A; vector<Sprite*> B; // 记录每个格子是哪张图片。	
	vector<Vec2> P; // 每个格子的实际位置。
	int blank; // 记录空格的位置
	
	void onKeyPressed(EventKeyboard::KeyCode, Event*);
	bool Done();
	void Swap(int, int);
	CREATE_FUNC(Puzzle); virtual bool init();
};


class Game : public Scene{
public:	
	
	void restart();
	CREATE_FUNC(Game); virtual bool init();
};


#endif // __HELLOWORLD_SCENE_H__
