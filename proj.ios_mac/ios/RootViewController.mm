#import "cocos2d.h"
#import "CCEAGLView.h"
#import "RootViewController.h"


@implementation RootViewController

// This method is deprecated on iOS6.
- (BOOL) shouldAutorotateToInterfaceOrientation: (UIInterfaceOrientation)interfaceOrientation {
  return UIInterfaceOrientationIsLandscape(interfaceOrientation);
}

// For iOS6, use `supportedInterfaceOrientations` and `shouldAutorotate` instead.
- (NSUInteger) supportedInterfaceOrientations {
#ifdef __IPHONE_6_0
  return UIInterfaceOrientationMaskAllButUpsideDown;
#endif
}

- (BOOL) shouldAutorotate {
  return YES;
}

- (void) didRotateFromInterfaceOrientation: (UIInterfaceOrientation)fromInterfaceOrientation {
	[super didRotateFromInterfaceOrientation: fromInterfaceOrientation];

  cocos2d::GLView* glView = cocos2d::Director::getInstance()->getOpenGLView();
  CCEAGLView* eaglView = (CCEAGLView*) glView->getEAGLView();

	CGSize s = CGSizeMake([eaglView getWidth], [eaglView getHeight]);
	cocos2d::Application::getInstance()->applicationScreenSizeChanged((int)s.width, (int)s.height);
}

- (BOOL) prefersStatusBarHidden {
  return YES;
}

- (void) didReceiveMemoryWarning {
  [super didReceiveMemoryWarning];
}

- (void) viewDidUnload {
  [super viewDidUnload];
}


- (void) dealloc {
  [super dealloc];
}

@end
