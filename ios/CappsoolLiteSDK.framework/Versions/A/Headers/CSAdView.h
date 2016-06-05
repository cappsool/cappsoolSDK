//
//  CSAdView.h
//  CappsoolLiteSDK
//
//  Created by Eyal Flato on 04/11/2015.
//  Copyright © 2015 Eyal Flato. All rights reserved.
//

#import <UIKit/UIKit.h>

@class CSAdView;
@class CSAppVideoView;

@protocol CSAdViewDelegate <NSObject>
@optional
- (void) csAdViewReady:(nonnull CSAdView *)adView;
- (void) csAdDidClick:(nonnull CSAdView *)adViewController;
@end

@interface CSAdView : UIView

@property (nullable, nonatomic, assign) id <CSAdViewDelegate> csAdViewDelegate;
@property BOOL allowScroll;
-(void) load:(nonnull NSString*)htmlString;
-(void) reload;
@end
