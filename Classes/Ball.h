#ifndef BALL_H
#define BALL_H

#include "cocos2d.h"

#include "Resources.h"

using namespace cocos2d;


/**
 * Ball that bounces across the screen.
 */
class Ball : public Sprite {

public:
  CREATE_FUNC(Ball);

  /**
   * Initializes the ball.
   *
   * @return Whether initialization succeeded.
   */
  virtual bool init();

  /**
   * Increases the velocity of the ball.
   */
  void increaseVelocity();

  /**
   * Resets the ball and throws it to the left.
   */
  void resetToLeft();

  /**
   * Resets the ball and throws it to the right.
   */
  void resetToRight();

private:
  Ball() {};
  virtual ~Ball() {};

  void createPhysicsBody();

  void stop();
  void reset(float norm);
  void resetWithDelay(float norm);

};

#endif
