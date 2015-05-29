//
//  BTEndlessTunnelAppController.h
//  BTEndlessTunnel
//
//  Created by NSS on 3/21/14.
//  Copyright __MyCompanyName__ 2014. All rights reserved.
//
#import "AppDelegate.h"


@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

+(AppController*) sharedInstance;
- (id) init;
-(UIViewController*) getRootViewController;
@end