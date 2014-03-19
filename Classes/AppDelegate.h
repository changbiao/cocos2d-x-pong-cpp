#ifndef APP_DELEGATE_H
#define APP_DELEGATE_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;


/**
 * Pong clone.
 */
class AppDelegate : private Application {

public:
  AppDelegate() {};
  virtual ~AppDelegate() {};

  /**
   * Called when the application finishes launching.
   *
   * @return Whether initialization succeeded.
   */
  virtual bool applicationDidFinishLaunching();

  /**
   * Called when the application enters background state.
   */
  virtual void applicationDidEnterBackground();

  /**
   * Called when the application enters foreground state.
   */
  virtual void applicationWillEnterForeground();

private:
  void setupSprites();
  void setupSounds();

};

#endif
