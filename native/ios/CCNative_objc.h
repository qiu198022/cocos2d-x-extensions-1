
#import <Foundation/Foundation.h>
#include "CCAlertViewDelegate.h"
#include "CCScriptSupport.h"

using namespace cocos2d;
using namespace extensions;

@interface CCNative_objc : NSObject < UIAlertViewDelegate >
{
    UIActivityIndicatorView *activityIndicatorView_;
    
    UIAlertView *alertView_;
    CCAlertViewDelegate *alertViewDelegates_;
    LUA_FUNCTION alertViewLuaListener_;
}

+ (CCNative_objc *)sharedInstance;


#pragma mark -
#pragma mark activity indicator

- (void)showActivityIndicator:(UIActivityIndicatorViewStyle)style;
- (void)hideActivityIndicator;


#pragma mark -
#pragma mark alert view

- (void)createAlertView:(NSString *)title
             andMessage:(NSString *)message
   andCancelButtonTitle:(NSString *)cancelButtonTitle;
- (NSInteger)addAlertButton:(NSString *)buttonTitle;
- (void)showAlertViewWithDelegate:(CCAlertViewDelegate *)delegate;
- (void)showAlertViewWithLuaListener:(LUA_FUNCTION)listener;
- (void)removeAlertView;
- (void)removeAlertViewLuaListener;
- (void)cancelAlertView;

#pragma mark -
#pragma mark UIAlertView delegates

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex;
- (void)alertViewCancel:(UIAlertView *)alertView;

@end
