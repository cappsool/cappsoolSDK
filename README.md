# CappsoolLiteSDK integration guide for iOS/Android

## iOS integration:

* Obtain an Integration key and placement strings from Cappsool
* Add CappsoolLiteSDK.framework to your XCode Project (drag and drop)
* Go to Project Settings -> General -> Linked Frameworks and Libraries and add AdSupport.framework
* Open info.plist and paste these lines (if not there earlier):
```
    <key>NSAppTransportSecurity</key>
    <dict>
        <key>NSAllowsArbitraryLoads</key>
        <true/>
    </dict>
```
* In <your>AppDelegate.m, add this line:
```
#import <CappsoolLiteSDK/CappsoolLiteSDK.h>
...
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
...
[[CSServer sharedInstance] putIntegrationKey:@"<Your integration key>"];
...
}
```
* (optional) Setup additional paramters to improve targeting:
```
[[CSServer sharedInstance] putUserGender:@"<male/female>"];
[[CSServer sharedInstance] putUserAge:@"<age>"];
```
### Requesting and ad - Option 1: interstitial


```
@interface ViewController () <CSServerDelegate>
@end

@implementation ViewController


- (void)viewDidLoad {
    [super viewDidLoad];
    ...
    [CSServer sharedInstance].csServerDelegate = self;
    [[CSServer sharedInstance] startLoading:@"interstitial"];
    ...
}

-(void) csAdReady:(CSServer *)csServer subject:(nullable NSString *)subject {
    if ([subject isEqualToString:@"interstitial"]) {
        // display the ad when it's ready, or whenever after that, according to the app behaviour
        [[CSServer sharedInstance] presentInterstitialAd:self];
    }
}
```

call [[CSServer sharedInstance] stopLoading] when the ad auto refresh is not needed any more.

### Requesting and ad - Option 2: custom view

```
@interface ViewController () <CSServerDelegate>
@end

@implementation ViewController


- (void)myMethod {
    ...
    [CSServer sharedInstance].csServerDelegate = self;
    [[CSServer sharedInstance] loadOnce:@"ad"];
    ...
}

-(void) csAdReady:(CSServer *)csServer subject:(nullable NSString *)subject {
    if ([subject isEqualToString:@"ad"]) {
        CGRect rect = CGRectMake(80,10,300,250);
        CSAdView *csAdView = [[CSServer sharedInstance] createAdView:rect subject:@"ad"];
        csAdView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleWidth;
        [self.view addSubview:self.csAdView];
    }
}
```
* Can be used as a banner as well.
* Make sure you have a way to close or hide the ad, if needed.





## Android integration:

* Obtain an Integration key and placement strings from Cappsool
* Add cappsool-lite-sdk jar file to your project.
* In order to initialize the SDK, add the following code to your onCreate function:
```
CSAdView myCsAdView = (CSAdView) findViewById(R.id.banner_csadview);
myCsAdView.setIntegrationKey("<Your integration key>");
```
Note: The <Your integration key> string should be replaced with your own integration key.  In case if you are going to use a number of ads in the project then you need to pass the integration key one time.
* Adding a CSAdView to the application:  simply include the <CSAdView> element in your activity layout. For example, here's a layout file in which the CSAdView  fills the ad on the screen:
```
<?xml version="1.0" encoding="utf-8"?>
<LinearLayout
    xmlns:android="http://schemas.android.com/apk/res/android"
    android:orientation="vertical"
    android:layout_width="match_parent"
    android:layout_height="match_parent" >

    <com.cappsool.lite.sdk.widget.CSAdView
        android:id="@+id/banner_csadview"
        android:layout_width="match_parent"
        android:layout_height="100dp">
    </com.cappsool.lite.sdk.widget.CSAdView>
</LinearLayout>
```
To load an ad in the CSAdView, use load(). For example:
```
CSAdView myCsAdView = (CSAdView) findViewById(R.id.banner_csadview);
myCsAdView.setIntegrationKey("<Your integration key>");
myCsAdView.load("<placement>");
```
Before this will work, however, your application must have access to the Internet. To get Internet access, request the INTERNET permission in your manifest file. For example:
```
<manifest ... >
    <uses-permission android:name="android.permission.INTERNET" />
    ...
</manifest>
```
* Adding a CSAdViewListener: 
To recieve a notification when the widget is ready to be displayed

```
myAdView.setAdListener(new CSAdViewListener() {

    @Override
    public void onWidgetLoaded() {
// Do something, such as:
        myAdView.setVisibility(View.VISIBLE);
    }
});
```
