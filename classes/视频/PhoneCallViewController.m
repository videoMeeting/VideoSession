//
//  MJSecondDetailViewController.m
//  MJPopupViewControllerDemo
//
//  Created by Martin Juhasz on 24.06.12.
//  Copyright (c) 2012 martinjuhasz.de. All rights reserved.
//

#import "PhoneCallViewController.h"

@interface PhoneCallViewController ()

@end

@implementation PhoneCallViewController

@synthesize delegate;
@synthesize accpetImage;
@synthesize accpetUserID;
@synthesize accpetInfo;

- (IBAction)BtAccept:(id)sender
{
    if (self.delegate && [self.delegate respondsToSelector:@selector(OKButtonClicked:)]) {
        [self.delegate OKButtonClicked:self];
    }
}
- (IBAction)BtRefuse:(id)sender
{
    if (self.delegate && [self.delegate respondsToSelector:@selector(cancelButtonClicked:)]) {
        [self.delegate cancelButtonClicked:self];
    }
}
 


@end
