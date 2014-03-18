#include "Goal.h"
#include "VisibleRect.h"


#pragma mark - Constants

static const float BORDER_PERCENTAGE  (0.03125);

static const int BITMASK_CONTACT_TEST (1);

static const PhysicsMaterial MATERIAL (1.0f, 1.0f, 0.0f);


#pragma mark - Public methods

bool Goal::init() {
  if (!Node::init()) {
    return false;
  }

  createPhysicsBody();

  return true;
}


#pragma mark - Private methods

void Goal::createPhysicsBody() {
  auto screenSize = VisibleRect::size();
  auto bodyBorder = screenSize.height * BORDER_PERCENTAGE;
  auto body = PhysicsBody::createBox(Size(bodyBorder, screenSize.height), MATERIAL);
  body->setDynamic(false);
  body->setContactTestBitmask(BITMASK_CONTACT_TEST);

  setPhysicsBody(body);
}
