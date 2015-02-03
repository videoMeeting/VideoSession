
#import "liveFFmpegdecode.h"
 
@implementation liveFFmpegdecode
@synthesize otherLiveVideo;
@synthesize markfound;
@synthesize decryptflag;
@synthesize copyoffset;
@synthesize zeronum;
@synthesize yuvbuffer;
@synthesize pixelsize;
@synthesize readbuffer;
@synthesize bmpbuffer;
@synthesize g_bDecoding;
 
#define INBUF_OTHERVIDEOSIZE 0

- (id)init
{
    self = [super init];
    if (self) {
        codec=NULL;
        pictureFrame=NULL;
        ps=NULL;
        readoffset=0;
        parseoffset=0;
        liveVideoutputWidth=320;
        LiveVideoutputHeight=240;
        m_pSwsCtxDst = NULL;
        m_pUIImageView = nil;
    }
    return self;
}

// Allocate RGB picture
-(UIImage *) imageFromAVPicture:(AVPicture *)pict  width:(int) width   height:(int )height;

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

-(int) Beginmpeg_decode_h264
{
    //av_register_all();
    
    avpicture_alloc(&picture_rgb,PIX_FMT_RGB24,liveVideoutputWidth,LiveVideoutputHeight);
  	codec = avcodec_find_decoder(CODEC_ID_H264);
	if (!codec) {
		return -1;
	}
    
	ps = av_parser_init(CODEC_ID_H264);
	if (!ps) {
		return -1;
	}
    
	cdecode= avcodec_alloc_context3(codec);
	if (!cdecode) {
		av_parser_close(ps);
        
		return -1;
	}
    
	pictureFrame= av_frame_alloc();
	if (!pictureFrame) {
		av_parser_close(ps);
     	avcodec_close(cdecode);
		av_free(cdecode);
        
		return -1;
	}
    
	if(codec->capabilities&CODEC_CAP_TRUNCATED)
		cdecode->flags|= CODEC_FLAG_TRUNCATED;  
    
 	if (avcodec_open2(cdecode, codec,0) < 0) {
		av_parser_close(ps);
        
		avcodec_close(cdecode);
		av_free(cdecode);
		av_free(pictureFrame);
        
		return -1;
	}
    m_IsDisplayVideo = false;
    
    return 0;
}

-(int) Endinmpeg_decode_h264
{
    m_IsDisplayVideo = false;
    if(m_pSwsCtxDst)
    {
        sws_freeContext(m_pSwsCtxDst);
        m_pSwsCtxDst=NULL;
    }
    if (picture_rgb.data) {
        avpicture_free(&picture_rgb);
    }
    
    if (ps) {
        av_parser_close(ps);
        ps=NULL;
    }
    
    if (cdecode) {
        avcodec_close(cdecode);
        av_free(cdecode);
        cdecode=NULL;
    }
    
    if (pictureFrame) {
        av_free(pictureFrame);
        pictureFrame=NULL;
    }
    
    return 0;
}

-(bool)StartDisplayVideo
{
    m_IsDisplayVideo = true;
    return true;
}

-(void)StopDisplayVideo
{
    m_IsDisplayVideo = false;
}

-(int) ffmpeg_decode_h264:(unsigned char*) ucbuffer Len:(int) buffer_size  iCount:(int) iCount
{
    NSAutoreleasePool *pooldecode= [[NSAutoreleasePool alloc] init];
    av_init_packet(&avpkt);
    avpkt.data = ucbuffer;
    avpkt.size = buffer_size;
    got_picture = 0;
    if(cdecode==NULL)
    {
        av_free_packet(&avpkt);
        [pooldecode release];
        return 0;
    }
    len = avcodec_decode_video2(cdecode, pictureFrame, &got_picture, &avpkt);
    if (len <= 0) 
    {
        av_free_packet(&avpkt);
        [pooldecode release];
        return 0;
    }
                
    if (got_picture) 
    {
        int xsize = avpicture_get_size(PIX_FMT_YUV420P,cdecode->width,cdecode->height);
        
        uint8_t *  out_data =(uint8_t *) malloc( xsize ) ;
        avpicture_layout((AVPicture *)pictureFrame,PIX_FMT_YUV420P,cdecode->width,cdecode->height,
                         out_data, xsize);
        
        
        if(self->m_pUIImageView)
            [self->m_pUIImageView setBufferYUV:out_data andWidth:cdecode->width andHeight:cdecode->height];
        free(out_data);

      /*  m_pSwsCtxDst= sws_getContext(cdecode->width,cdecode->height,PIX_FMT_YUV420P,liveVideoutputWidth,LiveVideoutputHeight,PIX_FMT_RGB24,SWS_POINT,NULL, NULL, NULL);
        sws_scale ( m_pSwsCtxDst,pictureFrame->data, pictureFrame->linesize, 0, cdecode->height , picture_rgb.data, picture_rgb.linesize);
                    
        if(m_pSwsCtxDst)
        {
            sws_freeContext(m_pSwsCtxDst);
            m_pSwsCtxDst=NULL;
        }
        
        UIImage * picture =[self imageFromAVPicture:&picture_rgb width:liveVideoutputWidth height:LiveVideoutputHeight];
        
        m_ulCount = iCount;
        
        if(m_IsDisplayVideo)
            [self performSelectorOnMainThread:@selector(outputdataImage:) withObject:picture   waitUntilDone:YES];*/
    }
    av_free_packet(&avpkt);
    [pooldecode release];
        
	return 0;
}

-(void) SetResolution:(unsigned int) uiWidth uiHeight:(unsigned int) uiHeight
{
    liveVideoutputWidth = uiWidth;
    LiveVideoutputHeight = uiHeight;
}

-(void)SetLocalVideoWindow:(iOSGLView *)pUIImageView
{
    m_pUIImageView = pUIImageView;
}

-(void)outputdataImage:(iOSGLView*)picture
{
    //if(m_pUIImageView!=nil)
     //   m_pUIImageView.image = picture;
    //[inout_delegate outputdata:picture iCount:m_ulCount];
}

-(void)dealloc
{
    m_pUIImageView = nil;
    [super dealloc];
}
-(void) ffmpeg_set_decodestate:(bool) bInDecoding  
{
    g_bDecoding = bInDecoding;
}
@end

