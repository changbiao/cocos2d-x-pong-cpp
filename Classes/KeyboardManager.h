#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include "cocos2d.h"

#include "Resources.h"

using namespace cocos2d;


/**
 * Keyboard manager.
 */
class KeyboardManager : public Node {

public:
  enum class Key : enum_t {
    START             = (1 << 0),
    ESCAPE            = (1 << 1),
    PLAYER_LEFT_UP    = (1 << 2),
    PLAYER_LEFT_DOWN  = (1 << 3),
    PLAYER_RIGHT_UP   = (1 << 4),
    PLAYER_RIGHT_DOWN = (1 << 5),
    OTHER             = (1 << 6)
  };
  typedef enum_t Keys;

  /**
   * Creates the manager with a specific key mapping.
   *
   * @param mapping Key mapping, from Cocos2D keycodes to our own.
   *
   * @return Instance of the manager.
   */
  static KeyboardManager* createWithMapping(const std::map<EventKeyboard::KeyCode, Key>& mapping);

  /**
   * Initializes the manager.
   *
   * @return Whether initialization succeeded.
   */
  virtual bool init();

public:
  /**
   * Key pressed callback.
   *
   * @param key Key that was pressed.
   */
  std::function<void(Key key)> onPressed;

  /**
   * Key released callback.
   *
   * @param key Key that was released.
   */
  std::function<void(Key key)> onReleased;

  /**
   * Key update callback.
   *
   * @param key Key that is currently pressed.
   */
  std::function<void(Key key)> onUpdate;

private:
  const std::map<EventKeyboard::KeyCode, Key> _mapping;
  Keys _pressedKeys;

private:
  KeyboardManager(const std::map<EventKeyboard::KeyCode, Key>& mapping) :
    onPressed(nullptr),
    onReleased(nullptr),
    onUpdate(nullptr),
    _mapping(mapping),
    _pressedKeys(0) {};
  virtual ~KeyboardManager() {};

  void createKeyboardListener();
  void createUpdateListener();

  Key findKey(const EventKeyboard::KeyCode keyCode);

  void onKeyPressed(const EventKeyboard::KeyCode keyCode, const Event* event);
  void onKeyReleased(const EventKeyboard::KeyCode keyCode, const Event* event);
  void onKeyUpdate(const EventCustom* event);

};

#endif
