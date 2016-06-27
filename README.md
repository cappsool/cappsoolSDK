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
* In order to initialize the SDK, add the following code to your Activity:
```
CSAdWidget mCSAdWidget = CSAdWidget.getInstance(this, "<Some uniqe key>");
mCSAdWidget.setIntegrationKey("<Your integration key>")
```
Notes: The \<Your integration key\> string should be replaced with your own integration key.  
The \<uniqe key\> that is passed to the CSAdWidget is a random key that you choose for every ad that you have in the project.
In case you are going to use a number of ads in the project then you need to re-initialize the SDK for each ad with a different uniqe key, but with the same integration key.

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
In order to initialize the CSAdView, use this:
```
CSAdView mCsAdView = mCSAdWidget.prepareWebView((CSAdView) findViewById(R.id.banner_csadview));
```
* Adding a CSAdViewListener:
You can also set a CSAdViewListener to recieve notifications about the widget, such as:
onWidgetLoaded- when the widget in done loading,
or onNoServing- when the widget is not going to be loaded at all because of some error.
Use this code:
```
mCSAdWidget.setAdListener(new CSAdWidgetListener() {
    @Override
    public void onWidgetLoaded() {
    }
    
    @Override
    public void onNoServing(String reason) {
    }
});
```
To load an ad, use load(). For example:
```
mCSAdWidget.load("<Placement>", <callEventsOnEveryLoadCall: true|false>);
```
Notes: \<Placement\> - Is the placement string you obtained from Cappsool.
callEventsOnEveryLoadCall - When you're using the CSAdWidgetListener you might want to get the events notifications on each load() call, even if the loading was suspended from some reason. for example: When the orientation changes, the widget handles whether a load() was called for no reason, suspends the loading and keeps showing the old adView. In that case you might want to get your notifications again, or not. Use the true/false parameter.


Before this will work, however, your application must have access to the Internet. To get Internet access, request the INTERNET permission in your manifest file. For example:
```
<manifest ... >
    <uses-permission android:name="android.permission.INTERNET" />
    ...
</manifest>
```

Finaly, if you know that you're about to leave the page in which the ad is placed, it's recommended to use the destroyAdWidget() function in order to make sure it will be loaded as new in the next page view.
Use this code when you're leaving the page:
```
mCSAdWidget.destroyAdWidget();
```
