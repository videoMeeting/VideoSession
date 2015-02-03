//
//  MJSecondDetailViewController.h
//  MJPopupViewControllerDemo
//
//  Created by Martin Juhasz on 24.06.12.
//  Copyright (c) 2012 martinjuhasz.de. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol MJSecondPopupDelegate;


@interface PhoneCallViewController : UIViewController
{
    UIImageView *accpetImage;
    UILabel     *accpetUserID;
    UILabel     *accpetInfo;
}
@property (assign, nonatomic)id <MJSecondPopupDelegate>delegate;
@property (retain, nonatomic)IBOutlet UIImageView *accpetImage;
@property (retain, nonatomic)IBOutlet UILabel     *accpetUserID;
@property (retain, nonatomic)IBOutlet UILabel     *accpetInfo;

@end

@protocol MJSecondPopupDelegate<NSObject>
@optional
- (void)cancelButtonClicked:(PhoneCallViewController*)secondDetailViewController;
- (void)OKButtonClicked:(PhoneCallViewController*)secondDetailViewController;
@end