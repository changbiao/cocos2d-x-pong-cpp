#ifndef PARTICLE_SYSTEM_CUSTOM_H
#define PARTICLE_SYSTEM_CUSTOM_H

#include "cocos2d.h"

#include "Resources.h"

using namespace cocos2d;


/**
 * Custom particle system.
 *
 * It inherits from `ParticleSystemQuad` just to add a new `create` method that
 * relies on `initWithDictionary` instead of `initWithFile`, as the latter
 * always tries to read the file from disc.
 */
class ParticleSystemCustom : public ParticleSystemQuad {

public:

  /**
   * Creates the particle system.
   *
   * @param dictionary Properties of the particle system.
   *
   * @return Instance of the system.
   */
  static ParticleSystemCustom* createWithDictionary(ValueMap& dictionary);

  /**
  * Creates the particle system.
  *
  * @param dictionary Properties of the particle system.
  * @param dirname Path from where to load the image.
  *
  * @return Instance of the system.
  */
  static ParticleSystemCustom* createWithDictionary(ValueMap& dictionary, const std::string& dirname);

protected:

};

#endif
