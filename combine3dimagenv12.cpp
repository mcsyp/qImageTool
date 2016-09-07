#include "combine3dimagenv12.h"
#include <QDebug>
Combine3DImageNV12::Combine3DImageNV12(QObject* parent):
    Combine3DImage(parent)
{}
bool Combine3DImageNV12::loadBGRXBinToImage(QImage *dstImage, unsigned char *buffer,int width, int height)
{
    CombineColorBGRA dst;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            unsigned int *pixel;
            int index  =  i*width +j;
            dst.b = buffer[4*index];
            dst.g = buffer[4*index+1];
            dst.r = buffer[4*index+2];
            dst.a = buffer[4*index+3];
            pixel = (unsigned int*)(&dst);
            dstImage->setPixel(j,i,*pixel);
        }
    }
    return true;
}
bool Combine3DImageNV12::interleavingLine(QImage *srcLeft, QImage *srcRight)
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
    m_rgbToYuv.convertBGRXtoNV12(m_dstbuffer,bgrx,m_width,m_height);

    return true;
}

bool Combine3DImageNV12::interleavingPixelByPixel(QImage *srcLeft, QImage *srcRight)
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
    m_rgbToYuv.convertBGRXtoNV12(m_dstbuffer,bgrx,m_width,m_height);

    return true;
}

bool Combine3DImageNV12::convertToRawData(QImage *srcImage)
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
    m_rgbToYuv.convertBGRXtoNV12(m_dstbuffer,bgrx,width,height);

    return true;
}

bool Combine3DImageNV12::loadBinToImage(QImage *dstImage, unsigned char *buffer, int len)
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
        yuvToBgr.convertNV12toBGRX(bgraBuffer,buffer,width,height);
        ret = loadBGRXBinToImage(dstImage,bgraBuffer,width,height);
        free(bgraBuffer);
    }else{
        qDebug()<<tr("[%1,%2]Fail to malloc YCbCrToBGRX convert buffer.").arg(__FUNCTION__).arg(__LINE__);
        return false;
    }

    return true;
}

bool Combine3DImageNV12::convertLinearToTileBasedBuffer(unsigned char *dstbuffer,
                                                        unsigned char *srcbuffer,
                                                        int srclen,
                                                        int srcw, int srch)
{

    if((srcw%256) || (srch%16)){
        qDebug()<<tr("[%1,%2]unsupported source image stride.srcw=%3,srch=%4.")
                  .arg(__FILE__).arg(__LINE__)
                  .arg(srcw).arg(srch);
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
    int uw=srcw;
    int uh=srch/2;
    int dstuw = tileBasedStride(uw);
    int dstuh = tileBasedHeight(uh);
    //qDebug()<<tr("[%1,%2]dst_uw=%3,dst_uh=%4.\n")
    //          .arg(__FILE__).arg(__LINE__)
    //          .arg(dstuw).arg(dstuh);
    /*malloc the temp buffer to convert the uv into a tlb valid buffer region.*/
    unsigned char * tempbuffer = (unsigned char*)malloc(dstuw*dstuh);
    if(tempbuffer==0){
        qDebug()<<tr("[%1,%2]dst_uw=%3,dst_uh=%4. Fail to malloc tempbuffer for tile based conversion.\n")
                  .arg(__FILE__).arg(__LINE__)
                  .arg(dstuw).arg(dstuh);
        return false;
    }
    memset(tempbuffer,0,dstuw*dstuh);
    /*copy the uv buffer into a tlb valid buffer region*/
    unsigned char * srcUVbuffer = srcbuffer+srcw*srch;
    for(int i=0;i<uh;i++){
        memcpy(tempbuffer+i*dstuw,srcUVbuffer+i*uw,uw);
    }

    w = dstuw/256;//uw*2/256
    h = dstuh/16;
    num = w*h;
    srcUVbuffer = tempbuffer;
    unsigned char * dstUVbuffer = dstbuffer+srcw*srch;
    for(int i=0;i<num;i++){
        int x = i % w;
        int y = i / w;
        unsigned char * linebuffer_uv = srcUVbuffer + y*dstuw*16+x*256;
        unsigned char * tlbbuffer_uv  = dstUVbuffer + i*TILEBASEMEM_SIZE;
        for(int k=0;k<16;k++){
            memcpy(tlbbuffer_uv+256*k,linebuffer_uv+k*dstuw,256);
        }
    }

    m_dstlen = srcw*srch+dstuw*dstuh;
    free(tempbuffer);

    return true;
}
void Combine3DImageNV12::convertTilebasedToLinearBuffer(unsigned char *dstbuffer,
                                                        unsigned char *srcbuffer,
                                                        int tlblen,
                                                        int srcw,int srch)
{
    if(dstbuffer==0 || srcbuffer==0)return;
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

    int uw = srcw;
    int uh = srch/2;
    int dstuw = tileBasedStride(uw);
    int dstuh = tileBasedHeight(uh);

    /*convert U and V section*/
    w = dstuw/256;
    h = dstuh/16;
    num = w*h;
    unsigned char * srcUVbuffer = srcbuffer+srcw*srch;
    unsigned char * dstUVbuffer = dstbuffer+srcw*srch;
    for(int i=0;i<num;i++){
        int x = i % w;
        int y = i / w;
        unsigned char * tlbbuffer_uv  = srcUVbuffer + i*TILEBASEMEM_SIZE;
        unsigned char * linebuffer_uv = dstUVbuffer + y*dstuw*16+x*256;
        for(int k=0;k<16;k++){
            memcpy(linebuffer_uv+k*dstuw,tlbbuffer_uv+256*k,256);
        }
    }
}
#if 0
int Combine3DImageNV12::tileBasedStride(int width)
{
    /*width here is for Y only*/
    int uw=width/2;
    int a=uw;
    if(a%256!=0){
        a = ((int)(uw/256)+1)*256;
    }
    return (a*2);
}
int Combine3DImageNV12::tileBasedHeight(int height)
{
    int uh = height/2;
    int h = uh;
    if(h%16!=0){
        h = ((int)(uh/16)+1)*16;
    }
    return (2*h);
}
#else
int Combine3DImageNV12::tileBasedStride(int width)
{
    /*width here is for Y only*/
    int a=width;
    if(a%256!=0){
        a = ((int)(width/256)+1)*256;
    }
    return a;
}
int Combine3DImageNV12::tileBasedHeight(int height)
{
    int h = height;
    if(h%16!=0){
        h = ((int)(height/16)+1)*16;
    }
    return h;
}
#endif
