//
//  MainViewController.h
//  Monitor
//
//  Created by huacai-mac on 12-10-19.
//  Copyright (c) 2012年 mac. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "CameraHelp.h"
#import "VideoLibrary.h"
#import "iOSGLView.h"
@interface VideoManagement : NSObject<CameraHelpDelegate>{
    bool transferBuffer;
    bool recordVideo;
    bool h264open;
    
    iOSGLView *m_pUIImageView;
    unsigned int m_uiBitRate;
    unsigned int m_uiFps;
    unsigned int m_uiWidth;
    unsigned int m_uiHeight;
    VideoCaptureDataCallBack* m_pVideoCaptureDataCallBack;
    bool bIsEncodingData;
}
@property bool transferBuffer;
@property bool recordVideo;
@property bool bIsEncodingData;

-(bool) tdav_codec_h264_open;
//-(void)CloseAllResouse;

-(void)Alert:(NSString*) result message:(NSString*) message;
-(void)strartTransfer;
-(void)StartTransferThread:(id)sender;
-(void)StopTransferThread:(id)sender;
-(void)setBackinitEncod:(id)sender;
-(void)setBack:(id)sender;

-(bool)StartCapture;
-(void)StopCapture;

-(bool)StartEncoding;
-(void)StopEncoding;
-(void)setPreview: (UIView*)preview;
-(void)SetLocalVideoWindow:(iOSGLView *)pUIImageView;
-(void)SetBitRate:(unsigned int)uiBitRate;
-(void)SetResolution:(unsigned int)uiWidth uiHeight:(unsigned int) uiHeight;
-(void)SetVideoFps:(unsigned int)uiFps;
-(void)SetCallBack:(VideoCaptureDataCallBack*)pVideoCaptureDataCallBack;
-(void)SetFrontAndRearCamera:(bool)isFront;

@end
