//
//  RegistrationTableViewCell.m
//  VideoSession
//
//  Created by liwei on 14-11-3.
//  Copyright (c) 2014年 zhangxm. All rights reserved.
//

#import "RegistrationTableViewCell.h"

@implementation RegistrationTableViewCell

- (void)awakeFromNib {
    // Initialization code
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

- (void)dealloc {
    [_textField release];
    [super dealloc];
}
@end
