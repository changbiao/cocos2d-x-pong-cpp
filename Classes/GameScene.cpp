#include <cstdlib>

#include "GameScene.h"
#include "MenuScene.h"
#include "VisibleRect.h"


#pragma mark - Constants

static const float TRANSITION_DURATION (0.5f);


#pragma mark - Public methods

Scene* GameLayer::createScene() {
  auto scene = Scene::createWithPhysics();
  auto world = scene->getPhysicsWorld();

  // No need for gravity.
  world->setGravity(Vect::ZERO);

#ifndef NDEBUG
  // Display physics in debug mode.
  world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif

  // Create layer.
  auto layer = GameLayer::create();
  layer->setPhysicsWorld(scene->getPhysicsWorld());
  scene->addChild(layer);

  return scene;
}

bool GameLayer::init() {
  if (!BaseLayer::init()) {
    return false;
  }

  createWall();
  createBall();
  createPaddles();
  createGoals();
  createScores();

  start();

  return true;
}

void GameLayer::onEnter() {
  Layer::onEnter();

  createParticleManager();
  createCollisionManager();
  createKeyboardManager();
  createTouchManager();
}

void GameLayer::prev() {
  auto menuScene = MenuLayer::createScene();
  Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_DURATION, menuScene));
}

void GameLayer::start() {
  if ((std::rand() % 2) == 0) {
    restartToLeft();
  }
  else {
    restartToRight();
  }
}

void GameLayer::restartToLeft() {
  _ball->setPosition(VisibleRect::center());
  _ball->resetToLeft();
}

void GameLayer::restartToRight() {
  _ball->setPosition(VisibleRect::center());
  _ball->resetToRight();
}

void GameLayer::scoreLeft() {
  _scoreLeft->increment();
}

void GameLayer::scoreRight() {
  _scoreRight->increment();
}


#pragma mark - Private methods

void GameLayer::setPhysicsWorld(PhysicsWorld* world) {
  _world = world;
}

void GameLayer::createWall() {
  _wall = Wall::create();
  _wall->setTag(static_cast<Tags>(Tag::WALL));
  _wall->setPosition(VisibleRect::center());

  addChild(_wall, static_cast<Orders>(Order::BACKGROUND));
}

void GameLayer::createBall() {
  _ball = Ball::create();
  _ball->setTag(static_cast<Tags>(Tag::BALL));
  _ball->setPosition(VisibleRect::center());

  addChild(_ball, static_cast<Orders>(Order::FOREGROUND));
}

void GameLayer::createPaddles() {
  auto hgap = VisibleRect::width() * 0.05;

  _playerLeft = Paddle::create();
  _playerLeft->setTag(static_cast<Tags>(Tag::PLAYER_LEFT));
  _playerLeft->setPosition(Point(VisibleRect::left().x + hgap, VisibleRect::left().y));

  _playerRight = Paddle::create();
  _playerRight->setTag(static_cast<Tags>(Tag::PLAYER_RIGHT));
  _playerRight->setPosition(Point(VisibleRect::right().x - hgap, VisibleRect::right().y));

  addChild(_playerLeft, static_cast<Orders>(Order::FOREGROUND));
  addChild(_playerRight, static_cast<Orders>(Order::FOREGROUND));
}

void GameLayer::createGoals() {
  auto hgap = VisibleRect::width() * 0.025;

  _goalLeft = Goal::create();
  _goalLeft->setTag(static_cast<Tags>(Tag::GOAL_LEFT));
  _goalLeft->setPosition(Point(VisibleRect::left().x - hgap, VisibleRect::left().y));

  _goalRight = Goal::create();
  _goalRight->setTag(static_cast<Tags>(Tag::GOAL_RIGHT));
  _goalRight->setPosition(Point(VisibleRect::right().x + hgap, VisibleRect::right().y));

  addChild(_goalLeft, static_cast<Orders>(Order::FOREGROUND));
  addChild(_goalRight, static_cast<Orders>(Order::FOREGROUND));
}

void GameLayer::createScores() {
  auto hgap = VisibleRect::width() * 0.20;
  auto vgap = VisibleRect::height() * 0.15;

  _scoreLeft = Score::create();
  _scoreLeft->setPosition(Point(VisibleRect::top().x - hgap, VisibleRect::top().y - vgap));

  _scoreRight = Score::create();
  _scoreRight->setPosition(Point(VisibleRect::top().x + hgap, VisibleRect::top().y - vgap));

  addChild(_scoreLeft, static_cast<Orders>(Order::BACKGROUND));
  addChild(_scoreRight, static_cast<Orders>(Order::BACKGROUND));
}

void GameLayer::createParticleManager() {
  _particleMgr = ParticleManager::create();

  addChild(_particleMgr);
}

