#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H

#include "cocos2d.h"

#include "Resources.h"

using namespace cocos2d;


/**
 * Particle manager.
 */
class ParticleManager : public Node {

public:

  /**
   * Creates the manager.
   *
   * @return Instance of the manager.
   */
  static ParticleManager* create();

  /**
   * Initializes the manager.
   *
   * @return Whether initialization succeeded.
   */
  virtual bool init();

  /**
   * Adds a new particle emitter.
   *
   * @param filename File name from which to load the emitter.
   * @param position Position where the emitter will be added.
   * @param order Depth at which the emitter will be added.
   */
  void addEmitter(const std::string& filename, const Point& position, int order);

private:
  std::map<const std::string, ValueMap> _emitters;

private:
  ParticleManager() {};
  virtual ~ParticleManager() {};

  ParticleSystem* getEmitter(const std::string& filename);

};

#endif
