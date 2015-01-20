#include "MainLayer.h"
#include "ConstValue.h"

USING_NS_CC;

bool MainLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	
	this->isFullView = true;
	this->setAnchorPoint(ccp(0, 0));
	this->setEmptyGrid(GRID_SIZE - 1, GRID_SIZE - 1);

	this->listenKeyboardEvent();
	this->scheduleUpdate();

	return true;
}

void MainLayer::initContent() {
	this->createGideLayers();
	this->createPlayerSprite();
}

void MainLayer::setEmptyGrid(int x, int y) {
	this->_emptyGridX = x;
	this->_emptyGridY = y;
}

void MainLayer::createGideLayers() {
	for (int i = 0; i < GRID_SIZE * GRID_SIZE - 1; i++) {
		GridLayer* gridLayer = GridLayer::create();
		gridLayer->initContent(i);
		gridLayer->setGridPosition(i / GRID_SIZE, i % GRID_SIZE);
		this->addChild(gridLayer);
		this->_gridLayers.pushBack(gridLayer);
	}
}

void MainLayer::createPlayerSprite() {
	this->_playerSprite = PlayerSprite::create();
	this->_playerSprite->setPosition(this->findObjPosition("player"));
	this->addChild(this->_playerSprite);
}

Vec2 MainLayer::findObjPosition(const char* name) {
	for (auto& grid : this->_gridLayers) {
		Vec2 res;
		if (grid->findObjPosition(name, res)) {
			res += grid->getPosition();
			return res;
		}
	}
	return ccp(0, 0);
}

void MainLayer::listenKeyboardEvent() {
	this->_eventDispatcher->removeAllEventListeners();
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(MainLayer::onKeyPressed2, this);
	listener->onKeyReleased = CC_CALLBACK_2(MainLayer::onKeyReleased2, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


void MainLayer::onKeyPressed2(EventKeyboard::KeyCode code, Event* evt) {
	switch ((int)code) {
	case (int)EventKeyboard::KeyCode::KEY_SPACE:
		this->_playerSprite->runState = PlayerSprite::RunState::Idle;
		if (this->isFullView) {
			this->setLocalView();
		}
		else {
			this->setFullView();
		}
		break;
	case (int)EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case (int)EventKeyboard::KeyCode::KEY_A:
		if (isFullView) {
			this->moveEmptyGrid(1);
		}
		else {
			this->_playerSprite->runState = PlayerSprite::RunState::RunLeft;
		}
		break;
	case (int)EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case (int)EventKeyboard::KeyCode::KEY_D:
		if (isFullView) {
			this->moveEmptyGrid(0);
		}
		else {
			this->_playerSprite->runState = PlayerSprite::RunState::RunRight;
		}
		break;
	case (int)EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case (int)EventKeyboard::KeyCode::KEY_S:
		if (isFullView) {
			this->moveEmptyGrid(3);
		}
		break;
	case (int)EventKeyboard::KeyCode::KEY_UP_ARROW:
	case (int)EventKeyboard::KeyCode::KEY_W:
		if (isFullView) {
			this->moveEmptyGrid(2);
		} else {
			if (!this->_playerSprite->isJumping)
				this->_playerSprite->setVelocity(Vec2(0, JUMP_SPEED_Y));
		}
		break;
	default:
		break;
	}
}

void MainLayer::onKeyReleased2(EventKeyboard::KeyCode code, Event* evt) {
	switch ((int)code) {
	case (int)EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case (int)EventKeyboard::KeyCode::KEY_A:
	case (int)EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case (int)EventKeyboard::KeyCode::KEY_D:
		this->_playerSprite->runState = PlayerSprite::RunState::Idle;
		break;
	default:
		break;
	}
}

void MainLayer::moveEmptyGrid(int dir) {
	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, 1, -1 };
	int nextX = this->_emptyGridX + dx[dir];
	int nextY = this->_emptyGridY + dy[dir];
	if (nextX >= 0 && nextX < GRID_SIZE && nextY >= 0 && nextY < GRID_SIZE) {
		for (auto& grid : this->_gridLayers)
			if (grid->_gridX == nextX && grid->_gridY == nextY) {
				grid->moveGridPosition(dir ^ 1);
				break;
			}
		if (this->_playerSprite->gridX == nextX && this->_playerSprite->gridY == nextY) {
			this->_playerSprite->moveGridPosition(dir ^ 1);
		}
		this->_emptyGridX = nextX;
		this->_emptyGridY = nextY;
	}
}

void MainLayer::setLocalView() {
	Size winSize = Director::sharedDirector()->getWinSize();
	auto posX = winSize.width / 2 - this->_playerSprite->getPositionX() * LOCAL_VIEW_SCALE;
	auto posY = winSize.height / 2 - this->_playerSprite->getPositionY() * LOCAL_VIEW_SCALE;
	auto scaleTo = ScaleTo::create(0.5f, LOCAL_VIEW_SCALE);
	auto moveTo = MoveTo::create(0.5f, ccp(posX, posY));
	auto action1 = Sequence::create(moveTo, CallFunc::create(CC_CALLBACK_0(MainLayer::setIsFullView, this, false)), NULL);
	auto action2 = Sequence::create(scaleTo, CallFunc::create(CC_CALLBACK_0(MainLayer::setIsFullView, this, false)), NULL);
	this->runAction(action1);
	this->runAction(action2);
}

void MainLayer::setFullView() {
	auto scaleTo = ScaleTo::create(0.5f, 1.0f);
	auto moveTo = MoveTo::create(0.5f, ccp(0, 0));
	this->runAction(scaleTo);
	this->runAction(moveTo);
	this->isFullView = true;
}

void MainLayer::setIsFullView(bool flag) {
	this->isFullView = flag;
}

void MainLayer::setPlayerView() {
	Size winSize = Director::sharedDirector()->getWinSize();
	auto posX = winSize.width / 2 - this->_playerSprite->getPositionX() * LOCAL_VIEW_SCALE;
	auto posY = winSize.height / 2 - this->_playerSprite->getPositionY() * LOCAL_VIEW_SCALE;
	this->setPosition(posX, posY);
}

void MainLayer::update(float dt) {
	this->_playerSprite->update(dt);
	if (!isFullView)
		this->setPlayerView();
}
