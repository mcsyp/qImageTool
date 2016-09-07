#include "combine3dimageyuv422.h"
#include <QDebug>

Combine3DImageYUV422::Combine3DImageYUV422(QObject *parent):Combine3DImageNV12(parent)
{
    m_isPlanar = false;
    m_outputFmt = R3D_FMT_YUYV;
}

void Combine3DImageYUV422::setIsPlanar(bool b)
{
    m_isPlanar = b;
}
void Combine3DImageYUV422::setYUV422Format(R3D_FMT_YUV422 fmt)
{
   m_outputFmt = fmt;
}
bool Combine3DImageYUV422::interleavingLine(QImage *srcLeft, QImage *srcRight)
{
    bool ret;
    unsigned char * bgrx;
    int len;
    m_dstlen = m_width*m_height*2;

    //step 1 convert to bgrx
    ret = m_combBgrx.generate3DImageBin(srcLeft,srcRight,INTERLEAVE_LINE);
    if(!ret){
        qDebug()<<tr("[%1,%2]Fail to convert the image into bgrx format.").arg(__FUNCTION__).arg(__LINE__);
        return false;
    }
    //step 2 convert to nv12;
    bgrx = m_combBgrx.data();
    len = m_combBgrx.datasize();
    if(m_isPlanar){
        m_bgrxToYuv.convertBGRXtoYUV422Planar(m_dstbuffer,bgrx,m_width,m_height);
    }else{
        m_bgrxToYuv.convertBGRXtoYUV422Packed(m_dstbuffer,bgrx,m_width,m_height,m_outputFmt);
    }
    return true;
}

