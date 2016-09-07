#include "combine3dimagergb332.h"
#include <qdebug.h>

Combine3DImageRGB332::Combine3DImageRGB332(QObject* parent):Combine3DImageRGBA(parent)
{
    int size = 4096*4096;
    m_rgbtmp = (unsigned char *)malloc(size);
    if(m_rgbtmp==0){
        qDebug()<<tr("[%1,%2]Fail to malloc rgb332 buffer.\n").arg(__FUNCTION__).arg(__LINE__);
    }else{
        memset(m_rgbtmp,0,size);
    }

    setPreAlpha(false);
}

Combine3DImageRGB332::~Combine3DImageRGB332()
{
    if(m_rgbtmp){
        free(m_rgbtmp);
    }
}

bool Combine3DImageRGB332::convertBinToImage(QImage *dstImage, unsigned char *buffer, int len)
{
    bool ret = true;
    if(m_rgbtmp==0)return false;
    //convert the rgb332 to rgbx
    int width = dstImage->width();
    int height = dstImage->height();
    int rgbxlen = 4*width*height;
    convertRGBLocaltoRGBX(m_rgbtmp,buffer,dstImage->width(),dstImage->height());
    ret = Combine3DImageRGBA::convertBinToImage(dstImage,m_rgbtmp,rgbxlen);
    return ret;
}

bool Combine3DImageRGB332::interleavingLine(QImage *srcLeft, QImage *srcRight)
{
    bool ret = Combine3DImageRGBA::interleavingLine(srcLeft,srcRight);
    if(ret){
        int width = m_width;
        int height = m_height;
        float bpp = combineFMTBpp();
        int len = width*height*bpp;
        convertRGBXtoRGBLocal(m_rgbtmp,m_dstbuffer,width,height);
        memcpy(m_dstbuffer,m_rgbtmp,len);
        m_dstlen = len;
    }
    return ret;
}
bool Combine3DImageRGB332::interleavingPixelByPixel(QImage *srcLeft, QImage *srcRight)
{
    bool ret = Combine3DImageRGBA::interleavingPixelByPixel(srcLeft,srcRight);
    if(ret && m_rgbtmp){
        int width = m_width;
        int height = m_height;
        float bpp = combineFMTBpp();
        int len = width*height*bpp;
        convertRGBXtoRGBLocal(m_rgbtmp,m_dstbuffer,width,height);
        memcpy(m_dstbuffer,m_rgbtmp,len);
        m_dstlen = len;
    }else{
        ret = false;
    }
    return ret;
}
bool Combine3DImageRGB332::convertToRawData(QImage *srcImage)
{
    bool ret = Combine3DImageRGBA::convertToRawData(srcImage);
    int width = srcImage->width();
    int height = srcImage->height();
    float bpp = combineFMTBpp();
    int len = width*height*bpp;
    if(ret && m_rgbtmp){
        convertRGBXtoRGBLocal(m_rgbtmp,m_dstbuffer,width,height);
        memcpy(m_dstbuffer,m_rgbtmp,len);
        m_dstlen = len;
    }else{
        ret = false;
    }
    return ret;
}

bool Combine3DImageRGB332::convertLinearToTileBasedBuffer(unsigned char *dstbuffer,
                                                        unsigned char *srcbuffer,
                                                        int srclen,
                                                        int srcw, int srch)
{
    float bpp = combineFMTBpp();
    int stride = srcw*bpp;
    if((stride%256) || (srch%16)){
        qDebug()<<tr("[%1,%2]unsupported source image stride.")
                  .arg(__FILE__).arg(__LINE__);
        return false;
    }
    /*convert  section*/
    int w = stride/256;
    int h = srch/16;
    int num = w*h;
    unsigned char * ybuffer = srcbuffer;
    unsigned char * dstYbuffer = dstbuffer;
    for(int i=0;i<num;i++){
        //init data;
        int x = i % w;
        int y = i / w;
        unsigned char * linebuffer = ybuffer + y*stride*16+x*256;
        unsigned char * tlbbuffer = dstYbuffer + i*TILEBASEMEM_SIZE;
        for(int k=0;k<16;k++){
            memcpy(tlbbuffer+256*k,linebuffer+k*stride,256);
        }
    }
    return true;
}

void Combine3DImageRGB332::convertTilebasedToLinearBuffer(unsigned char *dstbuffer,
                                                        unsigned char *srcbuffer,
                                                        int tlblen,
                                                        int srcw,int srch)
{
    float bpp = combineFMTBpp();
    int stride = srcw*bpp;
    if(dstbuffer==0 || srcbuffer==0)return;

    /*convert Y to linear*/
    int w = stride/256;
    int h = srch/16;
    int num = w*h;
    for(int i=0;i<num;i++){
        int x = i%w;
        int y = i/w;
        unsigned char* tlbbuffer_y  = srcbuffer + i*TILEBASEMEM_SIZE;
        unsigned char *linebuffer_y = dstbuffer + y*stride*16+x*256;
        for(int k=0;k<16;k++){
            memcpy(linebuffer_y + k*stride,tlbbuffer_y+k*256,256);
        }
    }
}
void Combine3DImageRGB332::convertRGBLocaltoRGBX(unsigned char * rgbx,
                                               unsigned char * rgb332,
                                               int w,int h)
{
    int len = w*h*combineFMTBpp();
    swapEndian(rgb332,len);

    int src_index=0;
    int dst_index=0;
    unsigned char tmp;
    unsigned char * src;//rgb332
    unsigned char * dst;//rgbx
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            //set dest index
            dst_index = 4*(i*w+j);
            dst = rgbx + dst_index;
            //set src index
            src_index = i*w+j;
            src = rgb332 + src_index;

            //convert
            tmp =((*src) & 0xe0)>>5;//r
            dst[0] = tmp*256/8;
            tmp =((*src) & 0x1c)>>2;//g
            dst[1] = tmp*256/8;
            tmp =((*src) & 0x03);//b
            dst[2] = tmp*256/4;
            dst[3] = 0;
        }
    }
}
void Combine3DImageRGB332::convertRGBXtoRGBLocal(unsigned char *rgb332,
                                               unsigned char *rgbx,
                                               int w, int h)
{
    int src_index=0;
    int dst_index=0;
    unsigned char tmp;
    unsigned char * src;//to rgbx
    unsigned char * dst;//to rgb32
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++){
            src_index = 4*(i*w+j);
            src = rgbx + src_index;
            dst_index = i*w+j;
            dst = rgb332 + dst_index;
            //convert
            tmp = ((src[0]*8/256) << 5) | ((src[1]*8/256)<<2) | (src[2]*4/256);
            *dst = tmp;
        }
    }

    int len = w*h*combineFMTBpp();
    swapEndian(rgb332,len);
}

void Combine3DImageRGB332::swapEndian(unsigned char *buffer, int len)
{
#if 1
    int dstlen = len/2;
    unsigned char tmp;
    unsigned char * src;
    for(int i=0;i<dstlen;i++){
        src = buffer + 2*i;
        tmp = src[0];
        src[0] = src[1];
        src[1] = tmp;
    }
#endif
}
