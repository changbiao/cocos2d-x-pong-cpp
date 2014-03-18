#include <cstdlib>

#include "Ball.h"
#include "VisibleRect.h"


#pragma mark - Constants

static const float VELOCITY_START     (200.0f);
static const float VELOCITY_LIMIT     (600.f);
static const float VELOCITY_INCREASE  (1.05f);

static const float RESET_DELAY        (1.5f);

static const int BITMASK_CONTACT_TEST (1);

static const PhysicsMaterial MATERIAL (1.0f, 1.0f, 0.0f);


#pragma mark - Inline functions

static inline float randInRange(float a, float b) {
  return (static_cast<float>(std::rand() % static_cast<int>((b - a) * 100)) / 100) + a;
}


#pragma mark - Public methods

bool Ball::init() {
  if (!Sprite::initWithFile(SPRITE_BALL)) {
    return false;
  }

  createPhysicsBody();

  return true;
}

void Ball::increaseVelocity() {
  auto body = getPhysicsBody();
  body->setVelocity(body->getVelocity() * VELOCITY_INCREASE);
}

void Ball::resetToLeft() {
  resetWithDelay(-VELOCITY_START);
}

void Ball::resetToRight() {
  resetWithDelay(VELOCITY_START);
}


#pragma mark - Private methods

void Ball::createPhysicsBody() {
  auto bodyRadius = getContentSize().width / 2;
  auto body = PhysicsBody::createCircle(bodyRadius, MATERIAL);
  body->setVelocityLimit(VELOCITY_LIMIT);
  body->setRotationEnable(false);
  body->setContactTestBitmask(BITMASK_CONTACT_TEST);

  setPhysicsBody(body);
}

void Ball::stop() {
  getPhysicsBody()->setVelocity(Vect::ZERO);
}

void Ball::reset(float norm) {
  stop();

  // Throw the ball in a random direction between -45 and 45 degrees.
  auto angle = randInRange(static_cast<float>(-M_PI_4), static_cast<float>(M_PI_4));
  auto velocity = Vect(norm, 0).rotateByAngle(Point::ZERO, angle);
  getPhysicsBody()->setVelocity(velocity);
}

void Ball::resetWithDelay(float norm) {
  stop();

  // Wait and then throw the ball.
  runAction(Sequence::create(
    DelayTime::create(RESET_DELAY),
    CallFunc::create(CC_CALLBACK_0(Ball::reset, this, norm)),
    NULL));
}
