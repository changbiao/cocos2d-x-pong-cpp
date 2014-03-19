#include "ParticleSystemCustom.h"


#pragma mark - Public methods

ParticleSystemCustom* ParticleSystemCustom::createWithDictionary(ValueMap& dictionary) {
  return ParticleSystemCustom::createWithDictionary(dictionary, "");
}

ParticleSystemCustom* ParticleSystemCustom::createWithDictionary(ValueMap& dictionary, const std::string& dirname) {
  ParticleSystemCustom* ret = new ParticleSystemCustom();
  if (ret && ret->initWithDictionary(dictionary, dirname)) {
    ret->autorelease();
  }
  else {
    CC_SAFE_DELETE(ret);
  }
  return ret;
}
