//
//  VideoSessionViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-1-8.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "VideoSessionViewController.h"
#import "SessionInfoViewController.h"
#import "SessionShowViewController.h"
#import "SessionChatViewController.h"
#import "sys/utsname.h"

static NSUInteger kNumberOfPages = 3;

@interface VideoSessionViewController ()


@end

@implementation VideoSessionViewController

@synthesize scrollView;
@synthesize sessionInfoViewController;
@synthesize sessionShowViewController;
@synthesize sessionChatViewController;
@synthesize sessionShowNavCtrl;
@synthesize sessionInfoNavCtrl;
@synthesize sessionChatNavCtrl;
@synthesize m_ViewCount;
 
+ (NSString*)deviceString
{
    // 需要#import "sys/utsname.h"
    struct utsname systemInfo;
    uname(&systemInfo);
    NSString *deviceString = [NSString stringWithCString:systemInfo.machine encoding:NSUTF8StringEncoding];
    
    if ([deviceString isEqualToString:@"iPhone1,1"])    return @"iPhone 1G";
    if ([deviceString isEqualToString:@"iPhone1,2"])    return @"iPhone 3G";
    if ([deviceString isEqualToString:@"iPhone2,1"])    return @"iPhone 3GS";
    if ([deviceString isEqualToString:@"iPhone3,1"])    return @"iPhone 4";
    if ([deviceString isEqualToString:@"iPhone4,1"])    return @"iPhone 4S";
    if ([deviceString isEqualToString:@"iPhone5,2"])    return @"iPhone 5";
    if ([deviceString isEqualToString:@"iPhone3,2"])    return @"Verizon iPhone 4";
    if ([deviceString isEqualToString:@"iPod1,1"])      return @"iPod Touch 1G";
    if ([deviceString isEqualToString:@"iPod2,1"])      return @"iPod Touch 2G";
    if ([deviceString isEqualToString:@"iPod3,1"])      return @"iPod Touch 3G";
    if ([deviceString isEqualToString:@"iPod4,1"])      return @"iPod Touch 4G";
    if ([deviceString isEqualToString:@"iPod5,1"])      return @"iPod Touch 5G";
   
    if ([deviceString isEqualToString:@"iPad1,1"])      return @"iPad";
    if ([deviceString isEqualToString:@"iPad2,1"])      return @"iPad 2 (WiFi)";
    if ([deviceString isEqualToString:@"iPad2,2"])      return @"iPad 2 (GSM)";
    if ([deviceString isEqualToString:@"iPad2,3"])      return @"iPad 2 (CDMA)";
    if ([deviceString isEqualToString:@"i386"])         return @"Simulator";
    if ([deviceString isEqualToString:@"x86_64"])       return @"Simulator";
    NSLog(@"NOTE: Unknown device type: %@", deviceString);
    return deviceString;
}
- (void) hideTabBar:(UITabBarController *) tabbarcontroller {
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationDuration:0.5];
    for(UIView *view in tabbarcontroller.view.subviews)
    {
        if([view isKindOfClass:[UITabBar class]])
        {
            [view setFrame:CGRectMake(view.frame.origin.x, 480, view.frame.size.width, view.frame.size.height)];
        }
        else
        {
            [view setFrame:CGRectMake(view.frame.origin.x, view.frame.origin.y, view.frame.size.width, 480)];
        }
    }
    [UIView commitAnimations];
}

- (void) showTabBar:(UITabBarController *) tabbarcontroller {
    
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationDuration:0.5];
    for(UIView *view in tabbarcontroller.view.subviews)
    {
        NSLog(@"%@", view);
        
        if([view isKindOfClass:[UITabBar class]])
        {
            [view setFrame:CGRectMake(view.frame.origin.x, 431, view.frame.size.width, view.frame.size.height)];
        }
        else
        {
            [view setFrame:CGRectMake(view.frame.origin.x, view.frame.origin.y, view.frame.size.width, 431)];
        }
    }
    
    [UIView commitAnimations];
}
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
//   NSString*str= [VideoSessionViewController deviceString];
    
