#include "TouchManager.h"
#include "VisibleRect.h"


#pragma mark - Public methods

TouchManager* TouchManager::create() {
	TouchManager* ret = new TouchManager();
  if (ret && ret->init()) {
    ret->autorelease();
  }
  else {
    CC_SAFE_DELETE(ret);
  }
	return ret;
}

bool TouchManager::init() {
  if (!Node::init()) {
    return false;
  }

  createTouchListener();

  return true;
}


#pragma mark - Private methods

void TouchManager::createTouchListener() {
  auto touchListener = EventListenerTouchOneByOne::create();
  touchListener->onTouchBegan = CC_CALLBACK_2(TouchManager::onTouchBegan, this);
  touchListener->onTouchMoved = CC_CALLBACK_2(TouchManager::onTouchMoved, this);
  getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool TouchManager::onTouchBegan(const Touch* touch, const Event* event) {
  if (onTouch == nullptr) {
    return true;
  }

  auto location = touch->getLocation();
  onTouch(location);
  return true;
}

void TouchManager::onTouchMoved(const Touch* touch, const Event* event) {
  if (onTouch == nullptr) {
    return;
  }

  auto location = touch->getLocation();
  onTouch(location);
}
