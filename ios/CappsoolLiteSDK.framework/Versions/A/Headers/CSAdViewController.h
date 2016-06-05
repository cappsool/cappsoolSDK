//
//  CSAdViewController.h
//  balloons
//
//  Created by Eyal Flato on 31/05/2016.
//  Copyright © 2016 cappsool. All rights reserved.
//

#import <UIKit/UIKit.h>


@class CSAdViewController;
@protocol CSAdViewControllerDelegate <NSObject>
@optional
- (void) csAdClosed:(nonnull CSAdViewController *)adViewController;
- (void) csAdDidClick:(nonnull CSAdViewController *)adViewController;
@end

@interface CSAdViewController : UIViewController

@property (nullable, nonatomic, assign) id <CSAdViewControllerDelegate> csAdViewControllerDelegate;
@property (nullable, strong) NSString *subject;
-(void) load:(nonnull NSString*)htmlString ;

@end
