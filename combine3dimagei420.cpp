#include "combine3dimagei420.h"
#include <QDebug>
Combine3DImageI420::Combine3DImageI420(QObject* parent):
    Combine3DImageNV12(parent)
{}
bool Combine3DImageI420::interleavingLine(QImage *srcLeft, QImage *srcRight)
{
    bool ret;
    unsigned char * bgrx;
    int len;
    m_dstlen = m_width*m_height*3/2;

    //step 1 convert to bgrx
    ret = m_combBgrx.generate3DImageBin(srcLeft,srcRight,INTERLEAVE_LINE);
    if(!ret){
        qDebug()<<tr("[%1,%2]Fail to convert the image into bgrx format.").arg(__FUNCTION__).arg(__LINE__);
        return false;
    }
    //step 2 convert to nv12;
    bgrx = m_combBgrx.data();
    len = m_combBgrx.datasize();
    m_rgbToYuv.convertBGRXtoI420(m_dstbuffer,bgrx,m_width,m_height);

    return true;
}

bool Combine3DImageI420::interleavingPixelByPixel(QImage *srcLeft, QImage *srcRight)
{
    bool ret;
    unsigned char * bgrx;
    int len;
    m_dstlen = m_width*m_height*3/2;

    //step 1 convert to bgrx
    ret = m_combBgrx.generate3DImageBin(srcLeft,srcRight,INTERLEAVE_PIXEL_BY_PIXEL);
    if(!ret){
        qDebug()<<tr("[%1,%2]Fail to convert the image into bgrx format.").arg(__FUNCTION__).arg(__LINE__);
        return false;
    }

    //step 2 convert to nv12;
    bgrx = m_combBgrx.data();
    len = m_combBgrx.datasize();
    m_rgbToYuv.convertBGRXtoI420(m_dstbuffer,bgrx,m_width,m_height);

    return true;
}

bool Combine3DImageI420::convertToRawData(QImage *srcImage)
{
    bool ret;
    unsigned char * bgrx;
    int len;
    int width = srcImage->width();
    int height = srcImage->height();
    m_dstlen = width * height * 3 / 2;

    //step 1 convert to bgrx
    ret = m_combBgrx.generate2DImageBin(srcImage);
    if(!ret){
        qDebug()<<tr("[%1,%2]Fail to convert the image into bgrx format.").arg(__FUNCTION__).arg(__LINE__);
        return false;
    }

    //step 2 convert to nv12;
    bgrx = m_combBgrx.data();
    len = m_combBgrx.datasize();
    m_rgbToYuv.convertBGRXtoI420(m_dstbuffer,bgrx,width,height);

    return true;
}

