#include <array>

#include "Paddle.h"
#include "VisibleRect.h"


#pragma mark - Constants

static const float MOVE_PERCENTAGE    (0.015625);

static const int BITMASK_CONTACT_TEST (1);

static const PhysicsMaterial MATERIAL (1.0f, 1.0f, 0.0f);


#pragma mark - Inline functions

static inline float moveDistance() {
  return VisibleRect::height() * MOVE_PERCENTAGE;
}


#pragma mark - Public methods

bool Paddle::init() {
  if (!Sprite::initWithFile(SPRITE_PADDLE)) {
    return false;
  }

  createPhysicsBody();

  return true;
}

void Paddle::move(const Point& location) {
  // Clamp position to bounds.
  auto position = getPosition();
  auto height = getContentSize().height / 2;
  auto min = Point(position.x, VisibleRect::bottom().y + height);
  auto max = Point(position.x, VisibleRect::top().y - height);
  setPosition(location.getClampPoint(min, max));
}

void Paddle::moveUp() {
  move(getPosition() + Point(0, moveDistance()));
}

void Paddle::moveDown() {
  move(getPosition() - Point(0, moveDistance()));
}


#pragma mark - Private methods

void Paddle::createPhysicsBody() {
  auto bodySize = getContentSize();

  auto width2 = bodySize.width / 2;
  auto width4 = width2 / 2;
  auto width8 = width4 / 2;
  auto height2 = bodySize.height / 2;
  auto height4 = height2 / 2;
  auto height8 = height4 / 2;

  // Create this oval shape so that, when the ball bounces closer to the edges,
  // its direction changes slightly.
  std::array<Point, 12> bodyPoints = {
    Point(width4,           height2),
    Point(width2 - width8,  height2 - height8),
    Point(width2,           height8),
    Point(width2,           -height8),
    Point(width2 - width8,  -height2 + height8),
    Point(width4,           -height2),
    Point(-width4,          -height2),
    Point(-width2 + width8, -height2 + height8),
    Point(-width2,          -height8),
    Point(-width2,          height8),
    Point(-width2 + width8, height2 - height8),
    Point(-width4,          height2)
  };

  auto body = PhysicsBody::createPolygon(bodyPoints.data(), bodyPoints.size(), MATERIAL);
  body->setDynamic(false);
  body->setContactTestBitmask(BITMASK_CONTACT_TEST);

  setPhysicsBody(body);
}
