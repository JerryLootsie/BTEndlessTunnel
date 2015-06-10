//
//  BTEndlessTunnelAppController.mm
//  BTEndlessTunnel
//
//  Created by NSS on 3/21/14.
//  Copyright __MyCompanyName__ 2014. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "AppController.h"
#import "cocos2d.h"
#import "EAGLView.h"
#import "AppDelegate.h"

#import "PlayGameConstants.h"
#import "PlayGameSingleton.h"

#import "RootViewController.h"
//#import "GCHelper.h"

//#import <FacebookSDK/FacebookSDK.h> 

#import "Lootsie.h"

// cpp stuff
#import "LootsieManager.h"

@implementation AppController

@synthesize window;
@synthesize viewController;
//@synthesize viewController = _viewController;

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
// BTEndlessTunnel/ios/AppController.mm:33:20: error: interface type cannot be statically allocated
static AppDelegate s_sharedApplication;

/**
 Singleton instance
 */
+ (id)sharedInstance {
    static dispatch_once_t pred = 0;
    __strong static id _sharedObject = nil;
    dispatch_once(&pred, ^{
        //_sharedObject = [[self alloc] init];
        _sharedObject = [self alloc];
        
        NSLog(@"AppController: singleton created!");
    });
    return _sharedObject;
}


-(id) init
{
    
     NSLog(@"AppController: init");
    
    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH_COMPONENT16
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples:0 ];
    
    // Use RootViewController manage EAGLView
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;
    [__glView setMultipleTouchEnabled: YES];
    
    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    
    [window makeKeyAndVisible];
    
    [[UIApplication sharedApplication] setStatusBarHidden: YES];
    
    return self;
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

//    [[GCHelper sharedInstance] authenticateLocalUser];
    // PlayGameSingleton::sharedInstance().authenticate();

    // Override point for customization after application launch.
    ServiceCallback initCallback = ^(BOOL success, id result, NSString* error, NSInteger statusCode) {
        if (success) {
            NSLog(@"AppDelegate: initCallback success: %@", error);

            //[[Lootsie sharedInstance] achievementReachedWithId:@"first_x"];
            
            //[[LootsieManager sharedInstance] getAchievements];
            // cpp style call
            //LootsieManager::sharedInstance().getAchievements();
        } else {
            NSLog(@"AppDelegate: initCallback failure: %@", error);
        }
    };

    [[Lootsie sharedInstance] setLogLevel:verbose];

    // ttl 91BA8D7CF70420A628EABDFECB2E63F0D6CC4F9D256D978B1A7C0F209231CBD8
    // turbo race android on live - AC254671B2752EF9BF4F8ACA24F9F717B17B5BC900A233C4AE49DE215B6E8FE3
    [[Lootsie sharedInstance] initWithAppKeyCallback:@"AC254671B2752EF9BF4F8ACA24F9F717B17B5BC900A233C4AE49DE215B6E8FE3" callback:initCallback];

    [[Lootsie sharedInstance] setRenderingMode:landscape];
    
   	Lootsie *lootsie = [Lootsie sharedInstance];
   	lootsie->getControllerBlock = ^UIViewController* (void){
        // Change these example lines: get your viewcontroller instead.
//        id<UIApplicationDelegate> delegate =[UIApplication sharedApplication].delegate;
//        UIViewController * controller = [delegate window].rootViewController;
//       	NSLog(@"AppDelegate: overridden Lootsie getController: %@", controller.class);
//       	return controller; // You will return your viewcontroller here.
        
        UIViewController * controller = [[AppController sharedInstance] getRootViewController];
        NSLog(@"AppDelegate: overridden Lootsie getController: %@", controller.class);
        return controller;
    };
    
    [[AppController sharedInstance] init];

    // register for callbacks
    [[Lootsie sharedInstance] setDelegate:self];
    
    PlayGameSingleton::sharedInstance().initAd();
    cocos2d::CCApplication::sharedApplication()->run();
    
    return YES;
}

// Lootsie delegate method.  This is called when an achievement (Lootsie pop!) is expanded (Lootsie roll!).
- (void) achievementReachedBarExpanded
{
    NSLog(@"LootsieHybridApp: AppDelegate callback: Achievement reached and the Lootsie Pop has been expanded into a Lootsie Roll because the user tapped it!");
    cocos2d::CCDirector::sharedDirector()->pause();
    
}

// Lootsie delegate method.  This is called when an achievement page has been closed.
- (void) achievementReachedBarClosed
{
    NSLog(@"LootsieHybridApp: AppDelegate callback: Achievement page has been closed");
    cocos2d::CCDirector::sharedDirector()->resume();    
}


-(UIViewController*) getRootViewController {
    return viewController;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    cocos2d::CCDirector::sharedDirector()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
     cocos2d::CCDirector::sharedDirector()->purgeCachedData();
}


- (void)dealloc {
    [super dealloc];
}

- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation {
    
    return false;
}

@end