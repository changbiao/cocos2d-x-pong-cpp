#ifndef PADDLE_H
#define PADDLE_H

#include "cocos2d.h"

#include "Resources.h"

using namespace cocos2d;


/**
 * Paddle that each player controls, trying to keep the ball from touching the
 * edge of the screen behind it.
 */
class Paddle : public Sprite {

public:
  CREATE_FUNC(Paddle);

  /**
   * Initializes the paddle.
   *
   * @return Whether initialization succeeded.
   */
  virtual bool init();

  /**
   * Moves the paddle to the specified location.
   *
   * @param location Location where the paddle should move.
   */
  void move(const Point& location);

  /**
   * Moves the paddle up.
   */
  void moveUp();

  /**
   * Moves the paddle down.
   */
  void moveDown();

private:
  Paddle() {};
  virtual ~Paddle() {};

  void createPhysicsBody();

};

#endif
