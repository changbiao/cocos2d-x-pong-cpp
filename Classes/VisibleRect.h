#ifndef VISIBLERECT_H
#define VISIBLERECT_H

#include "cocos2d.h"

using namespace cocos2d;


/**
 * Visible area of the screen.
 */
class VisibleRect {

public:
  static const Size& size();

  static const float width();
  static const float height();

  static const Point left();
  static const Point right();
  static const Point top();
  static const Point bottom();
  static const Point center();
  static const Point leftTop();
  static const Point rightTop();
  static const Point leftBottom();
  static const Point rightBottom();

private:
  static Rect _visibleRect;

  static void lazyInit();

  VisibleRect() {};
  virtual ~VisibleRect() {};

};

#endif