void GameLayer::createCollisionManager() {
  std::map<CollisionManager::Tags, CollisionManager::Type> mapping = {
    { static_cast<Tags>(Tag::BALL) | static_cast<Tags>(Tag::WALL),         CollisionManager::Type::BALL_WITH_WALL         },
    { static_cast<Tags>(Tag::BALL) | static_cast<Tags>(Tag::PLAYER_LEFT),  CollisionManager::Type::BALL_WITH_PADDLE_LEFT  },
    { static_cast<Tags>(Tag::BALL) | static_cast<Tags>(Tag::PLAYER_RIGHT), CollisionManager::Type::BALL_WITH_PADDLE_RIGHT },
    { static_cast<Tags>(Tag::BALL) | static_cast<Tags>(Tag::GOAL_LEFT),    CollisionManager::Type::BALL_WITH_GOAL_LEFT    },
    { static_cast<Tags>(Tag::BALL) | static_cast<Tags>(Tag::GOAL_RIGHT),   CollisionManager::Type::BALL_WITH_GOAL_RIGHT   }
  };
  _collisionMgr = CollisionManager::createWithMapping(mapping);
  _collisionMgr->onCollision = CC_CALLBACK_2(GameLayer::onCollision, this);

  addChild(_collisionMgr);
}

void GameLayer::createKeyboardManager() {
  // The weird keyboard mapping choices are to prevent keyboard ghosting:
  // http://www.microsoft.com/appliedsciences/antighostingexplained.mspx
  std::map<EventKeyboard::KeyCode, KeyboardManager::Key> mapping = {
    { EventKeyboard::KeyCode::KEY_BACKSPACE, KeyboardManager::Key::ESCAPE            },
    { EventKeyboard::KeyCode::KEY_ESCAPE,    KeyboardManager::Key::ESCAPE            },
    { EventKeyboard::KeyCode::KEY_Q,         KeyboardManager::Key::PLAYER_LEFT_UP    },
    { EventKeyboard::KeyCode::KEY_W,         KeyboardManager::Key::PLAYER_LEFT_DOWN  },
    { EventKeyboard::KeyCode::KEY_P,         KeyboardManager::Key::PLAYER_RIGHT_UP   },
    { EventKeyboard::KeyCode::KEY_O,         KeyboardManager::Key::PLAYER_RIGHT_DOWN }
  };
  _keyboardMgr = KeyboardManager::createWithMapping(mapping);
  _keyboardMgr->onUpdate = CC_CALLBACK_1(GameLayer::onKey, this);

  addChild(_keyboardMgr);
}

void GameLayer::createTouchManager() {
  _touchMgr = TouchManager::create();
  _touchMgr->onTouch = CC_CALLBACK_1(GameLayer::onTouch, this);

  addChild(_touchMgr);
}

void GameLayer::onCollision(CollisionManager::Type type, const Point& point) {
  switch (type) {
    case CollisionManager::Type::BALL_WITH_PADDLE_LEFT:
    case CollisionManager::Type::BALL_WITH_PADDLE_RIGHT:
      playSoundCollision();
      emitParticles(point);
      increaseVelocity();
      break;
    case CollisionManager::Type::BALL_WITH_GOAL_LEFT:
      playSoundPoint();
      scoreRight();
      restartToLeft();
      break;
    case CollisionManager::Type::BALL_WITH_GOAL_RIGHT:
      playSoundPoint();
      scoreLeft();
      restartToRight();
      break;
    default:
      playSoundCollision();
      emitParticles(point);
      break;
  }
}

void GameLayer::onKey(KeyboardManager::Key key) {
  switch (key) {
    case KeyboardManager::Key::ESCAPE:
      prev();
      break;
    case KeyboardManager::Key::PLAYER_LEFT_UP:
      _playerLeft->moveUp();
      break;
    case KeyboardManager::Key::PLAYER_LEFT_DOWN:
      _playerLeft->moveDown();
      break;
    case KeyboardManager::Key::PLAYER_RIGHT_UP:
      _playerRight->moveUp();
      break;
    case KeyboardManager::Key::PLAYER_RIGHT_DOWN:
      _playerRight->moveDown();
      break;
    default:
      break;
  }
}

void GameLayer::onTouch(const Point& location) {
  auto side = getTouchSide(location);
  if (side == Side::LEFT) {
    _playerLeft->move(location);
  }
  else if (side == Side::RIGHT) {
    _playerRight->move(location);
  }
}

GameLayer::Side GameLayer::getTouchSide(const Point& location) {
  auto center = VisibleRect::center();
  if (location.x < center.x) {
    return Side::LEFT;
  }
  else {
    return Side::RIGHT;
  }
}

void GameLayer::increaseVelocity() {
  _ball->increaseVelocity();
}

void GameLayer::emitParticles(const Point& point) {
  _particleMgr->addEmitter(PARTICLE_PIXELS, point, static_cast<Orders>(Order::FOREGROUND));
}

void GameLayer::playSoundCollision() {
  SimpleAudioEngine::getInstance()->playEffect(SOUND_COLLISION);
}

void GameLayer::playSoundPoint() {
  SimpleAudioEngine::getInstance()->playEffect(SOUND_POINT);
}
