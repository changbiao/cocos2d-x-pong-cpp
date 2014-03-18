#include <sstream>

#include "Score.h"
#include "VisibleRect.h"


#pragma mark - Constants

static const GLubyte OPACITY (87.5);


#pragma mark - Inline functions

static inline std::string toString(int val) {
  // We cannot use `std::to_string` on Android, so we fall back to this.
  std::ostringstream ss;
  ss << val;
  return ss.str();
}


#pragma mark - Public methods

bool Score::init() {
  if (!LabelTTF::initWithString(toString(_value), FONT_NAME, FONT_SIZE_SCORE)) {
    return false;
  }

  setOpacity(OPACITY);

  return true;
}

void Score::increment() {
  setString(toString(++_value));
}
