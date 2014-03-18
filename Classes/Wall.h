#ifndef WALL_H
#define WALL_H

#include "cocos2d.h"

#include "Resources.h"

using namespace cocos2d;


/**
 * Wall that surrounds the play area.
 */
class Wall : public Sprite {

public:
  CREATE_FUNC(Wall);

  /**
   * Initializes the wall.
   *
   * @return Whether initialization succeeded.
   */
  virtual bool init();

private:
  Wall() {};
  virtual ~Wall() {};

  void adjustScale();
  void createPhysicsBody();

};

#endif
