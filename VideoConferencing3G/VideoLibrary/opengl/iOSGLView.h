
#if TARGET_OS_IPHONE

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

@interface iOSGLView : UIView
{
    CAEAGLLayer* _eaglLayer;
    EAGLContext* _context;
    CADisplayLink* displayLink;
    GLuint _program;
    GLuint _renderBuffer;
    GLuint _framebuffer;
    GLuint _positionSlot;
    GLuint _texCoordSlot;
    GLuint _lumaUniform, _chromaUniformU, _chromaUniformV;
    GLuint _lumaTexture, _chromaTextureU, _chromaTextureV;
    CGFloat _screenWidth, _screenHeight;
    GLint _textureWidth, _textureHeight;
    GLuint _vertexShader, _fragmentShader;
    uint _bufferWidth, _bufferHeight, _bufferSize;
    uint8_t* _buffer;
    GLboolean _animating;
    GLuint _fps;
    bool isInitialize;
}
@property(retain,nonatomic) CADisplayLink* displayLink;
- (void)SetOpenglFrame:(CGRect)frame;
-(void)setFps:(GLuint)fps;
-(void)startAnimation;
-(void)stopAnimation;
-(void)setOrientation:(UIDeviceOrientation)orientation;
-(void)setBufferYUV:(const uint8_t*)buffer andWidth:(uint)bufferWidth andHeight:(uint)bufferHeight;
-(void)unInitialize;
@end

#endif /* #if TARGET_OS_IPHONE */