//  Created by Jumax.R on 11-12-3.
//  Copyright 2011 __MyCompanyName__. All rights reserved.


#import "Custom.h"
#import "ImageExtras.h"

@implementation Custom

+ (void)messageWithString:(NSString *)aString {

	UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"提示" message:aString delegate:nil cancelButtonTitle:nil otherButtonTitles:@"确定", nil];
	[alertView show];
	[alertView release];
}

+ (void)setBorder:(UIView *)sender {
	
	[sender.layer setBorderColor:COLOR_WITH_ARGB(1,1,1,0.3).CGColor];
	[sender.layer setMasksToBounds:YES];
	[sender.layer setCornerRadius:8];
	[sender.layer setBorderWidth:1];
}

+ (void)setShadow:(UIView *)sender {

	sender.layer.shadowOffset = CGSizeMake(0, 10);
	sender.layer.shadowOpacity = 1.1f;
	sender.layer.shadowColor = [UIColor blackColor].CGColor;
}

+ (UIButton *)createItemWithTitle:(NSString *)_tilte image:(NSString *)path target:(id)target action:(SEL)action {
	
    CGSize ImSize;
         ImSize.width=48;
        ImSize.height=30;
     
	UIImage *image =[[UIImage imageNamed:path]imageByScalingToSize:ImSize];// LOADIMAGE(path, @"png");
	
	UIButton	*button = [UIButton buttonWithType:UIButtonTypeCustom];
	[button		addTarget:target action:action forControlEvents:UIControlEventTouchUpInside];
	[button		setBackgroundImage:image forState:UIControlStateNormal];
	[button		setTitle:_tilte forState:UIControlStateNormal];
	[[button	titleLabel]setFont:FONT_WITH_SIZE(14)];
	[button		setFrame:CGRectMake(0, 0, image.size.width, image.size.height)];
	return		button;
}

+ (UILabel *)createLabelWithTitle:(NSString *)text {

	UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 150, 20)];
	label.backgroundColor = CLEARCOLOR;
	label.textAlignment = NSTextAlignmentCenter;
	label.text = text;
	label.font = [UIFont boldSystemFontOfSize:20];
	return [label autorelease];
}

+ (NSString *)getDocumentDir {

	return [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask,YES) objectAtIndex:0];
}

@end

@implementation UINavigationBar (clm)


- (void)drawRect:(CGRect)rect {

	[LOADIMAGE(@"navigation@2x", @"png") drawInRect:rect];
}

@end


@implementation Location

static CLLocationCoordinate2D currentCoors;

+ (void)setLocation:(CLLocationCoordinate2D)coors {

	currentCoors = coors;
}

+ (CLLocationCoordinate2D)location {

	return currentCoors;
}

@end