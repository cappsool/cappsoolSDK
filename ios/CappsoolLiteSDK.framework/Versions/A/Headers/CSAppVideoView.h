//
//  CSAppVideoView.h
//  balloons
//
//  Created by Eyal Flato on 26/05/2016.
//  Copyright © 2016 cappsool. All rights reserved.
//

#import <UIKit/UIKit.h>


@class CSAppVideoView;

@protocol CSAppVideoViewDelegate <NSObject>
@optional
- (void) csAppVideoViewReady:(nonnull CSAppVideoView *)adView;
@end


@interface CSAppVideoView : UIView
@property (nullable, nonatomic, assign) id <CSAppVideoViewDelegate> csAppVideoViewDelegate;

-(void) loadApps:(nonnull NSArray *)apps;
@end