bool Combine3DImageYUV422::interleavingPixelByPixel(QImage *srcLeft, QImage *srcRight)
{
    bool ret;
    unsigned char * bgrx;
    int len;
    m_dstlen = m_width*m_height*2;


    //step 1 convert to bgrx
    ret = m_combBgrx.generate3DImageBin(srcLeft,srcRight,INTERLEAVE_PIXEL_BY_PIXEL);
    if(!ret){
        qDebug()<<tr("[%1,%2]Fail to convert the image into bgrx format.").arg(__FUNCTION__).arg(__LINE__);
        return false;
    }

    //step 2 convert to nv12;
    bgrx = m_combBgrx.data();
    len = m_combBgrx.datasize();
    if(m_isPlanar){
        m_bgrxToYuv.convertBGRXtoYUV422Planar(m_dstbuffer,bgrx,m_width,m_height);
    }else{
        m_bgrxToYuv.convertBGRXtoYUV422Packed(m_dstbuffer,bgrx,m_width,m_height,m_outputFmt);
    }
    return true;
}
bool Combine3DImageYUV422::convertBinToImage(QImage *dstImage, unsigned char *buffer, int len)
{
    bool ret = Combine3DImage::loadBinToImage(dstImage,buffer,len);
    int imageSize;
    int width,height;

    if(ret==false){
        return false;
    }
    width = dstImage->width();
    height = dstImage->height();
    imageSize = width*height*2;
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
        if(m_isPlanar){
            yuvToBgr.convertYUV422PlanarToBGRX(bgraBuffer,buffer,width,height);
        }else{
            //add convert to 422 packed operation.
            yuvToBgr.convertYUV422PackedToBGRX(bgraBuffer,buffer,width,height,m_outputFmt);
        }
        ret = loadBGRXBinToImage(dstImage,bgraBuffer,width,height);
        free(bgraBuffer);
    }else{
        qDebug()<<tr("[%1,%2]Fail to malloc YCbCrToBGRX convert buffer.").arg(__FUNCTION__).arg(__LINE__);
        return false;
    }

    return true;
}
bool Combine3DImageYUV422::convertToRawData(QImage *srcImage)
{
    bool ret;
    unsigned char * bgrx;
    int len;
    int width = srcImage->width();
    int height = srcImage->height();
    m_dstlen = width * height * 2;

    //step 1 convert to bgrx
    ret = m_combBgrx.generate2DImageBin(srcImage);
    if(!ret){
        qDebug()<<tr("[%1,%2]Fail to convert the image into bgrx format.").arg(__FUNCTION__).arg(__LINE__);
        return false;
    }

    //step 2 convert to yuv422;
    bgrx = m_combBgrx.data();
    len = m_combBgrx.datasize();
    if(m_isPlanar){
        m_bgrxToYuv.convertBGRXtoYUV422Planar(m_dstbuffer,bgrx,width,height);
    }else{
        m_bgrxToYuv.convertBGRXtoYUV422Packed(m_dstbuffer,bgrx,width,height,m_outputFmt);
    }
    return true;
}
bool Combine3DImageYUV422::convertLinearToTileBasedBuffer(unsigned char *dstbuffer,
                                                        unsigned char *srcbuffer,
                                                        int srclen,
                                                        int srcw, int srch)
{
    if(m_isPlanar)
    {
        int uw=srcw/2;
        int uh=srch;
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
        unsigned char * srcUbuffer = srcbuffer+srcw*srch;
        unsigned char * srcVbuffer = srcUbuffer+uw*uh;
        unsigned char * dstUbuffer = dstbuffer+srcw*srch;
        unsigned char * dstVbuffer = dstUbuffer+uw*uh;
        for(int i=0;i<num;i++){
            int x = i % w;
            int y = i / w;
            unsigned char * linebuffer_u = srcUbuffer + y*uw*16+x*256;
            unsigned char * tlbbuffer_u  = dstUbuffer + i*TILEBASEMEM_SIZE;
            unsigned char * linebuffer_v = srcVbuffer + y*uw*16+x*256;
            unsigned char * tlbbuffer_v  = dstVbuffer + i*TILEBASEMEM_SIZE;
            for(int k=0;k<16;k++){
                memcpy(tlbbuffer_u+256*k,linebuffer_u+k*uw,256);
                memcpy(tlbbuffer_v+256*k,linebuffer_v+k*uw,256);
            }
        }
    }else{
        if((srcw%128) || (srch%16)){
            qDebug()<<tr("[%1,%2]unsupported source image stride.")
                      .arg(__FILE__).arg(__LINE__);
            return false;
        }
        int w = srcw/128;//srcw*2/256
        int h = srch/16;
        int num = w*h;
        for(int i=0;i<num;i++){
            //init data;
            int x = i % w;
            int y = i / w;
            unsigned char * linebuffer = srcbuffer + y*srcw*16*2+x*256;
            unsigned char * tlbbuffer  = dstbuffer + i*TILEBASEMEM_SIZE;
            for(int k=0;k<16;k++){
                memcpy(tlbbuffer+256*k,linebuffer+k*srcw*2,256);
            }
        }
    }

    return true;
}
void Combine3DImageYUV422::convertTilebasedToLinearBuffer(unsigned char *dstbuffer,
                                                        unsigned char *srcbuffer,
                                                        int tlblen,
                                                        int srcw,int srch)
{
    if(dstbuffer==0 || srcbuffer==0)return;
    if(m_isPlanar)
    {
        int uw = srcw/2;
        int uh = srch;

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

    #if 1
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
    #endif
    }else{
        if((srcw%128) || (srch%16)){
            qDebug()<<tr("[%1,%2]unsupported source image stride.")
                      .arg(__FILE__).arg(__LINE__);
            return;
        }
        int w = srcw/128;//srcw*4/256
        int h = srch/16;
        int num = w*h;
        for(int i=0;i<num;i++){
            //init data;
            int x = i % w;
            int y = i / w;
            unsigned char * tlbbuffer  = srcbuffer + i*TILEBASEMEM_SIZE;
            unsigned char * linebuffer = dstbuffer + y*srcw*16*2+x*256;
            for(int k=0;k<16;k++){
                memcpy(linebuffer+k*srcw*2,tlbbuffer+256*k,256);
            }
        }
    }

}
