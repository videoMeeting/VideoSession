

#import "VideoManagement.h"
#import "iOSGLView.h"
static int isencode=0; 
AVCodec * livecodec=NULL ;
AVCodecContext * liveContext=NULL;
#define TOOLBARTAG		200
#define TABLEVIEWTAG	300

@interface VideoManagement ()

@end 

@implementation VideoManagement
@synthesize transferBuffer;
@synthesize recordVideo;
@synthesize bIsEncodingData;

- (id)init
{
    self = [super init];
    if (self) {
        m_pUIImageView=nil;
        m_uiBitRate = 0;
        m_uiFps = 15;
        m_uiWidth = 0;
        m_uiHeight = 0;
        m_pVideoCaptureDataCallBack = NULL;
        h264open = NO;
    }
    self.bIsEncodingData = NO;
    return self;
}

- (void)dealloc
{
    m_pUIImageView=nil;
    m_uiBitRate = 0;
    m_uiFps = 0;
    m_uiWidth = 0;
    m_uiHeight = 0;
    m_pVideoCaptureDataCallBack = NULL;
    h264open = NO;
    [super dealloc];
}

-(bool)StartEncoding
{
    h264open=[self tdav_codec_h264_open];
    self.transferBuffer =NO;
    [self strartTransfer];
    return true;
}

-(void)StopEncoding
{
    [self tdav_codec_h264_close];
}

- (void) setPreview: (UIView*)preview
{
    [[CameraHelp shareCameraHelp] setPreview:preview];
    
}
-(bool)StartCapture
{
    [[CameraHelp shareCameraHelp] setVideoDataOutputBuffer:nil];
    [[CameraHelp shareCameraHelp] prepareVideoCapture:m_uiWidth andHeight:m_uiHeight andFps:m_uiFps andFrontCamera:NO andPreview:m_pUIImageView];
    
    //开始捕获
	[[CameraHelp shareCameraHelp] startVideoCapture];
    return true;
}

-(void)StopCapture
{
    if (self.recordVideo==YES) {
        [[CameraHelp shareCameraHelp]stopVideoRecording];
        self.recordVideo=NO;
    }
    [[CameraHelp shareCameraHelp] setVideoDataOutputBuffer:nil];
    self.transferBuffer =NO;
    
    [[CameraHelp shareCameraHelp] stopVideoCapture];
    [CameraHelp closeCamera];
}

-(IBAction)btnRec:(id)sender{
    
    if (!recordVideo) {
        self.recordVideo=YES;
        [[CameraHelp shareCameraHelp]startVideoRecording];
    }
    else
    {
        [[CameraHelp shareCameraHelp]stopVideoRecording];
        self.recordVideo=NO;
    }
}

-(void)SetLocalVideoWindow:( iOSGLView*)pUIImageView
{
    m_pUIImageView = pUIImageView;
}

-(void)SetBitRate:(unsigned int)uiBitRate
{
    m_uiBitRate = uiBitRate;
}

-(void)SetResolution:(unsigned int)uiWidth uiHeight:(unsigned int)uiHeight
{
    m_uiWidth = uiWidth;
    m_uiHeight = uiHeight;
}

-(void)SetVideoFps:(unsigned int)uiFps
{
    m_uiFps = uiFps;
}

-(void)SetCallBack:(VideoCaptureDataCallBack*)pVideoCaptureDataCallBack
{
    m_pVideoCaptureDataCallBack = pVideoCaptureDataCallBack;
}

-(void)SetFrontAndRearCamera:(bool)isFront
{
    if(isFront)
    {
        [[CameraHelp shareCameraHelp] setFrontCamera];
    }
    else
        [[CameraHelp shareCameraHelp] setBackCamera];
}

-(void)strartTransfer
{
    if (!self.transferBuffer)
    {
        [NSThread detachNewThreadSelector:@selector(StartTransferThread:) toTarget:self withObject:self];
    }
    else
    {
        [NSThread detachNewThreadSelector:@selector(StopTransferThread:) toTarget:self withObject:self];
    }
}

-(void)StopTransferThread:(id)sender
{
    self.transferBuffer =NO;
}

-(void)StartTransferThread:(id)sender
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    if (h264open) 
    {
        [self performSelectorOnMainThread:@selector(setBackinitEncod:) withObject:self  waitUntilDone:YES];
        [pool release];
        return; 
    } 
    else
    {
        [self performSelectorOnMainThread:@selector(setBack:) withObject:self  waitUntilDone:YES];
        [pool release];
        return; 
    }
}

