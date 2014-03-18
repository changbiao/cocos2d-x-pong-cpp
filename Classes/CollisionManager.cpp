#include "CollisionManager.h"
#include "VisibleRect.h"


#pragma mark - Public methods

CollisionManager* CollisionManager::createWithMapping(const std::map<Tags, Type>& mapping) {
	CollisionManager* ret = new CollisionManager(mapping);
  if (ret && ret->init()) {
    ret->autorelease();
  }
  else {
    CC_SAFE_DELETE(ret);
  }
	return ret;
}

bool CollisionManager::init() {
  if (!Node::init()) {
    return false;
  }

  createCollisionListener();

  return true;
}


#pragma mark - Private methods

void CollisionManager::createCollisionListener() {
  auto contactListener = EventListenerPhysicsContact::create();
  contactListener->onContactBegin = CC_CALLBACK_1(CollisionManager::onContactBegin, this);
  getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool CollisionManager::onContactBegin(const PhysicsContact& contact) {
  if (onCollision == nullptr) {
    return true;
  }

  auto tagA = contact.getShapeA()->getBody()->getNode()->getTag();
  auto tagB = contact.getShapeB()->getBody()->getNode()->getTag();

  auto data = contact.getContactData();
  auto points = data->points;
  auto count = data->count;

  onCollision(_mapping.at(tagA | tagB), getPoint(points, count));

  return true;
}

const Point& CollisionManager::getPoint(const Point* points, int count) {
  return points[0];
}
