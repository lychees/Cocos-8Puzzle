#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ConvertUTF.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace std;

#define REP(i, n) for (int i=0;i<n;++i)
#define FOR(i, a, b) for (int i=a;i<b;++i)
#define DWN(i, b, a) for (int i=b-1;i>=a;--i)
typedef vector<int> VI;



// 菜单

Scene* MainMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = MainMenu::create();
	scene->addChild(layer);

	// return the scene
	return scene;
}




void MainMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){

	//CCLOG("Key with keycode %d pressed", keyCode);

	if (keyCode == EventKeyboard::KeyCode::KEY_W){	
		
		if (point>1)
		{
			Fo->runAction(MoveBy::create(0.1, Vec2(0, 50) ));
			SimpleAudioEngine::getInstance()->playEffect("sound/pinu_koke.wav");
			point-=1;
		}
		

	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S){
		if (point<3)
		{
			Fo->runAction(MoveBy::create(0.1, Vec2(0, -50) ));
			SimpleAudioEngine::getInstance()->playEffect("sound/pinu_koke.wav");
			point+=1;
		}
		
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE || keyCode == EventKeyboard::KeyCode::KEY_ENTER){
		
		SimpleAudioEngine::getInstance()->playEffect("sound/2-69-se-2.wav");		
		if (point==1)
		{
			SimpleAudioEngine::getInstance()->playEffect("sound/选择.wav");
			Director::getInstance()->replaceScene(Game::create());
		}
		else
			if (point==2)
			{
				
			}
			else
				if(point==3)
				{
					Director::getInstance()->end();
				}
	}
}

bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	point = 1;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto l1 = Label::createWithTTF(   GBKToUTF8("Start 开始"), "fonts/Marker Felt.ttf", 32);        
	auto ll1 = MenuItemLabel::create(l1, CC_CALLBACK_1(MainMenu::menuCallbackStart, this));
	ll1->setPosition(Vec2(0, -0));
	ll1->setName("Start");

	auto l2 = Label::createWithTTF("Option", "fonts/Marker Felt.ttf", 32);	
	auto ll2 = MenuItemLabel::create(l2, CC_CALLBACK_1(MainMenu::menuCallbackOption, this));
	ll2->setPosition(Vec2(0, -50));
	ll2->setName("Option");

	auto l3 = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 32);	
	auto ll3 = MenuItemLabel::create(l3, CC_CALLBACK_1(MainMenu::menuCallbackExit, this));
	ll3->setPosition(Vec2(0, -100));
	ll3->setName("Exit");
    
	auto menu = Menu::create(ll1, ll2, ll3, NULL);
	addChild(menu);

	focus = 0;

	Fo = Label::createWithTTF("?", "fonts/Marker Felt.ttf", 32);	
	Fo->setPosition(Vec2( origin.x + visibleSize.width / 2 - 80,  origin.y + visibleSize.height / 2));
	Fo->setName("Focus");

	addChild(Fo);

	auto e = EventListenerKeyboard::create();
	e->onKeyPressed = CC_CALLBACK_2(MainMenu::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(e, this);;

    return true;
}

void MainMenu::menuCallbackStart(Ref* p)
{
	//auto t = Game::create();

	SimpleAudioEngine::getInstance()->playEffect("sound/选择.wav");


	Director::getInstance()->replaceScene(Game::create());
}
void MainMenu::menuCallbackOption(Ref* p)
{

}
void MainMenu::menuCallbackExit(Ref* p)
{
	Director::getInstance()->end();
}

void Puzzle::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){

	//CCLOG("Key with keycode %d pressed", keyCode);

	if (keyCode == EventKeyboard::KeyCode::KEY_W){
		if (blank % h != 0) 
			{
				Swap(blank, blank - 1);
				SimpleAudioEngine::getInstance()->playEffect("sound/跳.wav");
			}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S){
		if ((blank + 1) % h != 0) 
		{
			Swap(blank, blank + 1);
			SimpleAudioEngine::getInstance()->playEffect("sound/跳.wav");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A){
		if (blank + h < n) 		
		{
			Swap(blank, blank + h);
			SimpleAudioEngine::getInstance()->playEffect("sound/跳.wav");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D){		
		if (blank - h >= 0) 	
		{
			Swap(blank, blank - h);
			SimpleAudioEngine::getInstance()->playEffect("sound/跳.wav");
		}
		//Director::getInstance()->end();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE){
		{
			SimpleAudioEngine::getInstance()->playEffect("sound/eat.wav");
		}
	}
}

bool Puzzle::Done(){
	for (int i = 0; i < n; ++i) if (A[i] != i) return 0;
	return 1;
}

void Puzzle::Swap(int a, int b){
	blank = b;	
	B[A[a]]->runAction(MoveTo::create(0.0, P[b]));
	B[A[b]]->runAction(MoveTo::create(0.0, P[a]));
	swap(A[a], A[b]);
	
	if (Done()){		
		SimpleAudioEngine::getInstance()->playEffect("sound/傾僀僥儉1.wav");
		//Director::getInstance()->end();
	}
}


int inversion(VI& A){ // 计算逆序对
	int n = A.size();
	int z = 0; REP(i, n) FOR(j, i+1, n) if (A[i] > A[j]) ++z;
	return z;
}


bool Puzzle::init(){
	if (!Layer::init()){
		return false;
	}

	w = 6, h = 6; 
	
	n = w * h;
	A.resize(n); B.resize(n); P.resize(n); blank = random()%n;	 REP(i, n) A[i] = i;
	
	
	random_shuffle(A.begin(), A.end()); 

	// STL 
	
	while (inversion(A) & 1) random_shuffle(A.begin(), A.end());

	auto t = Sprite::create("pic.png");	
	int ww = t->getContentSize().width / w;
	int hh = t->getContentSize().height / h;	

	for (int ii = 0; ii < n; ++ii){
		int i = A[ii] / h, j = A[ii] % h, i2 = ii / h, j2 = ii % h;		
		B[A[ii]] = blank == ii ? Sprite::create("black.png", Rect(0,0,1,1)) : Sprite::create("pic.png", Rect(i*ww, (h-1-j)*hh, ww, hh));							
		B[A[ii]]->setPosition(Vec2(i2*(ww+2), j2*(hh+2))); addChild(B[A[ii]]);
		P[ii] = B[ A[ii] ]->getPosition();		
	}

	// ...
	// .
	// .
		//监听键盘事件
		auto e = EventListenerKeyboard::create();
		e->onKeyPressed = CC_CALLBACK_2(Puzzle::onKeyPressed, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(e, this);;

	return true;
}

bool Game::init(){
	if (!Scene::init()){
		return false;
	}

	auto t = Puzzle::create();
	t->setPosition(100, 100);
	t->setTag(1);
	addChild(t);
	return true;
}