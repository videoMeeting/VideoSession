//  Created by Jumax.R on 11-12-3.
//  Copyright 2011 __MyCompanyName__. All rights reserved.


#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <CoreLocation/CoreLocation.h>


@interface Custom : NSObject {

}

+ (void)messageWithString:(NSString *)aString;
+ (void)setBorder:(UIView *)sender;
+ (void)setShadow:(UIView *)sender;
+ (UIButton *)createItemWithTitle:(NSString *)_tilte image:(NSString *)path target:(id)target action:(SEL)action;
+ (NSString *)getDocumentDir;
+ (UILabel *)createLabelWithTitle:(NSString *)text;

@end

@interface UINavigationBar (clm)

- (void)drawRect:(CGRect)rect;

@end
 

@interface Location : NSObject {

}

+ (void)setLocation:(CLLocationCoordinate2D)coors;
+ (CLLocationCoordinate2D)location;

@end