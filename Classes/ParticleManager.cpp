#include "ParticleManager.h"
#include "ParticleSystemCustom.h"
#include "VisibleRect.h"


#pragma mark - Public methods

ParticleManager* ParticleManager::create() {
  ParticleManager* ret = new ParticleManager();
  if (ret && ret->init()) {
    ret->autorelease();
  }
  else {
    CC_SAFE_DELETE(ret);
  }
  return ret;
}

bool ParticleManager::init() {
  if (!Node::init()) {
    return false;
  }

  return true;
}

void ParticleManager::addEmitter(const std::string& filename, const Point& position, int order) {
  auto emitter = getEmitter(filename);
  emitter->setPosition(position);
  emitter->setAutoRemoveOnFinish(true);

  getParent()->addChild(emitter, order);
}


#pragma mark - Private methods

ParticleSystem* ParticleManager::getEmitter(const std::string& filename) {
  auto filepath = FileUtils::getInstance()->fullPathForFilename(filename);
  ValueMap dict;
  ParticleSystem* emitter;

  auto iter = _emitters.find(filepath);
  if (iter != _emitters.end()) {
    dict = iter->second;
  }
  else {
    dict = FileUtils::getInstance()->getValueMapFromFile(filepath);
    _emitters[filepath] = dict;
  }

  CCASSERT(!dict.empty(), "Particles: file not found");

  if (filepath.find('/') != std::string::npos) {
    filepath = filepath.substr(0, filepath.rfind('/') + 1);
    emitter = ParticleSystemCustom::createWithDictionary(dict, filepath);
  }
  else {
    emitter = ParticleSystemCustom::createWithDictionary(dict, "");
  }

  return emitter;
}
