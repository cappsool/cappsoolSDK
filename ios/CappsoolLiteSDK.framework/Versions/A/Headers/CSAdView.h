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
@end

@interface CSAdView : UIView

@property (nullable, nonatomic, assign) id <CSAdViewDelegate> csAdViewDelegate;

-(void) load:(nullable NSString*)content;
-(nullable NSArray*) getSuggestedApps;
-(nullable CSAppVideoView *) createAppVideoView :(CGRect)frame;

@end
