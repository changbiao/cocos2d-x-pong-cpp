#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "cocos2d.h"

#include "Resources.h"

using namespace cocos2d;


/**
 * Collision manager.
 */
class CollisionManager : public Node {

public:
  typedef enum_t Tags;

  enum class Type : enum_t {
    BALL_WITH_WALL,
    BALL_WITH_PADDLE_LEFT,
    BALL_WITH_PADDLE_RIGHT,
    BALL_WITH_GOAL_LEFT,
    BALL_WITH_GOAL_RIGHT
  };

  /**
   * Creates the manager.
   *
   * @return Instance of the manager.
   */
  static CollisionManager* createWithMapping(const std::map <Tags, Type>& mapping);

  /**
   * Initializes the manager.
   *
   * @return Whether initialization succeeded.
   */
  virtual bool init();

public:
  /**
   * Collision callback.
   *
   * @param type Type of collision.
   * @param point Point where the collision happened.
   */
  std::function<void(Type type, const Point& point)> onCollision;

private:
  const std::map<Tags, Type> _mapping;

private:
  CollisionManager(const std::map<Tags, Type>& mapping) :
    onCollision(nullptr),
    _mapping(mapping) {};
  virtual ~CollisionManager() {};

  void createCollisionListener();

  bool onContactBegin(const PhysicsContact& contact);

  const Point& getPoint(const Point* points, int count);

};

#endif