//    if ([str isEqualToString:@"iPhone 5"]||[str isEqualToString:@"iPod Touch 5G"])
//    
//    {
//        self =[super initWithNibName:@"VideoSessionViewController_iphone5" bundle:nil];
//    }
//    else
//    {
        self =[super initWithNibName:@"VideoSessionViewController" bundle:nil];
//    }
    
   /* if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        self =[super initWithNibName:@"VideoSessionViewController_ipad" bundle:nil];
    } else {
        self =[super initWithNibName:@"VideoSessionViewController" bundle:nil];
    }
    */
    if (self) {
        // Custom initialization
        self.isBackCam=YES;
        m_ViewCount=0;
    }
    
    return self;
}

- (void)loadScrollViewWithPage:(int)page {
    if (page < 0) return;
    if (page >= kNumberOfPages) return;
    
    if (page==0) {
        CGRect frame = scrollView.frame;
        frame.origin.x = frame.size.width * page;
        frame.origin.y = 0;
        self.sessionInfoNavCtrl.view.frame = frame;
        [self.scrollView addSubview:self.sessionInfoNavCtrl.view];
        self.sessionInfoNavCtrl.view.translatesAutoresizingMaskIntoConstraints=YES;
        [self.sessionInfoNavCtrl.view removeConstraints:[self.sessionInfoNavCtrl.view constraints]];
        [self.sessionInfoNavCtrl.view updateConstraints];
        
        
    }
    else
        if (page==1)
        {
            CGRect frame = scrollView.frame;
            frame.origin.x = frame.size.width * page;
            frame.origin.y = 0;
            self.sessionShowNavCtrl.view.frame = frame;
            [self.scrollView addSubview:self.sessionShowNavCtrl.view];
            self.sessionInfoNavCtrl.view.translatesAutoresizingMaskIntoConstraints=YES;
            [self.sessionInfoNavCtrl.view removeConstraints:[self.sessionInfoNavCtrl.view constraints]];
            [self.sessionInfoNavCtrl.view updateConstraints];
        }
        else if (page==2)
        {
            CGRect frame = scrollView.frame;
            frame.origin.x = frame.size.width * page;
            frame.origin.y = 0;
            self.sessionChatNavCtrl.view.frame = frame;
            [self.scrollView addSubview:self.sessionChatNavCtrl.view];
            self.sessionInfoNavCtrl.view.translatesAutoresizingMaskIntoConstraints=YES;
            [self.sessionInfoNavCtrl.view removeConstraints:[self.sessionInfoNavCtrl.view constraints]];
            [self.sessionInfoNavCtrl.view updateConstraints];
        }
}

- (void)ScrollViewWithPage:(int)page 
{
    //self.pageControl.currentPage =1;
    CGRect frameSecond = scrollView.frame;
    frameSecond.origin.x = frameSecond.size.width * page;
    frameSecond.origin.y = 0;
    
    [self.scrollView scrollRectToVisible:frameSecond animated:YES];
}
- (void)scrollViewDidScroll:(UIScrollView *)sender {
    // We don't want a "feedback loop" between the UIPageControl and the scroll delegate in
    // which a scroll event generated from the user hitting the page control triggers updates from
    // the delegate method. We use a boolean to disable the delegate logic when the page control is used.
    
    // Switch the indicator when more than 50% of the previous/next page is visible
    CGFloat pageWidth = self.scrollView.frame.size.width;
    int page = floor((self.scrollView.contentOffset.x - pageWidth / 2) / pageWidth) + 1;
    
    if(page == 0)
    {
        [self.sessionShowViewController SetControlShow:false];
    }
    else if(page == 2)
    {
        [self.sessionShowViewController SetChatShow:false];
    }
    
    // load the visible page and the page on either side of it (to avoid flashes when the user starts scrolling)
    [self loadScrollViewWithPage:page - 1];
    [self loadScrollViewWithPage:page];
    [self loadScrollViewWithPage:page + 1];
    
    if (page==0) {
        //[self.ivPage1 setImage:[UIImage imageNamed:@"main_image_select"]];
        //[self.ivPage2 setImage:[UIImage imageNamed:@"main_image_unselect"]];
    }
    else if (page==1) {
        //[self.ivPage1 setImage:[UIImage imageNamed:@"main_image_unselect"]];
        //[self.ivPage2 setImage:[UIImage imageNamed:@"main_image_select"]];
    }
    
    m_ViewCount=page;
    // A possible optimization would be to unload the views+controllers which are no longer visible
}