-(void)setBackinitEncod:(id)sender
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    [[CameraHelp shareCameraHelp] setVideoDataOutputBuffer:self];
    self.transferBuffer =YES;
    [pool release];
}

-(void)setBack:(id)sender
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
   // [self CloseAllResouse ];
    self.transferBuffer =NO;
    [self Alert:@"现场上传失败" message:@"请稍后重新尝试"];
    [pool release];
}

static  long long framcount=0;

-(bool) tdav_codec_h264_open
{
    liveContext = avcodec_alloc_context3(livecodec);
    avcodec_get_context_defaults3(liveContext,livecodec);
    int cpuFlag=av_get_cpu_flags( );
    av_force_cpu_flags(cpuFlag);
    liveContext->codec_id = CODEC_ID_H264;
	liveContext->pix_fmt		= PIX_FMT_YUV420P;
	liveContext->time_base.num  = 1;
	liveContext->time_base.den  = m_uiFps;//18;
	liveContext->width = m_uiWidth;//320;
	liveContext->height = m_uiHeight;//240;
    liveContext->bit_rate=m_uiBitRate*1000;//150*1000;
	liveContext->refs = 1;
    liveContext->scenechange_threshold = 0;
    liveContext->me_subpel_quality = 0;
    liveContext->me_method = ME_EPZS;
    liveContext->trellis = 0;
    liveContext->qcompress = 0.4f;//0.6f;
	liveContext->me_range = 16;
	liveContext->max_qdiff = 4;
    liveContext->flags |=CODEC_FLAG_QSCALE
    |CODEC_FLAG2_FAST ; //
   	liveContext->max_b_frames = 0;
	liveContext->b_frame_strategy = 1;
	liveContext->chromaoffset = 0;
    liveContext->codec_type = AVMEDIA_TYPE_VIDEO;	 
    liveContext->profile = 66;
    liveContext->level = 13;
    liveContext->keyint_min=1;
    liveContext->thread_count = 0;
	//liveContext->rtp_payload_size = 900;
	liveContext->opaque = 0;
	liveContext->gop_size = 3;  
    livecodec = avcodec_find_encoder(liveContext->codec_id);
    
    if (!livecodec) {
        printf("avcodec_find_encoder error\n");
        
        return NO;
    }
    
    /* 打开视频解码器 */
    if (avcodec_open2(liveContext, livecodec,0) < 0) {
        printf("avcodec_open error\n");
        
        return NO;
    }
    framcount=0;
    return YES;	
    
}

-(int) tdav_codec_h264_close
{
    while(isencode==1)
    {
        usleep(100000);
    }
    if (liveContext) {
        avcodec_close(liveContext);
        av_free(liveContext);
        liveContext=NULL;
    }

    return 0;
}

-(void)VideoDataOutputFrame:(AVFrame *)pimageFrame framewidth:(int)framewidth framehight:(int)framehight
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init]; 
    
    if(self.transferBuffer && self.bIsEncodingData)
    {
        if(liveContext==NULL)
        {
            [pool release];
            return;
        }
        if(isencode==1)
        { 
            [pool release];
            return;
        }
        else
        {
            isencode=1;
        }
        
        int got_packet_ptr = 0; 
        AVPacket avpkt;  
        av_init_packet(&avpkt);  
        avpkt.data = NULL;  
        avpkt.size = 0;  
        
        pimageFrame->pts=framcount++;
        int out_size = avcodec_encode_video2(liveContext, &avpkt, pimageFrame, &got_packet_ptr);   
        
        if (out_size== 0) {
            if (avpkt.size>0) {
                
                if(m_pVideoCaptureDataCallBack)
                    m_pVideoCaptureDataCallBack->On_MediaReceiverCallbackVideo((unsigned char*)avpkt.data, avpkt.size, pimageFrame->key_frame == 1 ? true : false , m_uiWidth, m_uiHeight);
            }
        }
        av_free_packet(&avpkt);
        isencode=0;
    }
    [pool release];
}

-(void)Alert:(NSString*) result message:(NSString*) message
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:result message:message
                                                   delegate:self cancelButtonTitle:@"确定" otherButtonTitles: nil];
    [alert show];	
    [alert release];
}

@end
