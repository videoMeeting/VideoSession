//
//  CameraServer.m
//  Encoder Demo
//
//  Created by Geraint Davies on 19/02/2013.
//  Copyright (c) 2013 GDCL http://www.gdcl.co.uk/license.htm
//

#import "CameraCapture.h"
#import "AVEncoder.h"
//#import "RTSPServer.h"
 
static CameraCapture* theServer;

@interface CameraCapture  () <AVCaptureVideoDataOutputSampleBufferDelegate>
{
    AVCaptureSession* _session;
    AVCaptureVideoPreviewLayer* _preview;
    AVCaptureVideoDataOutput* _output;
    dispatch_queue_t _captureQueue;
    
    AVEncoder* _encoder;
    
//    RTSPServer* _rtsp;
}
@end


@implementation CameraCapture

+ (void) initialize
{
    // test recommended to avoid duplicate init via subclass
    if (self == [CameraCapture class])
    {
        theServer = [[CameraCapture alloc] init];
    }
}

+ (CameraCapture*) shareCameraCapture
{
    return theServer;
}

  OpenLocalUser *mOpenLocalUser;

- (void)setOpenLocalUser:( OpenLocalUser *)penLocalUser
{
       mOpenLocalUser=penLocalUser;
}

- (void) startup
{
    if (_session == nil)
    {
        NSLog(@"Starting up server");
        
        // create capture device with video input
        _session = [[AVCaptureSession alloc] init];
        AVCaptureDevice* dev = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
        AVCaptureDeviceInput* input = [AVCaptureDeviceInput deviceInputWithDevice:dev error:nil];
        [_session addInput:input];
        
        // create an output for YUV output with self as delegate
        _captureQueue = dispatch_queue_create("uk.co.gdcl.avencoder.capture", DISPATCH_QUEUE_SERIAL);
        _output = [[AVCaptureVideoDataOutput alloc] init];
        [_output setSampleBufferDelegate:self queue:_captureQueue];
        NSDictionary* setcapSettings = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithInt:kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange], kCVPixelBufferPixelFormatTypeKey,
                                        nil];
        _output.videoSettings = setcapSettings;
        [_session addOutput:_output];
        
        // create an encoder
        _encoder = [AVEncoder encoderForHeight:240 andWidth:320];
        [_encoder encodeWithBlock:^int(NSArray* data, double pts) {
            
            if (mOpenLocalUser) {
           int nNALUs = (int)[data count];
                for (int i = 0; i < nNALUs; i++)
                {
                    NSData* nalu = [data objectAtIndex:i];
                    bool iskey=NO;
                    unsigned char* pSource = (unsigned char*)[nalu bytes];
                    if ((pSource[0] & 0x1f) == 5)
                    {
                        iskey=YES;
                    }
                    mOpenLocalUser->On_MediaReceiverCallbackVideo(pSource , [nalu length], YES, 320, 240);
                    
                }
                
               
            }
 
            return 0;
        } onParams:^int(NSData *data) {
//            _rtsp = [RTSPServer setupListener:data];
            unsigned char* pSource = (unsigned char*)[data bytes];
            mOpenLocalUser->On_MediaReceiverCallbackVideo(pSource , [data length], YES, 320, 240);
            
            return 0;
        }];
        
        // start capture and a preview layer
        [_session startRunning];
        
        
        _preview = [AVCaptureVideoPreviewLayer layerWithSession:_session];
        _preview.videoGravity = AVLayerVideoGravityResizeAspectFill;
    }
}

- (void) captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection
{
    // pass frame to encoder
    [_encoder encodeFrame:sampleBuffer];
}

- (void) shutdown
{
    NSLog(@"shutting down server");
    if (_session)
    {
        [_session stopRunning];
        _session = nil;
    }
//    if (_rtsp)
//    {
//        [_rtsp shutdownServer];
//    }
    if (_encoder)
    {
        [ _encoder shutdown];
    }
}
 

- (AVCaptureVideoPreviewLayer*) getPreviewLayer
{
    return _preview;
}

@end
