#include "BaseLayer.h"


#pragma mark - Public methods

bool BaseLayer::init() {
  if (!Layer::init()) {
    return false;
  }

  return true;
}

void BaseLayer::quit() {
  Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  exit(0);
#endif
}
