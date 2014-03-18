#include "VisibleRect.h"


#pragma mark - Static members

Rect VisibleRect::_visibleRect;


#pragma mark - Public methods

const Size& VisibleRect::size() {
  lazyInit();
  return _visibleRect.size;
}

const float VisibleRect::width() {
  lazyInit();
  return _visibleRect.size.width;
}

const float VisibleRect::height() {
  lazyInit();
  return _visibleRect.size.height;
}

const Point VisibleRect::left() {
  lazyInit();
  return Point(_visibleRect.origin.x, _visibleRect.origin.y + _visibleRect.size.height / 2);
}

const Point VisibleRect::right() {
  lazyInit();
  return Point(_visibleRect.origin.x + _visibleRect.size.width, _visibleRect.origin.y + _visibleRect.size.height / 2);
}

const Point VisibleRect::top() {
  lazyInit();
  return Point(_visibleRect.origin.x + _visibleRect.size.width / 2, _visibleRect.origin.y + _visibleRect.size.height);
}

const Point VisibleRect::bottom() {
  lazyInit();
  return Point(_visibleRect.origin.x + _visibleRect.size.width / 2, _visibleRect.origin.y);
}

const Point VisibleRect::center() {
  lazyInit();
  return Point(_visibleRect.origin.x + _visibleRect.size.width / 2, _visibleRect.origin.y + _visibleRect.size.height / 2);
}

const Point VisibleRect::leftTop() {
  lazyInit();
  return Point(_visibleRect.origin.x, _visibleRect.origin.y + _visibleRect.size.height);
}

const Point VisibleRect::rightTop() {
  lazyInit();
  return Point(_visibleRect.origin.x + _visibleRect.size.width, _visibleRect.origin.y + _visibleRect.size.height);
}

const Point VisibleRect::leftBottom() {
  lazyInit();
  return Point(_visibleRect.origin.x, _visibleRect.origin.y);
}

const Point VisibleRect::rightBottom() {
  lazyInit();
  return Point(_visibleRect.origin.x + _visibleRect.size.width, _visibleRect.origin.y);
}


#pragma mark - Private methods

void VisibleRect::lazyInit() {
  if (_visibleRect.size.width == 0.0f && _visibleRect.size.height == 0.0f) {
    auto director = Director::getInstance();
    _visibleRect.origin = director->getVisibleOrigin();
    _visibleRect.size = director->getVisibleSize();
  }
}
