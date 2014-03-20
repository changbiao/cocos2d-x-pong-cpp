#include "StreakManager.h"
#include "VisibleRect.h"


#pragma mark - Constants

static const float DURATION (0.25f);
static const float SEGMENTS (2);
static const Color3B COLOR  (87, 87, 87);


#pragma mark - Public methods

StreakManager* StreakManager::createWithSprites(const std::vector<Sprite*>& sprites) {
  StreakManager* ret = new StreakManager(sprites);
  if (ret && ret->init()) {
    ret->autorelease();
  }
  else {
    CC_SAFE_DELETE(ret);
  }
  return ret;
}

bool StreakManager::init() {
  if (!Node::init()) {
    return false;
  }

  createUpdateListener();

  return true;
}


#pragma mark - Private methods


StreakManager::StreakManager(const std::vector<Sprite*>& sprites) {
  for (auto sprite : sprites) {
    auto streak = MotionStreak::create(DURATION, SEGMENTS, sprite->getContentSize().width, COLOR, sprite->getTexture());
    sprite->getParent()->addChild(streak, sprite->getZOrder() - 1);

    _streaks[sprite] = streak;
  };
}

StreakManager::~StreakManager() {
}


void StreakManager::createUpdateListener() {
  auto updateListener = EventListenerCustom::create(Director::EVENT_AFTER_UPDATE, CC_CALLBACK_1(StreakManager::onUpdate, this));
  getEventDispatcher()->addEventListenerWithSceneGraphPriority(updateListener, this);
}

void StreakManager::onUpdate(const EventCustom* event) {
  for (auto iter = _streaks.begin(); iter != _streaks.end(); ++iter) {
    auto node = iter->first;
    auto streak = iter->second;

    auto nodePos = node->getPosition();
    auto streakPos = streak->getPosition();

    // Avoid excessive ribbon when moving sprites long distances.
    if (nodePos.getDistance(streakPos) > VisibleRect::width() / 3) {
      streak->reset();
    }

    streak->setPosition(nodePos);
  }
}
