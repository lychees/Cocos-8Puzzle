#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace std;


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


bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto l1 = Label::createWithTTF("Start", "fonts/Marker Felt.ttf", 32);        
    //l1->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height / 7*4));		
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
	this->addChild(menu);
    return true;
}

void MainMenu::menuCallbackStart(Ref* p)
{
	//auto t = Game::create();
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
		if (blank % 3 != 0) Swap(blank, blank - 1); 
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S){
		if ((blank + 1) % 3 != 0) Swap(blank, blank + 1);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A){
		if (blank + 3 < 9) Swap(blank, blank + 3);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D){		
		if (blank - 3 >= 0) Swap(blank, blank - 3);		
		//Director::getInstance()->end();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE){
		Swap(0, 1);
	}
}

bool Puzzle::Done(){
	for (int i = 0; i < 9; ++i) if (A[i] != i) return 0;
	return 1;
}

void Puzzle::Swap(int a, int b){
	blank = b;
	CCLOG("%d %d \n ", a, b); //blank = b;		
	B[A[a]]->runAction(MoveTo::create(0.0, P[b]));
	B[A[b]]->runAction(MoveTo::create(0.0, P[a]));
	swap(A[a], A[b]);
	
	if (Done()){
		Director::getInstance()->end();
	}

}

bool Puzzle::init(){
	if (!Layer::init()){
		return false;
	}
	
	int n = 0; A.resize(9); B.resize(9); P.resize(9);

	blank = random() % 9;

	for (int i = 0; i < 9; ++i) A[i] = i;
	
	random_shuffle(A.begin(), A.end());

	for (int ii = 0; ii < 9; ++ii){
		int i = A[ii] / 3, j = A[ii] % 3;		
		int i2 = ii / 3, j2 = ii % 3;
		int n = ii;
		B[A[ii]] = blank == ii ? Sprite::create("black.png", Rect(0,0,150,150)) : Sprite::create("pic.png", Rect(i*150, (2-j)*150, 150, 150));							
		B[A[ii]]->setPosition(Vec2(i2 * 152, j2 * 152)); addChild(B[A[ii]]);
		P[ii] = B[ A[ii] ]->getPosition();
		++n;
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

/*
test git push
*/
