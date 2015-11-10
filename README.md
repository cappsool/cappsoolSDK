# cappsoolSDK

CappsoolLiteSDK integration guide for iOS

1. Obtain an Integration key from Cappsool
2. add CappsoolLiteSDK.framework to your XCode Project (drag and drop)
3. Go to Project Settings -> General -> Linked Frameworks and Libraries and add AdSupport.framework
4. Open info.plist and paste these lines (if not there earlier):

```
    <key>NSAppTransportSecurity</key>
    <dict>
        <key>NSAllowsArbitraryLoads</key>
        <true/>
    </dict>
```

5. In <your>AppDelegate.m, add the bold lines:

```
#import <CappsoolLiteSDK/CappsoolLiteSDK.h>
...
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
...
[[CSServer sharedInstance] putIntegrationKey:@"<Your integration key>"];
...
}
```

6. In your view controller, in the desired location, create an instance of CSAdView and add it to the view. For example:

```
#import <CappsoolLiteSDK/CappsoolLiteSDK.h>

@interface ViewController () 
...
@property (strong) CSAdView *csAdView;
@end

- (void)viewDidLoad {
    [super viewDidLoad];

    CSAdView* csAdView = [[CSAdView alloc] init];
    self.csAdView = csAdView;
    
    // Positions the ad at the bottom, with the correct size
    self.csAdView.frame = CGRectMake(0, self.view.bounds.size.height - 380, self.view.bounds.size.width, 380);
    [self.view addSubview:self.csAdView];
    
    // Loads the ad over the network
    [self.csAdView load:@"<Size and Location description>"];

}
```
7. Size and Location Description should be letters only string. For example: mainScreenBottomBanner, listItemMedium, etc. These text will later help us configure the appearance of the ad through Cappsool’s servers. 
8. CSAdView size should generally span the entire width of the device (portrait mode) and have an height of:
- 380px : large ad, suitable for a list  or a scroll view
- 240px : medium ad, suitable as a big banner or in a list or a scroll view
- 100px/80px : banner, or small list item


