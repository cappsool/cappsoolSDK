//
//  CSServer.h
//  CappsoolLiteSDK
//
//  Created by Eyal Flato on 04/11/2015.
//  Copyright © 2015 Eyal Flato. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "CSAppVideoView.h"
#import "CSAdView.h"

@class CSServer;

@protocol CSServerDelegate <NSObject>
@optional
- (void) csAdReady:(nonnull CSServer *)adManager subject:(nullable NSString*)subject;
- (void) csAdNoInventory:(nonnull CSServer *)adManager subject:(nullable NSString*)subject error:(nullable NSString*)error;
- (void) csAdDidClick:(nonnull CSServer *)adManager subject:(nullable NSString*)subject;
@end


@interface CSServer : NSObject
+(nonnull CSServer*) sharedInstance;

@property int logLevel;
@property (nullable, nonatomic, assign) id <CSServerDelegate> csServerDelegate;

-(void) putIntegrationKey:(nonnull NSString *)integrationKey;
-(nullable NSString*) getIntegrationKey;
-(void) putUserGender:(nonnull NSString *)gender;
-(void) putUserAge:(nonnull NSString *)age;
-(void) requestOffer:(nonnull NSString*)content;
-(nonnull NSString*) getQuickSuggestUrl:(nonnull NSString*)content;

-(void) startLoading:(nullable NSString*)subject;
-(void) stopLoading;
-(void) loadOnce:(nonnull NSString*)subject;
-(void) presentInterstitialAd:(nonnull UIViewController*)vc;
-(nullable CSAppVideoView *) createAppVideoView :(CGRect)frame subject:(nonnull NSString*)subject multiVideo:(BOOL)multiVideo;
-(nullable CSAdView *) createAdView :(CGRect)frame subject:(nonnull NSString*)subject;

@end

