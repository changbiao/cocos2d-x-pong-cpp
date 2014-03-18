#include "Wall.h"
#include "VisibleRect.h"


#pragma mark - Constants

static const float BORDER_PERCENTAGE  (0.03125);

static const int BITMASK_CONTACT_TEST (1);

static const PhysicsMaterial MATERIAL (1.0f, 1.0f, 0.0f);


#pragma mark - Public methods

bool Wall::init() {
  if (!Sprite::initWithFile(SPRITE_WALL)) {
    return false;
  }

  adjustScale();
  createPhysicsBody();

  return true;
}


#pragma mark - Private methods

void Wall::adjustScale() {
  // Stretch to cover the whole screen.
  auto screenSize = VisibleRect::size();
  auto spriteSize = getContentSize();
  setScale(screenSize.width / spriteSize.width, screenSize.height / spriteSize.height);
}

void Wall::createPhysicsBody() {
  auto spriteSize = getContentSize() * getScale();
  auto bodyBorder = spriteSize.height * BORDER_PERCENTAGE;
  auto bodySize = Size(spriteSize.width + (10 * bodyBorder), spriteSize.height);
  auto body = PhysicsBody::createEdgeBox(bodySize, MATERIAL, bodyBorder);
  body->setContactTestBitmask(BITMASK_CONTACT_TEST);

  setPhysicsBody(body);
}
