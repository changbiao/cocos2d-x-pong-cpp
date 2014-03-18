#ifndef GOAL_H
#define GOAL_H

#include "cocos2d.h"

#include "Resources.h"

using namespace cocos2d;


/**
 * Goal behind each player.
 */
class Goal : public Node {

public:
  CREATE_FUNC(Goal);

  /**
   * Initializes the goal.
   *
   * @return Whether initialization succeeded.
   */
  virtual bool init();

private:
  Goal() {};
  virtual ~Goal() {};

  void createPhysicsBody();

};

#endif
