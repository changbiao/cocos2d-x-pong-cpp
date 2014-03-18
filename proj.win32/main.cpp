#include "main.h"
#include "AppDelegate.h"

using namespace cocos2d;

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  AppDelegate app;
  return Application::getInstance()->run();
}
