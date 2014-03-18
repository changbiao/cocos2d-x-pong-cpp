#ifndef BASE_LAYER_H
#define BASE_LAYER_H

#include "cocos2d.h"

using namespace cocos2d;


/**
 * Layer from which all others should inherit.
 */
class BaseLayer : public Layer {

public:
  BaseLayer() {};
  virtual ~BaseLayer() {};

  /**
   * Initializes the layer.
   *
   * @return Whether initialization succeeded.
   */
  virtual bool init();

  /**
  * Quits the application.
  */
  void quit();

};

#endif
