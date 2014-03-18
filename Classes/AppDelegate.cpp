#include <cstdlib>
#include <ctime>

#include "AppDelegate.h"
#include "MenuScene.h"
#include "Resources.h"


#pragma mark - Resolutions

typedef struct Resolution {
  const Size size;
  const char path[3];
} Resolution;

static const Resolution smallDef  = { Size(480, 320),   "SD" };
static const Resolution mediumDef = { Size(1024, 768),  "MD" };
static const Resolution highDef   = { Size(2048, 1536), "HD" };

static const Size designSize = Size(480, 320);


#pragma mark - Public methods

bool AppDelegate::applicationDidFinishLaunching() {
  auto director  = Director::getInstance();

  setupSprites();

  director->setAnimationInterval(1.0 / 60);

#ifndef NDEBUG
  // Display FPS in debug mode.
  director->setDisplayStats(true);
#endif

  // Seed RNG.
  std::srand(std::time(0));

  // Create the initial scene.
  auto scene = MenuLayer::createScene();
  director->runWithScene(scene);

  return true;
}

void AppDelegate::applicationDidEnterBackground() {
  Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
  Director::getInstance()->startAnimation();
}


#pragma mark - Private methods

void AppDelegate::setupSprites() {
  auto fileUtils = FileUtils::getInstance();
  auto director  = Director::getInstance();
  auto glView    = director->getOpenGLView();

  if (!glView) {
    glView = GLView::createWithFullScreen(STR_APP);
    director->setOpenGLView(glView);
  }

  glView->setDesignResolutionSize(designSize.width,
                                  designSize.height,
                                  ResolutionPolicy::SHOW_ALL);

  Size screenSize = glView->getFrameSize();
  if (screenSize.height > mediumDef.size.height) {
	  fileUtils->addSearchPath(highDef.path);
    director->setContentScaleFactor(highDef.size.height / designSize.height);
  }
  else if (screenSize.height > smallDef.size.height) {
    fileUtils->addSearchPath(mediumDef.path);
    director->setContentScaleFactor(mediumDef.size.height / designSize.height);
  }
  else {
    fileUtils->addSearchPath(smallDef.path);
    director->setContentScaleFactor(smallDef.size.height / designSize.height);
  }
}
