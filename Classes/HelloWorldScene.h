#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace std;
USING_NS_CC;

class MainMenu : public Layer
{
public:
    
	
	static Scene* createScene();    
	
	void menuCallbackStart(Ref*);
	void menuCallbackOption(Ref*);
	void menuCallbackExit(Ref*);	

	int focus; Label* Fo;
	void onKeyPressed(EventKeyboard::KeyCode, Event*);


	CREATE_FUNC(MainMenu ); virtual bool init();
};

class Puzzle : public Layer{
public:

	int w, h, n;  // ��¼����߷ָ�ķ���������һ���ж��ٸ�����
	int ww, hh; // ��¼ÿ�����ӵĿ����

	vector<int> A; vector<Sprite*> B; // ��¼ÿ������������ͼƬ��	


	vector<Vec2> P; // ÿ�����ӵ�ʵ��λ�á�
	int blank; // ��¼�ո��λ��
	
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
