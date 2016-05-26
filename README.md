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
* In your view controller, in the desired location, create an instance of CSAdView and add it to the view. For example:
```
#import <CappsoolLiteSDK/CappsoolLiteSDK.h>

@interface ViewController () <CSAdViewDelegate>
...
@property (strong) CSAdView *csAdView;
@end

- (void)viewDidLoad {
    [super viewDidLoad];

    CSAdView* csAdView = [[CSAdView alloc] init];
    self.csAdView = csAdView;
    
    // Positions the ad at the bottom, with the correct size
    self.csAdView.frame = CGRectMake(0, self.view.bounds.size.height - 380, self.view.bounds.size.width, 380);
    [self.csAdView setHidden:true];
    [self.view addSubview:self.csAdView];

    
    // Loads the ad over the network
    [self.csAdView load:@"<placement>"];

}

- (void) csAdViewReady:(nonnull CSAdView *)adView {
    // show the ad only when it's ready
    [self.csAdView setHidden:false];
}
```





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
* Adding a CSAdViewListener to Activity: 
When the user touches an ad in your CSAdView, the regular behavior is for CSAdView to launch an default web browser that handles URLs. A CSAdViewListener is helping to CSAdView in order to do this through onStartExternalBrowser method. You should implement an abstract method onStartExternalBrowser in the your activity or fragment.

For example, here's a code in which the CSAdViewListener launches an default web browser:

```
public class MainActivity extends AppCompatActivity implements CSAdViewListener {
     private CSAdView mCsAdView;
     ...

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mCsAdView = (CSAdView) findViewById(R.id.banner_csadview);
        mCsAdView.setIntegrationKey("<Your integration key>"));
        mCsAdView.setAdListener(this);

        mCsAdView.load("<placement>");
    }

    @Override
    public void onStartExternalBrowser(Intent intent) {
        if (intent != null) {
            startActivity(intent);
        }
    }
}
```
