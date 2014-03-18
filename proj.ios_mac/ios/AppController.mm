#import "cocos2d.h"
#import "CCEAGLView.h"
#import "AppController.h"
#import "RootViewController.h"

#import "AppDelegate.h"


@implementation AppController

#pragma mark - Application lifecycle

// Application instance.
static AppDelegate s_sharedApplication;


- (BOOL)application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)launchOptions {
  // Add the view controller's view to the window and display.
  window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];

  // Init the CCEAGLView.
  CCEAGLView* eaglView = [CCEAGLView viewWithFrame: [window bounds]
                                       pixelFormat: kEAGLColorFormatRGB565
                                       depthFormat: GL_DEPTH24_STENCIL8_OES
                                preserveBackbuffer: NO
                                        sharegroup: nil
                                     multiSampling: NO
                                   numberOfSamples: 0];

  // Enable multitouch.
  [eaglView setMultipleTouchEnabled:YES];

  // Use RootViewController manage CCEAGLView.
  viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
  viewController.wantsFullScreenLayout = YES;
  viewController.view = eaglView;

  // Set RootViewController to window.
  if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
  {
    // This doesn't work on iOS6.
    [window addSubview: viewController.view];
  }
  else
  {
    // This works on iOS6.
    [window setRootViewController:viewController];
  }

  [window makeKeyAndVisible];

  [[UIApplication sharedApplication] setStatusBarHidden:true];

    // IMPORTANT: Setting the GLView should be done after creating the RootViewController
    cocos2d::GLView* glview = cocos2d::GLView::createWithEAGLView(eaglView);
    cocos2d::Director::getInstance()->setOpenGLView(glview);

    cocos2d::Application::getInstance()->run();

  return YES;
}


- (void)applicationWillResignActive:(UIApplication*)application {
  cocos2d::Director::getInstance()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication*)application {
  cocos2d::Director::getInstance()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication*)application {
  cocos2d::Application::getInstance()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication*)application {
  cocos2d::Application::getInstance()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication*)application {
}

#pragma mark - Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication*)application {
}

- (void)dealloc {
  [window release];
  [super dealloc];
}

@end
