#ifndef TOUCH_MANAGER_H
#define TOUCH_MANAGER_H

#include "cocos2d.h"

#include "Resources.h"

using namespace cocos2d;


/**
 * Touch manager.
 */
class TouchManager : public Node {

public:
  enum class Side : enum_t {
    LEFT,
    RIGHT
  };

  /**
   * Creates the manager.
   *
   * @return Instance of the manager.
   */
  static TouchManager* create();

  /**
   * Initializes the manager.
   *
   * @return Whether initialization succeeded.
   */
  virtual bool init();

public:
  /**
   * Touch callback.
   *
   * @param location Location where the contact happened.
   */
  std::function<void(const Point& location)> onTouch;

private:
  TouchManager() :
    onTouch(nullptr) {};
  virtual ~TouchManager() {};

  void createTouchListener();

  bool onTouchBegan(const Touch* touch, const Event* event);
  void onTouchMoved(const Touch* touch, const Event* event);

};

#endif
