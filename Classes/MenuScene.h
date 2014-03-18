#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include "cocos2d.h"

#include "BaseLayer.h"
#include "Resources.h"

#include "KeyboardManager.h"

using namespace cocos2d;


/**
 * Scene with the main menu.
 */
class MenuLayer : public BaseLayer {

public:
  CREATE_FUNC(MenuLayer);

  /**
   * Creates a scene with this layer.
   *
   * @return The created scene.
   */
  static Scene* createScene();

  /**
   * Initializes the layer.
   *
   * @return Whether initialization succeeded.
   */
  virtual bool init();

  /**
   * Called when the layer enters the stage.
   */
  virtual void onEnter();

  /**
   * Moves to the next scene.
   */
  void next();

private:
  KeyboardManager* _keyboardMgr;

private:
  MenuLayer() :
    _keyboardMgr(nullptr) {};
  virtual ~MenuLayer() {};

  void createKeyboardManager();

  void createTitle();
  void createMenu();

  void onKey(KeyboardManager::Key key);
  void onMenuStart(const Ref* sender);

};

#endif
