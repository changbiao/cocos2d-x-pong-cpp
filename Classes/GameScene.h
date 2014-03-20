#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "BaseLayer.h"
#include "Resources.h"

#include "ParticleManager.h"
#include "StreakManager.h"
#include "CollisionManager.h"
#include "KeyboardManager.h"
#include "TouchManager.h"

#include "Wall.h"
#include "Ball.h"
#include "Paddle.h"
#include "Goal.h"
#include "Score.h"

using namespace cocos2d;
using namespace CocosDenshion;


/**
 * Scene with all the game elements.
 */
class GameLayer : public BaseLayer {

public:
  CREATE_FUNC(GameLayer);

  /**
   * Creates a scene with this layer.
   *
   * @return The created scene.
   */
  static Scene* createScene();

  /**
   * Initializes the layer.
   *
   * @return Whether initialization succeeded.
   */
  virtual bool init();

  /**
   * Called when the layer enters the stage.
   */
  virtual void onEnter();

  /**
   * Moves to the previous scene.
   */
  void prev();

  /**
   * Starts the game in a random direction.
   */
  void start();

  /**
   * Restarts the game throwing the ball to the left.
   */
  void restartToLeft();

  /**
   * Restarts the game throwing the ball to the right.
   */
  void restartToRight();

  /**
   * Increases the score for the left player.
   */
  void scoreLeft();

  /**
   * Increases the score for the left player.
   */
  void scoreRight();

private:
  enum class Tag : enum_t {
    WALL         = (1 << 0),
    BALL         = (1 << 1),
    PLAYER_LEFT  = (1 << 2),
    PLAYER_RIGHT = (1 << 3),
    GOAL_LEFT    = (1 << 4),
    GOAL_RIGHT   = (1 << 5)
  };
  typedef enum_t Tags;

  enum class Order : enum_t {
    BACKGROUND = (1 << 0),
    FOREGROUND = (1 << 1)
  };
  typedef enum_t Orders;

  enum class Side : enum_t {
    LEFT  = (1 << 0),
    RIGHT = (1 << 1)
  };
  typedef enum_t Sides;

private:
  PhysicsWorld* _world;

  ParticleManager* _particleMgr;
  StreakManager* _streakMgr;
  CollisionManager* _collisionMgr;
  KeyboardManager* _keyboardMgr;
  TouchManager* _touchMgr;

  Wall* _wall;
  Ball* _ball;
  Paddle* _playerLeft;
  Paddle* _playerRight;
  Goal* _goalLeft;
  Goal* _goalRight;
  Score* _scoreLeft;
  Score* _scoreRight;

private:
  GameLayer() :
    _world(nullptr),
    _particleMgr(nullptr),
    _streakMgr(nullptr),
    _collisionMgr(nullptr),
    _keyboardMgr(nullptr),
    _touchMgr(nullptr),
    _wall(nullptr),
    _ball(nullptr),
    _playerLeft(nullptr),
    _playerRight(nullptr),
    _goalLeft(nullptr),
    _goalRight(nullptr),
    _scoreLeft(nullptr),
    _scoreRight(nullptr) {};
  virtual ~GameLayer() {};

  void setPhysicsWorld(PhysicsWorld* world);

  void createWall();
  void createBall();
  void createPaddles();
  void createGoals();
  void createScores();

  void createParticleManager();
  void createStreakManager();
  void createCollisionManager();
  void createKeyboardManager();
  void createTouchManager();

  void onCollision(CollisionManager::Type type, const Point& point);
  void onKey(KeyboardManager::Key key);
  void onTouch(const Point& location);

  Sides getCollisionSides(const Point& point);
  Side getTouchSide(const Point& point);
  void increaseVelocity();
  void playSoundCollision();
  void playSoundPoint();
  void emitParticles(const Point& point);

};

#endif
