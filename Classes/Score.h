#ifndef SCORE_H
#define SCORE_H

#include "cocos2d.h"

#include "Resources.h"

using namespace cocos2d;


/**
 * Label to keep track of the score for each player.
 */
class Score : public LabelTTF {

public:
  CREATE_FUNC(Score);

  /**
   * Initializes the score.
   *
   * @return Whether initialization succeeded.
   */
  virtual bool init();

  /**
   * Increments the score.
   */
  void increment();

private:
  int _value;

private:
  Score() :
    _value(0) {};
  virtual ~Score() {};

};

#endif
