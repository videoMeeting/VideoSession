//
//  CameraServer.h
//  Encoder Demo
//
//  Created by Geraint Davies on 19/02/2013.
//  Copyright (c) 2013 GDCL http://www.gdcl.co.uk/license.htm
//

#import <Foundation/Foundation.h>
#import "AVFoundation/AVCaptureSession.h"
#import "AVFoundation/AVCaptureOutput.h"
#import "AVFoundation/AVCaptureDevice.h"
#import "AVFoundation/AVCaptureInput.h"
#import "AVFoundation/AVCaptureVideoPreviewLayer.h"
#import "AVFoundation/AVMediaFormat.h"
#include "OpenLocalUser.h"
@protocol CameraCaptureDelegate
-(void)VideoDataOutputFrame:(NSData *)pimageFrame framewidth:(int)framewidth framehight:(int)framehight;
@end
@interface CameraCapture : NSObject

{
    OpenLocalUser *mOpenLocalUser;
}
+ (CameraCapture*) shareCameraCapture;
@property id<CameraCaptureDelegate>  delegate;
- (void) startup;
- (void) shutdown;
- (void)setOpenLocalUser:( OpenLocalUser *)penLocalUser;
- (AVCaptureVideoPreviewLayer*) getPreviewLayer;

@end