bool Combine3DImageI420::loadBinToImage(QImage *dstImage, unsigned char *buffer, int len)
{
    bool ret = Combine3DImage::loadBinToImage(dstImage,buffer,len);
    int imageSize;
    int width,height;

    if(ret==false){
        return false;
    }
    width = dstImage->width();
    height = dstImage->height();
    imageSize = width*height*3/2;
    if(imageSize>len){
        qDebug()<<tr("[%1,%2]image size doesn't equal to data len.").arg(__FUNCTION__).arg(__LINE__);
        return false;
    }

    R3D_YCbCrtoBGRX yuvToBgr;
    unsigned char * bgraBuffer;
    int bgraLen;

    bgraLen = width*height*4;
    bgraBuffer = (unsigned char *)malloc(bgraLen);
    if(bgraBuffer){
        yuvToBgr.convertI420toBGRX(bgraBuffer,buffer,width,height);
        ret = loadBGRXBinToImage(dstImage,bgraBuffer,width,height);
        free(bgraBuffer);
    }else{
        qDebug()<<tr("[%1,%2]Fail to malloc YCbCrToBGRX converter.").arg(__FUNCTION__).arg(__LINE__);
        return false;
    }

    return true;
}
bool Combine3DImageI420::convertLinearToTileBasedBuffer(unsigned char *dstbuffer,
                                                    unsigned char *srcbuffer,
                                                    int srclen,
                                                    int srcw, int srch)
{
    int uw=srcw/2;
    int uh=srch/2;
    if((srcw%256) || (srch%16)
       ||(uw%256) || (uh%16)){
        qDebug()<<tr("[%1,%2]unsupported source image stride.")
                  .arg(__FILE__).arg(__LINE__);
        return false;
    }
    /*convert Y section*/
    int w = srcw/256;
    int h = srch/16;
    int num = w*h;
    unsigned char * ybuffer = srcbuffer;
    unsigned char * dstYbuffer = dstbuffer;
    for(int i=0;i<num;i++){
        //init data;
        int x = i % w;
        int y = i / w;
        unsigned char * linebuffer = ybuffer + y*srcw*16+x*256;
        unsigned char * tlbbuffer = dstYbuffer + i*TILEBASEMEM_SIZE;
        for(int k=0;k<16;k++){
            memcpy(tlbbuffer+256*k,linebuffer+k*srcw,256);
        }
    }

    /*convert U and V section*/
    w = uw/256;
    h = uh/16;
    num = w*h;
    unsigned char * ubuffer = srcbuffer+srcw*srch;
    unsigned char * vbuffer = ubuffer + srcw*srch/4;
    unsigned char * dstUbuffer = dstbuffer+srcw*srch;
    unsigned char * dstVbuffer = dstUbuffer+srcw*srch/4;
    for(int i=0;i<num;i++){
        int x = i % w;
        int y = i / w;
        unsigned char * linebuffer_u = ubuffer + y*uw*16+x*256;
        unsigned char * tlbbuffer_u = dstUbuffer + i*TILEBASEMEM_SIZE;
        unsigned char * linebuffer_v = vbuffer + y*uw*16+x*256;
        unsigned char * tlbbuffer_v = dstVbuffer + i*TILEBASEMEM_SIZE;
        for(int k=0;k<16;k++){
            memcpy(tlbbuffer_u+256*k,linebuffer_u+k*uw,256);
            memcpy(tlbbuffer_v+256*k,linebuffer_v+k*uw,256);
        }
    }
    return true;
}
void Combine3DImageI420::convertTilebasedToLinearBuffer(unsigned char *dstbuffer,
                                                        unsigned char *srcbuffer,
                                                        int tlblen,
                                                        int srcw,int srch)
{
    if(dstbuffer==0 || srcbuffer==0)return;
    int uw = srcw/2;
    int uh = srch/2;

    /*convert Y to linear*/
    int w = srcw/256;
    int h = srch/16;
    int num = w*h;
    for(int i=0;i<num;i++){
        int x = i%w;
        int y = i/w;
        unsigned char* tlbbuffer_y  = srcbuffer + i*TILEBASEMEM_SIZE;
        unsigned char *linebuffer_y = dstbuffer + y*srcw*16+x*256;
        for(int k=0;k<16;k++){
            memcpy(linebuffer_y + k*srcw,tlbbuffer_y+k*256,256);
        }
    }

    /*convert UV to linear*/
    w = uw/256;
    h = uh/16;
    num = w*h;
    unsigned char * srcUbuffer = srcbuffer + srcw*srch;
    unsigned char * srcVbuffer = srcbuffer + srcw*srch + uw*uh;
    unsigned char * dstUbuffer = dstbuffer + srcw*srch;
    unsigned char * dstVbuffer = dstbuffer + srcw*srch + uw*uh;
    for(int i=0;i<num;i++){
        int x = i % w;
        int y = i / w;
        unsigned char * tlbbuffer_u  = srcUbuffer + i*TILEBASEMEM_SIZE;
        unsigned char * linebuffer_u = dstUbuffer+ (y*uw*16+x*256);
        unsigned char * tlbbuffer_v  = srcVbuffer + i*TILEBASEMEM_SIZE;
        unsigned char * linebuffer_v = dstVbuffer + y*uw*16+x*256;
        for(int k=0;k<16;k++){
            memcpy(linebuffer_u+k*uw,tlbbuffer_u+k*256,256);
            memcpy(linebuffer_v+k*uw,tlbbuffer_v+k*256,256);
        }
    }

}
