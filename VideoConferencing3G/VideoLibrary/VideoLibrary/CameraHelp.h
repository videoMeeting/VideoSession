//
//  CameraHelp.h
//  
//
//  Created by Zhuang Chuan Xian. on 11-6-28.
//  Copyright 2011  . All rights reserved.
//
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

extern "C"
{
#import "libswscale/swscale.h"
#import  "libavformat/avformat.h"
    
}
@protocol CameraHelpDelegate
-(void)VideoDataOutputFrame:(AVFrame *)pimageFrame framewidth:(int)framewidth framehight:(int)framehight;
@end
@protocol AVCamCapturePhotoDelegate;

@interface CameraHelp : NSObject
<AVCaptureVideoDataOutputSampleBufferDelegate,AVCaptureAudioDataOutputSampleBufferDelegate>
{
    int mWidth;
	int mHeight;
@private

	int mFps;
	BOOL mFrontCamera;
	BOOL mFirstFrame;
	bool mStarted;
    UIView* mPreview;
 	AVCaptureSession* mCaptureSession;
	AVCaptureDevice *mCaptureDevice;
    AVCaptureVideoDataOutput *avCaptureVideoDataOutput;
    id<CameraHelpDelegate> outDelegate;
    id <AVCamCapturePhotoDelegate> photoDelegate;
    bool isoutPutBuffer;
    NSString *VideoName;
    NSString *VideoPath;
    NSString *imageName;
    NSString *imagePath;
    AVAssetWriter*  m_writer  ;
    AVAssetWriterInput* m_videoWriteInput ;  
    bool m_bRecording;
    AVCaptureDeviceInput *videoInput;
}
@property (nonatomic)int mWidth;
@property (nonatomic)int mHeight;
@property (assign,nonatomic)UIView* mPreview;
@property (retain,nonatomic)NSString *VideoName;
@property (retain,nonatomic)NSString *VideoPath;
@property (retain,nonatomic)NSString *imageName;
@property (retain,nonatomic)NSString *imagePath;
@property (retain,nonatomic)id<CameraHelpDelegate> outDelegate;
@property (nonatomic,assign)id <AVCamCapturePhotoDelegate> photoDelegate;
@property bool isoutPutBuffer;
@property (nonatomic,retain)NSString *fileName;
@property (nonatomic,retain)AVCaptureVideoDataOutput *avCaptureVideoDataOutput;
@property bool mStarted;
@property (retain,nonatomic)NSString *filePath;
//单例模式
+ (CameraHelp*)shareCameraHelp;
+ (void)closeCamera;
//设置前置摄像头
- (BOOL)setFrontCamera;
//设置后置摄像头
- (BOOL)setBackCamera;
//开始前设置捕获参数
//开始前设置捕获参数
- (void)prepareVideoCapture:(int) width andHeight: (int)height andFps: (int) fps andFrontCamera:(BOOL) bfront andPreview:(UIView*) view;
//开始捕获
- (void)startVideoCapture;
//停止捕获
- (void)stopVideoCapture;
- (void)TakePhoto;
- (void) setPreview: (UIView*)preview;
//设置要显示到得View
- (NSString *)GetPhotoName;
- ( AVFrame *)alloc_picture:(enum PixelFormat) pix_fmt width:(int)width height:(int) height;
 //设置数据输出
- (void)setVideoDataOutputBuffer:(id<CameraHelpDelegate>)delegate;
- (UIImage *) imageFromSampleBuffer:(CMSampleBufferRef) sampleBuffer;
- (void) startVideoRecording;
- (void) stopVideoRecording;
- (void)setUpWriter;
-(void)initEncodeWith:(int)width hight:(int)hight;
- (void)newVideoSample:(CMSampleBufferRef)sampleBuffer;
-(UIImage *) imageFromAVPicture:(AVPicture *)pict  width:(int) width   height:(int )height;
@end

@protocol AVCamCapturePhotoDelegate <NSObject>
@optional
 
- (void) AVCamCapturePhotoImage:(UIImage *)image;
@end