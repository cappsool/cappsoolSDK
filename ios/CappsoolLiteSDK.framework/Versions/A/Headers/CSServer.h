//
//  CSServer.h
//  CappsoolLiteSDK
//
//  Created by Eyal Flato on 04/11/2015.
//  Copyright © 2015 Eyal Flato. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CSServer : NSObject
+(CSServer*) sharedInstance;
-(void) putIntegrationKey:(NSString *)integrationKey;
-(void) requestOffer:(NSString*)content;
-(NSString*) getQuickSuggestUrl:(NSString*)content;
@end
