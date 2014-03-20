#ifndef STREAK_MANAGER_H
#define STREAK_MANAGER_H

#include "cocos2d.h"

#include "Resources.h"

using namespace cocos2d;


/**
 * Streak manager.
 */
class StreakManager : public Node {

public:

  /**
   * Creates the manager.
   *
   * @param sprites Sprites to track.
   *
   * @return Instance of the manager.
   */
  static StreakManager* createWithSprites(const std::vector<Sprite*>& sprites);

  /**
   * Initializes the manager.
   *
   * @return Whether initialization succeeded.
   */
  virtual bool init();

private:
  std::map<Sprite*, MotionStreak*> _streaks;

private:
  StreakManager(const std::vector<Sprite*>& sprites);
  virtual ~StreakManager();

  void createUpdateListener();

  void onUpdate(const EventCustom* event);

};

#endif
