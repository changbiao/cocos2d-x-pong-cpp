#include "KeyboardManager.h"


#pragma mark - Public methods

KeyboardManager* KeyboardManager::createWithMapping(const std::map<EventKeyboard::KeyCode, Key>& mapping) {
  KeyboardManager* ret = new KeyboardManager(mapping);
  if (ret && ret->init()) {
    ret->autorelease();
  }
  else {
    CC_SAFE_DELETE(ret);
  }
  return ret;
}

bool KeyboardManager::init() {
  if (!Node::init()) {
    return false;
  }

  createKeyboardListener();
  createUpdateListener();

  return true;
}


#pragma mark - Private methods

void KeyboardManager::createKeyboardListener() {
  auto keyboardListener = EventListenerKeyboard::create();
  keyboardListener->onKeyPressed = CC_CALLBACK_2(KeyboardManager::onKeyPressed, this);
  keyboardListener->onKeyReleased = CC_CALLBACK_2(KeyboardManager::onKeyReleased, this);
  getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void KeyboardManager::createUpdateListener() {
  auto updateListener = EventListenerCustom::create(Director::EVENT_AFTER_UPDATE, CC_CALLBACK_1(KeyboardManager::onKeyUpdate, this));
  getEventDispatcher()->addEventListenerWithSceneGraphPriority(updateListener, this);
}

KeyboardManager::Key KeyboardManager::findKey(const EventKeyboard::KeyCode keyCode) {
  auto iter = _mapping.find(keyCode);
  if (iter != _mapping.end()) {
    return iter->second;
  }

  return Key::OTHER;
}

void KeyboardManager::onKeyPressed(const EventKeyboard::KeyCode keyCode, const Event* event) {
  auto key = findKey(keyCode);
  _pressedKeys |= static_cast<Keys>(key);

  if (onPressed != nullptr) {
    onPressed(key);
  }
}

void KeyboardManager::onKeyReleased(const EventKeyboard::KeyCode keyCode, const Event* event) {
  auto key = findKey(keyCode);
  _pressedKeys &= ~static_cast<Keys>(key);

  if (onReleased != nullptr) {
    onReleased(key);
  }
}

void KeyboardManager::onKeyUpdate(const EventCustom* event) {
  if (_pressedKeys == 0 || onUpdate == nullptr) {
    return;
  }

  for (auto iter = _mapping.begin(); iter != _mapping.end(); ++iter) {
    auto key = iter->second;
    if (_pressedKeys & static_cast<Keys>(key)) {
      onUpdate(key);
    }
  }
}
