#include "MenuScene.h"
#include "GameScene.h"
#include "VisibleRect.h"


#pragma mark - Constants

static const float TRANSITION_DURATION (0.5f);


#pragma mark - Public methods

Scene* MenuLayer::createScene() {
  auto scene = Scene::create();
  auto layer = MenuLayer::create();
  scene->addChild(layer);

  return scene;
}

bool MenuLayer::init() {
  if (!BaseLayer::init()) {
    return false;
  }

  createTitle();
  createMenu();

  return true;
}

void MenuLayer::onEnter() {
  Layer::onEnter();

  createKeyboardManager();
}

void MenuLayer::next() {
  auto gameScene = GameLayer::createScene();
  Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_DURATION, gameScene));
}


#pragma mark - Private methods

void MenuLayer::createKeyboardManager() {
  std::map<EventKeyboard::KeyCode, KeyboardManager::Key> mapping = {
    { EventKeyboard::KeyCode::KEY_SPACE,     KeyboardManager::Key::START  },
    { EventKeyboard::KeyCode::KEY_BACKSPACE, KeyboardManager::Key::ESCAPE },
    { EventKeyboard::KeyCode::KEY_ESCAPE,    KeyboardManager::Key::ESCAPE }
  };
  _keyboardMgr = KeyboardManager::createWithMapping(mapping);
  _keyboardMgr->onUpdate = CC_CALLBACK_1(MenuLayer::onKey, this);

  addChild(_keyboardMgr);
}

void MenuLayer::createTitle() {
  auto vgap = VisibleRect::height() * 0.15;

  auto titleLabel = LabelTTF::create(STR_TITLE, FONT_NAME, FONT_SIZE_TITLE);
  titleLabel->setPosition(Point(VisibleRect::center().x, VisibleRect::center().y + vgap));
  addChild(titleLabel);
}

void MenuLayer::createMenu() {
  auto vgap = VisibleRect::height() * 0.15;

  auto startMenuLabel = LabelTTF::create(STR_MENU_START, FONT_NAME, FONT_SIZE_MENU);
  auto startMenuItem = MenuItemLabel::create(startMenuLabel, CC_CALLBACK_1(MenuLayer::onMenuStart, this));
  startMenuItem->setPosition(Point(VisibleRect::center().x, VisibleRect::center().y - vgap));

  auto menu = Menu::create(startMenuItem, NULL);
  menu->setPosition(Point::ZERO);
  addChild(menu);
}

void MenuLayer::onKey(KeyboardManager::Key key) {
  if (key == KeyboardManager::Key::START) {
    next();
  }
  else if (key == KeyboardManager::Key::ESCAPE) {
    quit();
  }
}

void MenuLayer::onMenuStart(const Ref* sender) {
  next();
}
