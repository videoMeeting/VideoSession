#ifndef VideoSession_Middlelayer_h
#define VideoSession_Middlelayer_h

#include "WYSYSClient.h"

typedef std::vector<std::string> ENTERMEETINGUSER;

typedef enum{
	CS_CONNECTING=0,		//
	CS_FAILED,				//
	CS_CONNECTED,			//
	CS_DISCONNECTED,		//
	CS_BUSY,				//
	CS_RECONNECTED,			//
	CS_IDLE,				//
	CS_RESTARTED,			//
    CS_LOGINED,
    CS_LOGINFAILED,
    CS_GETUSERINFO,
    CS_GETUSERGROP,
    CS_GETFRIEND,
}CONNECT_STATUS;

@protocol IMLoginInfo
-(void) OnServerConnectingInfo:(CONNECT_STATUS)cs errorid:(unsigned int)errorid;
-(void) OnServerLoginingInfo:(CONNECT_STATUS)cs errorid:(unsigned int)errorid;
-(void) OnServerBeginGetUserInfo:(CONNECT_STATUS)cs ;
-(void) OnServerEndGetUserInfo;
-(void) OnServerConnectingOutTime;
@end

@protocol IMGetUserGroupInfo
-(void) OnInsertGroup:(const std::string&)strGroup nIndex:(unsigned int)nIndex;
-(void) OnDeleteGrop:(const std::string&)strGroup nIndex:(unsigned int)nIndex;
-(void) OnUpdateGroupName:(const std::string&)strOldGroup strNewGroup:(const std::string&)strNewGroup;
-(void) OnUpdateGroupIndex:(const std::string&)strGroup nIndex:(unsigned int)nIndex;
@end

@protocol IMGetUserFriendInfo
-(void) OnFriendAdd:(const std::string&)strGroup strUserId:(const std::string&)strUserId;
-(void) OnFriendDelete:(const std::string&)strGroup strUserId:(const std::string&)strUserId;

-(void) OnFriendOnLine:(const std::string&)strUserId;
-(void) OnFriendOffline:(const std::string&)strUserId;

-(void) OnFriendEnterInterimMeeting:(const std::string&)strUserId ulRoomID:(unsigned long)ulRoomID;
-(void) OnFriendQuitInterimMeeting:(const std::string&)strUserId ulRoomID:(unsigned long)ulRoomID;
@end

@protocol MMMeetingProtocol

-(void) OnCreateInterimMeeting:(std::string)strHostId ulRoomID:(unsigned long)ulRoomID uiRoomType:(unsigned int)uiRoomType;

-(void) OnHostInviteUser:(const std::string&)strUserID ulRoomID:(unsigned long)ulRoomID;

-(void) OnEnterInterimMeetingInfo:(unsigned long)ulRoomID;

-(void) OnDestructionInterimMeetingInfo:(std::string)strHostId ulRoomID:(unsigned long)ulRoomID;

-(void) OnQuitInterimMeetingInfo:(const std::string&)strUserID ulRoomID:(unsigned long)ulRoomID;

-(void) OnJoinTemporaryMeeting:(const std::string&)strUserID ulRoomID:(unsigned long)ulRoomID;

-(void) OnPleaseOutTemporaryMeeting:(const std::string&)strHostID ulRoomID:(unsigned long)ulRoomID strUserID:(const std::string&)strUserID;

@end

@protocol MMGetRoomControl

-(void) OnInitializationTemporaryMeeting:(const std::string&)strUserID ulRoomID:(unsigned long) ulRoomID uiScreenCount:(unsigned int)uiScreenCount uiVideoType:(unsigned int)uiVideoType uiAudioType:(unsigned int)uiAudioType;

-(void) OnOpenUserVideo:(std::string) strFromUserID strUserId:(std::string)strUserId ulRoomID:(unsigned long)ulRoomID ulUserVideoID:(unsigned long)ulUserVideoID uiScreenControl:(unsigned int)uiScreenControl;
-(void) OnCloseUserVideo:(std::string) strFromUserID strUserId:(std::string)strUserId ulRoomID:(unsigned long)ulRoomID ulUserVideoID:(unsigned long)ulUserVideoID;

-(void) OnOpenUserAudio:(std::string) strFromUserID strUserId:(std::string)strUserId ulRoomID:(unsigned long)ulRoomID ulUserAudioID:(unsigned long)ulUserAudioID;
-(void) OnCloseUserAudio:(std::string) strFromUserID strUserId:(std::string)strUserId ulRoomID:(unsigned long)ulRoomID ulUserAudioID:(unsigned long)ulUserAudioID;

-(void) OnMeetingType:(unsigned long)ulRoomID uiType:(unsigned int)uiType;
-(void) OnScreenControl:(std::string)strUserID ulRoomID:(unsigned long)ulRoomID uiScreenCount:(unsigned int)uiScreenCount;

-(void) OnForTheFloor:(const std::string&)strUserID ulRoomID:(unsigned long)ulRoomID strHostID:(const std::string&)strHostID;

-(void) OnPassPrivileges:(const std::string&)strHostID ulRoomID:(unsigned long)ulRoomID;

-(void) OnUserSnedMsg:(const std::string&)strUserID ulRoomID:(unsigned long)ulRoomID strPeerUserID:(const std::string&)strPeerUserID ulUserMsg:(std::string&)ulUserMsg;

-(void) OnUserReplyInviteUser:(const std::string&)strUserID ulRoomID:(unsigned long)ulRoomID bIsAgree:(bool)bIsAgree;

@end

#endif