// At the end of scroll animation, reset the boolean used when scrolls originate from the UIPageControl
-(void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView {
    pageControlUsed = NO;
}

-(void)BackPressed:(id)sender
{
    //  [self dismissViewControllerAnimated:NO completion:nil];
}

-(void)viewWillAppear:(BOOL)animated 
{
       [super viewWillAppear:animated];
    [[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:NO];
   [ self hideTabBar:self.tabBarController];
}

-(void)viewWillDisappear:(BOOL)animated
{
       [ self showTabBar:self.tabBarController];
    [[UIApplication sharedApplication] setStatusBarHidden:NO withAnimation:NO];
     [super viewWillDisappear:animated];
}

-(void)initViews
{
    int _screenWidth = [UIScreen mainScreen].bounds.size.width;
    int _screenHeight = [UIScreen mainScreen].bounds.size.height;
 
    CGRect  fbounds = [UIScreen mainScreen].bounds;
    if (fbounds.size.height>fbounds.size.width) {
        long abc=fbounds.size.width;
        fbounds.size.width=fbounds.size.height;
        fbounds.size.height=abc;
    }
    
    self.sessionInfoViewController=[[[SessionInfoViewController alloc]initWithNibName:@"SessionInfoViewController" bundle:nil]autorelease];
        self.sessionChatViewController=[[[SessionChatViewController alloc]initWithNibName:@"SessionChatViewController" bundle:nil]autorelease];
        self.sessionShowViewController=[[[SessionShowViewController alloc]initWithNibName:@"SessionShowViewController" bundle:nil]autorelease];
        self.sessionShowViewController.videoSessionViewController=self;
        self.sessionInfoViewController.videoSessionViewController=self;
        self.sessionChatViewController.videoSessionViewController=self;
        self.sessionChatViewController.sessionShowViewController =self.sessionShowViewController;

        self.sessionInfoViewController.sessionShowViewController = self.sessionShowViewController;
        self.sessionShowViewController.sessionChatViewController = self.sessionChatViewController;
        self.sessionShowViewController.sessionInfoViewController = self.sessionInfoViewController;
    
        self.sessionShowNavCtrl = [[[UISubNavigationController alloc] initWithRootViewController:sessionShowViewController]autorelease];
  
        self.sessionInfoNavCtrl=[[[UISubNavigationController alloc] initWithRootViewController:sessionInfoViewController]autorelease];
        self.sessionChatNavCtrl=[[[UISubNavigationController alloc] initWithRootViewController:sessionChatViewController]autorelease];
        
    
    [self.sessionShowViewController.view  setFrame:fbounds];
    [self.sessionShowViewController.view setBounds:fbounds];
    
    [self.sessionShowViewController.navigationController.view  setFrame:fbounds];
    [self.sessionShowViewController.navigationController.view setBounds: fbounds];

    [self.sessionShowViewController.navigationController.visibleViewController.view setFrame:fbounds];
//    [self.sessionShowViewController  splitScreen];
    self.sessionShowViewController. sessionShowNavCtrl=sessionShowNavCtrl;
    
    [self.sessionInfoViewController.view  setFrame:fbounds];
    [self.sessionInfoViewController.view setBounds:fbounds];
    
    [self.sessionInfoViewController.navigationController.view  setFrame:fbounds];
    [self.sessionInfoViewController.navigationController.view setBounds: fbounds];
    
    [self.sessionInfoViewController.navigationController.visibleViewController.view setFrame:fbounds];
      [self.sessionInfoViewController initToolBar];

    
    [self.sessionChatViewController.view  setFrame:fbounds];
    [self.sessionChatViewController.view setBounds:fbounds];
  
    [self.sessionChatViewController.navigationController.view  setFrame:fbounds];
    [self.sessionChatViewController.navigationController.view setBounds: fbounds];
        
         [self.sessionChatViewController.navigationController.visibleViewController.view setFrame:fbounds];
    
    
     [self.sessionChatViewController InitCtrs];
    
    
        self.navigationController.navigationBar.frame = CGRectMake(0, 0, self.navigationController.navigationBar.frame.size.width, self.navigationController.navigationBar.frame.size.height*2);
        
        [self.scrollView setFrame:CGRectMake(0,  0, _screenHeight,_screenWidth  )];
  
    [self.view  setFrame:CGRectMake(0, 0,_screenWidth,_screenHeight )];
    
    self.scrollView.pagingEnabled = YES;
    
    self.scrollView.contentSize = CGSizeMake(scrollView.frame.size.width*kNumberOfPages, scrollView.frame.size.height);
    
    self.scrollView.showsHorizontalScrollIndicator = NO;
    self.scrollView.showsVerticalScrollIndicator = NO;
    self.scrollView.scrollsToTop = NO;
    self.scrollView.delegate = self;
    
    //self.pageControl.numberOfPages = kNumberOfPages;
    //////设定初始页面
    //return;
    {
        //self.pageControl.currentPage =1;
        CGRect frameSecond = scrollView.frame;
        frameSecond.origin.x = frameSecond.size.width * 1;
        frameSecond.origin.y = 0;
        [self.scrollView scrollRectToVisible:frameSecond animated:YES];
    }
}

-(void)viewDidLoad
{
    [super viewDidLoad];
    [self initViews];
}

-(void)dealloc
{
    self.scrollView=nil;
    self.sessionInfoNavCtrl=nil;
    self.sessionChatNavCtrl=nil;
    self.sessionInfoViewController=nil;
    self.sessionShowViewController=nil;
    self.sessionChatViewController=nil;
    self.sessionShowNavCtrl=nil;
    [super dealloc];
}

- (void)MyUpdateMeetingInfo:(id)mid
{
    if(self.sessionInfoViewController!=nil)
        [self.sessionInfoViewController MyUpdateMeetingInfo:mid];
    
    if(self.sessionChatViewController!=nil)
        [self.sessionChatViewController MyUpdateMeetingInfo:mid];
}

- (void)PeerUserJoinTemporaryMeeting:(const std::string&)strUserID ulRoomID:(unsigned long)ulRoomID;
{
    if(self.sessionShowViewController!=nil)
        [self.sessionShowViewController PeerUserJoinTemporaryMeeting:strUserID ulRoomID:ulRoomID];
}

- (void)PeerQuitInterimMeetingInfo:(const std::string&)strUserID ulRoomID:(unsigned long)ulRoomID
{
    if(self.sessionShowViewController!=nil)
        [self.sessionShowViewController PeerQuitInterimMeetingInfo:strUserID ulRoomID:ulRoomID];
}

- (void)PeerDestructionInterimMeetingInfo
{
    if(self.sessionShowViewController!=nil)
        [self.sessionShowViewController PeerDestructionInterimMeetingInfo];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)SetInterfaceOrientation:(bool)isBack
{
    self.isBackCam=isBack;
    int _screenWidth = [UIScreen mainScreen].bounds.size.width;
    int _screenHeight = [UIScreen mainScreen].bounds.size.height;
    
    if (self.isBackCam) {
        self.view.transform = CGAffineTransformMakeRotation(M_PI/2);
        self.view.bounds = CGRectMake(0, 0, _screenHeight, _screenWidth);
        [[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationLandscapeRight];
    }
    else
    {
        self.view.transform = CGAffineTransformMakeRotation(M_PI*3/2);
        self.view.bounds = CGRectMake(0, 0, _screenHeight, _screenWidth);
        
        [[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationLandscapeLeft];
    }
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    if (self.isBackCam) {
        return interfaceOrientation==UIInterfaceOrientationLandscapeRight;
    }
    else
    {
        return interfaceOrientation==UIInterfaceOrientationLandscapeLeft;
    }
}

-(BOOL)shouldAutorotate
{
    return NO;
}

-(NSUInteger)supportedInterfaceOrientations
{
    if (self.isBackCam)
    {
        return  UIInterfaceOrientationMaskLandscapeRight;
    }
    else
    {
        return  UIInterfaceOrientationMaskLandscapeLeft;
    }
}

@end
