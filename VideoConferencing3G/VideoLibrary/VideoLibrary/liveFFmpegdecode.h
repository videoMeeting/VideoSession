#ifndef _FFMPEGDECODE_H_
#define _FFMPEGDECODE_H_
#import <UIKit/UIKit.h>
extern "C"
{
#import "libavformat/avformat.h"
#import "libswscale/swscale.h"
#import "libavformat/avio.h"
}
#import "iOSGLView.h"
@protocol inoutDataDelegate;
 
@interface liveFFmpegdecode:NSObject 
{
    unsigned char** bmpbuffer;
    int markfound;
    int decryptflag;
    int copyoffset;
    int zeronum;
    unsigned char** yuvbuffer;
    long pixelsize;
    bool   g_bDecoding ;
    char* readbuffer;
    id otherLiveVideo;
   // id <inoutDataDelegate>	inout_delegate;
    AVPicture  picture_rgb;
    AVCodec *codec;
    AVCodecContext *cdecode;
    int  got_picture, len;
    AVFrame * pictureFrame;
    AVPacket avpkt;
    AVCodecParserContext* ps;
    struct SwsContext  * m_pSwsCtxDst;
    int readoffset;
    int parseoffset;
    int liveVideoutputWidth;
    int LiveVideoutputHeight;
    unsigned long m_ulCount;
    iOSGLView* m_pUIImageView;
    bool         m_IsDisplayVideo;
} 

@property (retain) id otherLiveVideo;
//@property (assign) id <inoutDataDelegate> inout_delegate;
@property bool g_bDecoding ;
@property int markfound;
@property int decryptflag;
@property int copyoffset;
@property int zeronum;
@property unsigned char** yuvbuffer;
@property long pixelsize;
@property char* readbuffer;
@property unsigned char** bmpbuffer;

-(int)Beginmpeg_decode_h264;
-(int)ffmpeg_decode_h264:(unsigned char*) ucbuffer Len:(int) buffer_size iCount:(int) iCount;
-(int)Endinmpeg_decode_h264;
-(void)ffmpeg_set_decodestate:(bool )bInDecoding;
-(UIImage *)imageFromAVPicture:(AVPicture *)pict  width:(int) width   height:(int )height;
-(void)SetResolution:(unsigned int) uiWidth uiHeight:(unsigned int) uiHeight;
-(void)SetLocalVideoWindow:(iOSGLView *)pUIImageView;

-(bool)StartDisplayVideo;
-(void)StopDisplayVideo;

@end
 
#endif
