//
//  ImsContactItem.h
//  VideoSession
//
//  Created by zhangxm on 13-1-18.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <iostream>
@interface ImsContactItem : NSObject
{
    std::string userid;			// ’ ªßID
	std::string username;		// ’ ªß√˚≥∆
	int         userlevel;		// ”√ªßº∂±
	
	std::string gender;			// –‘±
	std::string age;			// ƒÍ¡‰
	std::string country;		// π˙º“
	std::string province;		//  °∑›º∞÷›
	std::string city;			// ≥« –
	std::string address;		// Õ®—∂µÿ÷∑
	std::string postcode;		// ” ±‡
	std::string phone;			// µÁª∞
	std::string email;			// µÁ”
	std::string show;			// public=π´ø™◊ ¡œ protected=Ωˆ¡™œµ»Àø…º˚ private=≤ªπ´ø™
    
	std::string group;			// ¡™œµ»ÀÀ˘ Ù◊È
	std::string initiator;		// ÃÌº”¡™œµ»Àµƒ∑¢∆»À
	std::string acceptflag;		// Ω” ’±Í÷æ: true=“— «¡™œµ»À false=ªπŒ¥≥…Œ™¡™œµ»À
	std::string smscode;		// ∏ˆ»À∂Ã–≈’ ∫≈
	std::string voipcode;		// voip’ ∫≈º∞√‹¬Î
    
	std::string svrid;			// ∑˛ŒÒ∆˜ID
	std::string svraddr;		// ∑˛ŒÒ∆˜µÿ÷∑
	unsigned short svrport;		// ∑˛ŒÒ∆˜∂Àø⁄
	std::string svrtype;		// ∑˛ŒÒ∆˜¿‡–Õ
    
	std::string nodeid;			// ¡™œµ»ÀNODEID
	std::string nataddr;		// NATµÿ÷∑
	std::string localaddr;		// ±æµÿµÿ÷∑
	unsigned short localport;	// ±æµÿ∂Àø⁄
	std::string termtype;		// À˘‘⁄÷’∂À¿‡–Õ
	std::string status;			// online offline busy away
    bool isseletct;
    bool isInRoom;
}
@property (nonatomic)std::string userid;			// ’ ªßID
@property (nonatomic)std::string username;		// ’ ªß√˚≥∆
@property (nonatomic)int         userlevel;		// ”√ªßº∂±
@property (nonatomic)bool        isseletct;
@property (nonatomic)bool        isInRoom;
@property (nonatomic)std::string gender;			// –‘±
@property (nonatomic)std::string age;			// ƒÍ¡‰
@property (nonatomic)std::string country;		// π˙º“
@property (nonatomic)std::string province;		//  °∑›º∞÷›
@property (nonatomic)std::string city;			// ≥« –
@property (nonatomic)std::string address;		// Õ®—∂µÿ÷∑
@property (nonatomic)std::string postcode;		// ” ±‡
@property (nonatomic)std::string phone;			// µÁª∞
@property (nonatomic)std::string email;			// µÁ”
@property (nonatomic)std::string show;			// public=π´ø™◊ ¡œ protected=Ωˆ¡™œµ»Àø…º˚ private=≤ªπ´ø™

@property (nonatomic)std::string group;			// ¡™œµ»ÀÀ˘ Ù◊È
@property (nonatomic)std::string initiator;		// ÃÌº”¡™œµ»Àµƒ∑¢∆»À
@property (nonatomic)std::string acceptflag;		// Ω” ’±Í÷æ: true=“— «¡™œµ»À false=ªπŒ¥≥…Œ™¡™œµ»À
@property (nonatomic)std::string smscode;		// ∏ˆ»À∂Ã–≈’ ∫≈
@property (nonatomic)std::string voipcode;		// voip’ ∫≈º∞√‹¬Î

@property (nonatomic)std::string svrid;			// ∑˛ŒÒ∆˜ID
@property (nonatomic)std::string svraddr;		// ∑˛ŒÒ∆˜µÿ÷∑
@property (nonatomic)unsigned short svrport;		// ∑˛ŒÒ∆˜∂Àø⁄
@property (nonatomic)std::string svrtype;		// ∑˛ŒÒ∆˜¿‡–Õ

@property (nonatomic)std::string nodeid;			// ¡™œµ»ÀNODEID
@property (nonatomic)std::string nataddr;		// NATµÿ÷∑
@property (nonatomic)std::string localaddr;		// ±æµÿµÿ÷∑
@property (nonatomic)unsigned short localport;	// ±æµÿ∂Àø⁄
@property (nonatomic)std::string termtype;		// À˘‘⁄÷’∂À¿‡–Õ
@property (nonatomic)std::string status;			// online offline busy away

@end
