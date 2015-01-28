
//
//  CameraHelp.m
//  
//
//  Created by zcx. on 11-6-28.
//  Copyright 2011  . All rights reserved.
//
extern "C"
{
#import "libswscale/swscale.h"
#import "libavformat/avformat.h"
}

#import "CameraHelp.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<stdio.h>
#include<unistd.h> 
#import<AVFoundation/AVFoundation.h>

static bool isTakePhoto=NO;

static struct SwsContext *encodeimg_convert_ctx=NULL;
//static struct SwsContext *yuv2rgb_convert_ctx=NULL;
AVFrame *  pimageFrame=NULL;
AVFrame* encPictureout=NULL;
AVFrame*  ROTFrame = NULL;
//AVPicture  picture_rgb;
//int dstWidth=0;
//int  dstHeight=0;
static bool doing =NO;
uint8_t *picture_bufenc=NULL;
AVCaptureDevice * g_CaptureDevice=nil;
AVCaptureDevicePosition g_DevicePosition = AVCaptureDevicePositionUnspecified;

NSArray *cameras = [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
@interface CameraHelp (Private)
+(AVCaptureDevice *)cameraAtPosition:(AVCaptureDevicePosition)position;
-(void)startPreview;
-(void)stopPreview; 
@end  
 
@implementation CameraHelp  (Private)

+ (AVCaptureDevice *)cameraAtPosition:(AVCaptureDevicePosition)position{
	
    if(g_DevicePosition==position && g_CaptureDevice!=nil)
    {
        return g_CaptureDevice;
    }
    
    for (AVCaptureDevice *device in cameras){
        if (device.position == position){
            g_DevicePosition = position;
            g_CaptureDevice = device;
            return g_CaptureDevice;
        }
    }
    return [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
}

- (void)stopPreview{
	if(mCaptureSession){		
		if([mCaptureSession isRunning]){
			[mCaptureSession stopRunning];
			
			// remove all sublayers
			if(self.mPreview){
				for(CALayer *ly in self.mPreview.layer.sublayers){
					if([ly isKindOfClass: [AVCaptureVideoPreviewLayer class]])
					{
						[ly removeFromSuperlayer];
//                        [ly release];
                        ly=nil;
						break;
					}
				}
			}
		}
	}
}

- (void)startPreview{
	if(mCaptureSession && self.mPreview && mStarted){
		AVCaptureVideoPreviewLayer* previewLayer = [[[AVCaptureVideoPreviewLayer alloc ]initWithSession: mCaptureSession]autorelease];
	    CGRect            bounds=[self.mPreview bounds];
        if (previewLayer) {
            [previewLayer setFrame: bounds];
            previewLayer.videoGravity = AVLayerVideoGravityResize;
            
            [self.mPreview.layer addSublayer: previewLayer];
            if(![mCaptureSession isRunning]){
                [mCaptureSession startRunning];
            }
            
        }
        
		
		
	}
}

@end
static CameraHelp* g_camera = nil;
@implementation CameraHelp
@synthesize outDelegate;
@synthesize isoutPutBuffer;
@synthesize fileName;
@synthesize avCaptureVideoDataOutput;
@synthesize photoDelegate;
@synthesize mStarted;
@synthesize VideoName;
@synthesize VideoPath;
@synthesize imageName;
@synthesize imagePath;
@synthesize mHeight;
@synthesize mWidth;
@synthesize mPreview;
- (id)init
{
	if(g_camera)
		return g_camera;
	else
	{
		if(self = [super init])
		{
			self.mWidth = 320;
			self.mHeight = 240;
			self->mFps = 18;
			self->mFrontCamera = NO;
			self->mStarted = NO;
          	g_camera = self;
			self.outDelegate = nil;
            self.isoutPutBuffer=NO;
            self->avCaptureVideoDataOutput=nil;
           // self->audioOutput=nil;
            mCaptureDevice = nil;
            mStarted =NO;
            self.mPreview=nil;
            mCaptureSession=nil;
            self.fileName=@"";
		}
		return g_camera;
	}
}
-(void)initEncodeWith:(int)width hight:(int)hight
{
    encodeimg_convert_ctx = NULL;
   // yuv2rgb_convert_ctx=NULL;
    int sizeenc=0;
    m_bRecording=NO;
    encPictureout = av_frame_alloc();
    sizeenc = avpicture_get_size(PIX_FMT_YUV420P, width, hight);
    picture_bufenc=(uint8_t *)av_malloc(sizeenc);
    avpicture_fill((AVPicture*)encPictureout, picture_bufenc, PIX_FMT_YUV420P, width, hight);
    //avpicture_alloc(&picture_rgb,PIX_FMT_RGB24,320,240);
    pimageFrame = av_frame_alloc();
    self.mWidth=width;
    self.mHeight=hight;
     /*yuv2rgb_convert_ctx = sws_getContext(320, 240,
                                         PIX_FMT_YUV420P,
                                         320,240 ,
                                         PIX_FMT_RGB24,
                                         SWS_POINT, NULL, NULL, NULL);*/
}

-(void)dealloc
{
	[mCaptureSession release];
	[mCaptureDevice release];
    [avCaptureVideoDataOutput release];
    [VideoName release];
    [VideoPath release];
    [imageName release];
    [imagePath release];
    if(pimageFrame)
    { 
        av_free(pimageFrame);
        pimageFrame=NULL;
    }
    if(encPictureout)
    {
        av_free(encPictureout);
        encPictureout=NULL;
        
    }
    if (picture_bufenc) {
        av_free(picture_bufenc);
        picture_bufenc=NULL;
    }
    if (encodeimg_convert_ctx) {
        sws_freeContext(encodeimg_convert_ctx);
        encodeimg_convert_ctx=NULL;
    }
    
    /*if (yuv2rgb_convert_ctx) {
        sws_freeContext(yuv2rgb_convert_ctx);
        yuv2rgb_convert_ctx=NULL;
    }*/
    
    self.mPreview=nil;
	[super dealloc];
}

+(CameraHelp*)shareCameraHelp
{
	if(!g_camera)
		g_camera = [[CameraHelp alloc] init];
	return g_camera;
}

+(void)closeCamera
{
	if(g_camera)
	{
		[g_camera dealloc];
		g_camera = nil;
	}
}
 
-(void)prepareVideoCapture:(int) width andHeight: (int)height andFps: (int) fps andFrontCamera:(BOOL) bfront andPreview:(UIView*) view
{
	self->mWidth = width;
	self->mHeight = height;
	self->mFps = fps;
	self->mFrontCamera = bfront;
	if(view)
		self.mPreview =  view  ;
    
    [self initEncodeWith:width hight:height];
	if([mCaptureSession isRunning])
	{
		[self stopVideoCapture];
		[self startVideoCapture];
	}
}

-(void)setPreview:(UIView*)preview{
    
	if(preview == nil)
    {
		[self stopPreview];
        self.mPreview = nil;
        [self startPreview];
	}
	else
    {
        [self stopPreview];
		//[mPreview release];
        self.mPreview = preview;
        [self startPreview];
	}
}

-(NSString *)GetPhotoName
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    
    NSString *documentsDirectory = [paths objectAtIndex:0];
    
    NSDate *  senddate=[NSDate date];
    NSDateFormatter  *dateformatter=[[[NSDateFormatter alloc] init]autorelease];
    [dateformatter setDateFormat:@"HH:mm"];
    
    [dateformatter setDateFormat:@"YYYY-MM-dd-HH-mm-ss"];
    NSString *  morelocationString=[dateformatter stringFromDate:senddate];
    
    self.imagePath = [documentsDirectory stringByAppendingPathComponent:@"image/"];
    if (![[NSFileManager defaultManager] fileExistsAtPath:self.imagePath])
    {
        [[NSFileManager defaultManager] createDirectoryAtPath:self.imagePath withIntermediateDirectories:YES attributes:nil error:nil ];
    }
    
    NSString *fileNamet =[self.imagePath stringByAppendingPathComponent:morelocationString];
    self.imageName=[morelocationString  stringByAppendingString:@".jpg"] ;
    return  [fileNamet stringByAppendingString:@".jpg"] ;
}

-(void)startVideoCapture
{ 
    //防锁
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
    //打开摄像设备，并开始捕抓图像
    //[labelState setText:@"Starting Video stream"];
    if(mCaptureDevice || mCaptureSession)
    {
        NSLog(@"Already capturing");
        return;
    }
    
    if((mCaptureDevice = [CameraHelp cameraAtPosition:mFrontCamera? AVCaptureDevicePositionFront:AVCaptureDevicePositionBack]) == nil)
    {
        NSLog(@"Failed to get valide capture device");
        return;
    }
    
    NSError *error = nil;
    videoInput = [AVCaptureDeviceInput deviceInputWithDevice:mCaptureDevice error:&error];
    if (!videoInput)
    {
        NSLog(@"Failed to get video input");
        mCaptureDevice = nil;
        return;
    }
    
    mCaptureSession = [[AVCaptureSession alloc] init];
  //if(mHeight <= 144){
            // mCaptureSession.sessionPreset = AVCaptureSessionPresetLow;
     /*}
     else if(mHeight <= 360){*/
    mCaptureSession.sessionPreset = AVCaptureSessionPresetMedium;
  /* }
   else if(mHeight <= 480){
       mCaptureSession.sessionPreset = AVCaptureSessionPresetHigh;
   }
   else {
       mCaptureSession.sessionPreset = AVCaptureSessionPreset640x480;
   }*/
    [mCaptureSession addInput:videoInput];
    avCaptureVideoDataOutput =  [[AVCaptureVideoDataOutput alloc] init]  ;
    avCaptureVideoDataOutput.videoSettings = [[[NSDictionary alloc] initWithObjectsAndKeys:
                              [NSNumber numberWithUnsignedInt:kCVPixelFormatType_32BGRA], kCVPixelBufferPixelFormatTypeKey,nil]autorelease];
     
    avCaptureVideoDataOutput.alwaysDiscardsLateVideoFrames = YES;
  
    dispatch_queue_t queue = dispatch_queue_create("videoSession", NULL);
    [avCaptureVideoDataOutput setSampleBufferDelegate:self queue:queue];
    [mCaptureSession addOutput:avCaptureVideoDataOutput];
 
    dispatch_release(queue);
    mFirstFrame = YES;
    mStarted = YES;
    doing=NO;
    if(![mCaptureSession isRunning]){
        [mCaptureSession startRunning];
    }
    [self startPreview];
}

-(void)stopVideoCapture
{
	if(mCaptureSession){
        [mCaptureSession removeInput:videoInput];
		[mCaptureSession stopRunning];
		//[mCaptureSession release];
        mCaptureSession = nil;
        //videoInput = nil;
	}
    if (avCaptureVideoDataOutput) {
        //[avCaptureVideoDataOutput release];
        avCaptureVideoDataOutput=nil;
    }
    if(mCaptureDevice){
        
		//[mCaptureDevice release];
        mCaptureDevice = nil;
    }
   	if(mPreview){
		for (UIView *view in self.mPreview.subviews) {
			[view removeFromSuperview];
		}
	}
}

-(BOOL)setFrontCamera
{
	if(mFrontCamera)
		return YES;
	[self stopVideoCapture];
	mFrontCamera = YES;
	[self startVideoCapture];
	return YES;
}

-(BOOL)setBackCamera{
	if(!mFrontCamera)
		return YES;
	[self stopVideoCapture];
	mFrontCamera = NO;
	[self startVideoCapture];
	return YES;
}

-(void)setVideoDataOutputBuffer:(id<CameraHelpDelegate>)delegate
{ 
    if (delegate==nil) 
    {
        isoutPutBuffer=NO;
    }
    else
    {
        isoutPutBuffer=YES;
    }
    AVCaptureConnection *conn = [avCaptureVideoDataOutput connectionWithMediaType:AVMediaTypeVideo];
    conn.videoMaxFrameDuration=CMTimeMake(1, 20);
    conn.videoOrientation=AVCaptureVideoOrientationLandscapeRight;

	self.outDelegate = delegate;
}
 
-(void)TakePhoto
{
    isTakePhoto=YES;
}

-(UIImage *)imageFromAVPicture:(AVPicture *)pict  width:(int) width   height:(int )height

{
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
	CFDataRef data = CFDataCreateWithBytesNoCopy(kCFAllocatorDefault, pict->data[0], pict->linesize[0]*height,kCFAllocatorNull);
	CGDataProviderRef provider = CGDataProviderCreateWithCFData(data);
	CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
	CGImageRef cgImage = CGImageCreate(width, 
									   height, 
									   8, 
	 								   24, 
									   pict->linesize[0], 
									   colorSpace, 
									   bitmapInfo, 
									   provider, 
									   NULL, 
									   NO, 
									   kCGRenderingIntentDefault);
	CGColorSpaceRelease(colorSpace);
	UIImage *image = [UIImage imageWithCGImage:cgImage];
	CGImageRelease(cgImage);
	CGDataProviderRelease(provider);
	CFRelease(data);
	
	return image;
}

-(void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection 
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    
    if(doing==YES)
    {
        [pool release];
        return;
    }
    if(![mCaptureSession isRunning])
    {
        [pool release];
        return;
    }
   
    if( m_bRecording == YES )
    {
        CMTime lastSampleTime = CMSampleBufferGetPresentationTimeStamp(sampleBuffer);
        if( m_writer.status != AVAssetWriterStatusWriting  )
        {
            if (m_writer.status ==  AVAssetWriterStatusFailed)
            {
                NSLog(@"ERROR:%@\r\n", m_writer.error);
            }
            else
            {
                [m_writer startWriting];
                [m_writer startSessionAtSourceTime:lastSampleTime];
            }
        }

        if( captureOutput == avCaptureVideoDataOutput )
        {
            [self newVideoSample:sampleBuffer];
            // NSLog(@"i am video");
        }
        else 
        {
        }
    }
    
    CVImageBufferRef pixelBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    // Lock the image buffer
    if(CVPixelBufferLockBaseAddress(pixelBuffer, 0) == kCVReturnSuccess)
	{
        
        uint8_t *imageBuffer = (uint8_t *)CVPixelBufferGetBaseAddress( pixelBuffer);
        int width=(int)CVPixelBufferGetWidth(pixelBuffer);
        int hight=(int)CVPixelBufferGetHeight(pixelBuffer);
        
        if(!encodeimg_convert_ctx)
        {
        encodeimg_convert_ctx = sws_getContext(width, hight,
                                               PIX_FMT_BGRA,
                                               self.mWidth,self.mHeight ,
                                               PIX_FMT_YUV420P,
                                               SWS_POINT, NULL, NULL, NULL);
        }
        
	    if (isoutPutBuffer)// ||isTakePhoto
        {
            if(encodeimg_convert_ctx!=NULL)
            {
                avpicture_fill((AVPicture*)pimageFrame, imageBuffer, PIX_FMT_BGRA, width, hight);
                sws_scale (encodeimg_convert_ctx,  (pimageFrame->data), pimageFrame->linesize,
                           0, hight,
                           encPictureout->data, encPictureout->linesize);
                
                if (isoutPutBuffer) {
                    [self.outDelegate VideoDataOutputFrame:encPictureout  framewidth:self.mWidth framehight:self.mHeight];
                    
                }
               /*  if (isTakePhoto) {
                    if(yuv2rgb_convert_ctx!=NULL)
                    {
                        sws_scale ( yuv2rgb_convert_ctx,encPictureout->data, encPictureout->linesize, 0, 240 , picture_rgb.data, picture_rgb.linesize);            
                        
                        UIImage *image =[self imageFromAVPicture:&picture_rgb width:320 height:240];
                        
                        if ([ self.photoDelegate  respondsToSelector:@selector(AVCamCapturePhotoImage:)]) {
                            [ self.photoDelegate AVCamCapturePhotoImage:image];
                        } 
                        
                        [UIImageJPEGRepresentation(image, 1.0) writeToFile:[self GetPhotoName] atomically:YES];
                        
                        NSFileManager *fileManager = [NSFileManager defaultManager];
                        NSString *FullVideoPath=[self.imagePath stringByAppendingPathComponent:self.imageName] ;
                        
                        NSDictionary *fileAttributes = [fileManager attributesOfItemAtPath:FullVideoPath error:nil];
                        if (fileAttributes != nil) {
                            NSNumber *fileSize=0;
                            
                            //文件大小
                            if ((fileSize = [fileAttributes objectForKey:NSFileSize])) {
                                NSLog(@"File size: %qi\n", [fileSize unsignedLongLongValue]);
                            }
#if 0
                            MonitorAppDelegate *appDelegate = [[UIApplication sharedApplication] delegate];
                            
                            SendFileInfo mSendFileInfo;
                            mSendFileInfo.sfilePath = [self.imagePath UTF8String];
                            mSendFileInfo.sfilePath += "/";
                            mSendFileInfo.sfileName =[self.imageName UTF8String];
                            mSendFileInfo.sMId = "1234";
                            mSendFileInfo.sRtype = "file";
                            mSendFileInfo.sStartTime = "2012-12-16";
                            mSendFileInfo.ulSize = [fileSize intValue];
                            mSendFileInfo._strCompleteDate = "2012-12-16";
                            mSendFileInfo._strEndTime = "2012-12-16";
                            
                            appDelegate.mCFileUpLoad->SetFileFullPath(mSendFileInfo);
#endif
                            
                    } 
                    isTakePhoto=NO;
                    }
                }*/
            } 
        }
    }
    doing=NO;
    [pool release];
}

- (void)newVideoSample:(CMSampleBufferRef)sampleBuffer{
    if(m_bRecording)
    {
        if( m_writer.status > AVAssetWriterStatusWriting )
        {
            NSLog(@"Warning: writer status is %ld\r\n", (long)m_writer.status);
            if(m_writer.status == AVAssetWriterStatusFailed)
            {
                NSLog(@"Error: %@\r\n", m_writer.error);
            }
            return;
        }
        
        if (m_videoWriteInput.readyForMoreMediaData)
        {
            if(![m_videoWriteInput appendSampleBuffer:sampleBuffer])
            { 
                
                NSLog(@"Unable to write to video input\r\n");
            }
        }
        else
        {
            NSLog(@"video input readyForMoreMediaData is NO\r\n");
        }
    }
}

- (void)setUpWriter{
    NSError *error = nil;
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    //获取Temp目录
    
    NSString *documentsDirectory = [paths objectAtIndex:0];
    
    NSDate *  senddate=[NSDate date];
    NSDateFormatter  *dateformatter=[[NSDateFormatter alloc] init];
    [dateformatter setDateFormat:@"HH:mm"];
    
    [dateformatter setDateFormat:@"YYYY-MM-dd-HH-mm-ss"];
    NSString *  morelocationString=[dateformatter stringFromDate:senddate];
    
    self.VideoPath= [documentsDirectory stringByAppendingPathComponent:@"video/"];
    if (![[NSFileManager defaultManager] fileExistsAtPath:self.VideoPath])
    {
        [[NSFileManager defaultManager] createDirectoryAtPath:self.VideoPath withIntermediateDirectories:YES attributes:nil error:nil ];
    }
    
   // NSString *fileNamet =[filePath stringByAppendingPathComponent:morelocationString];
    self.VideoName  = [morelocationString stringByAppendingString:@".mp4"] ;
    [dateformatter release];
    
    NSString *FullVideoPath=[self.VideoPath stringByAppendingPathComponent:self.VideoName] ;
    
    
    NSURL *url = [NSURL fileURLWithPath:FullVideoPath];
    m_writer = [[AVAssetWriter alloc] initWithURL:url fileType:AVFileTypeMPEG4
                                            error:&error];
    NSParameterAssert(m_writer);
    
    
    NSDictionary *videoCleanApertureSettings = [NSDictionary dictionaryWithObjectsAndKeys:
                                                [NSNumber numberWithInt:self.mWidth], AVVideoCleanApertureWidthKey,
                                                [NSNumber numberWithInt:self.mHeight], AVVideoCleanApertureHeightKey,
                                                [NSNumber numberWithInt:10], AVVideoCleanApertureHorizontalOffsetKey,
                                                [NSNumber numberWithInt:10], AVVideoCleanApertureVerticalOffsetKey,
                                                nil];
    
    
    NSDictionary *codecSettings = [NSDictionary dictionaryWithObjectsAndKeys:
                                   [NSNumber numberWithInt:10],AVVideoMaxKeyFrameIntervalKey,
                                   AVVideoProfileLevelH264Main31,AVVideoProfileLevelKey,
                                   [NSNumber numberWithDouble:240.0*1024.0], AVVideoAverageBitRateKey,
                                   videoCleanApertureSettings, AVVideoCleanApertureKey,
                                   nil];
    
    
    
    NSDictionary *videoSettings = [NSDictionary dictionaryWithObjectsAndKeys:
                                   AVVideoCodecH264, AVVideoCodecKey,
                                   codecSettings,AVVideoCompressionPropertiesKey,
                                   [NSNumber numberWithInt:self.mWidth], AVVideoWidthKey,
                                   [NSNumber numberWithInt:self.mHeight], AVVideoHeightKey,
                                   nil];
    
    m_videoWriteInput = [[AVAssetWriterInput assetWriterInputWithMediaType:AVMediaTypeVideo
                                                            outputSettings:videoSettings] retain];
    NSParameterAssert(m_videoWriteInput);
    m_videoWriteInput.expectsMediaDataInRealTime = YES;
    
    [m_writer addInput:m_videoWriteInput];
}

-(void) startVideoRecording
{
    if( !m_bRecording )
    {
        NSLog(@"start video recording...");
        self.isoutPutBuffer=YES;
     
        [self setUpWriter];
        AVCaptureConnection *conn = [avCaptureVideoDataOutput connectionWithMediaType:AVMediaTypeVideo];
        conn.videoMaxFrameDuration=CMTimeMake(1, 20);
        conn.videoOrientation=AVCaptureVideoOrientationLandscapeRight;
        m_bRecording = YES;//AVCaptureVideoOrientationPortrait
    }
    
}

-(void) stopVideoRecording
{
    if( m_bRecording )
    {
        m_bRecording = NO;
        
        // [m_session stopRunning] ;
        
        if(![m_writer finishWriting])
        {
            NSLog(@"finishWriting returned NO") ;
        }
        AVCaptureConnection *conn = [avCaptureVideoDataOutput connectionWithMediaType:AVMediaTypeVideo];
        conn.videoMaxFrameDuration=CMTimeMake(1, 20);
        conn.videoOrientation=AVCaptureVideoOrientationLandscapeRight;
        
        isoutPutBuffer=NO;
       
       /* NSFileManager *fileManager = [NSFileManager defaultManager];
          NSString *FullVideoPath=[self.VideoPath stringByAppendingPathComponent:self.VideoName] ;
        
        NSDictionary *fileAttributes = [fileManager attributesOfItemAtPath:FullVideoPath error:nil];
          if (fileAttributes != nil) {
            NSNumber *fileSize=0;
        
            //文件大小
            if ((fileSize = [fileAttributes objectForKey:NSFileSize])) {
                NSLog(@"File size: %qi\n", [fileSize unsignedLongLongValue]);
            }
              
          MonitorAppDelegate *appDelegate = [[UIApplication sharedApplication] delegate];
        
        SendFileInfo mSendFileInfo;
        mSendFileInfo.sfilePath = [self.VideoPath UTF8String];
        mSendFileInfo.sfilePath += "/";
        mSendFileInfo.sfileName =[self.VideoName UTF8String];
        mSendFileInfo.sMId = "1234";
        mSendFileInfo.sRtype = "file";
        mSendFileInfo.sStartTime = "2012-12-16";
        mSendFileInfo.ulSize = [fileSize intValue];
        mSendFileInfo._strCompleteDate = "2012-12-16";
        mSendFileInfo._strEndTime = "2012-12-16";
        
        appDelegate.mCFileUpLoad->SetFileFullPath(mSendFileInfo);*/
        
   // }
    
   }
}

- (UIImage *) imageFromSampleBuffer:(CMSampleBufferRef) sampleBuffer
{
    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer); 
    CVPixelBufferLockBaseAddress(imageBuffer, 0); 
    void *baseAddress = CVPixelBufferGetBaseAddress(imageBuffer); 
    size_t bytesPerRow = CVPixelBufferGetBytesPerRow(imageBuffer); 
    size_t width = CVPixelBufferGetWidth(imageBuffer); 
    size_t height = CVPixelBufferGetHeight(imageBuffer); 
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB(); 
    
    CGContextRef context = CGBitmapContextCreate(baseAddress, width, height, 8, 
                                                 bytesPerRow, colorSpace, kCGBitmapByteOrder32Little | kCGImageAlphaPremultipliedFirst); 
    CGImageRef quartzImage = CGBitmapContextCreateImage(context); 
    CVPixelBufferUnlockBaseAddress(imageBuffer,0);
    CGContextRelease(context); 
    CGColorSpaceRelease(colorSpace);
    UIImage *image = [UIImage imageWithCGImage:quartzImage];
    CGImageRelease(quartzImage);
    
    return (image);
}
  
-(AVFrame*)alloc_picture:(enum PixelFormat) pix_fmt width:(int)width height:(int) height
{
    AVFrame *picture;
    uint8_t *picture_buf;
    int size;
    
    picture = av_frame_alloc();
    if (!picture)
        return NULL;
    size = avpicture_get_size(pix_fmt, width, height);
    picture_buf=(uint8_t *)av_malloc(size);
    if (!picture_buf) {
        av_free(picture);
        return NULL;
    }
    avpicture_fill((AVPicture *)picture, picture_buf,
                   pix_fmt, width, height);
    av_free(picture_buf);
    return picture;
}
 
@end
