#include "combine3dimage.h"
#include <QDebug>
#include <QRgb>
#include <QPainter>
#include <QString>

Combine3DImage::Combine3DImage(QObject *parent) :
    QObject(parent)
{
    m_dstbuffer=0;
    m_dstlen=0;
    m_width=0;
    m_height=0;
}
Combine3DImage::~Combine3DImage()
{
    if(m_dstbuffer)free(m_dstbuffer);
}
bool Combine3DImage::resetDstBuffer(int len)
{
    bool ret = true;
    //calculate the size
    m_dstlen = len;
    //free output buffer
    if(m_dstbuffer)free(m_dstbuffer);

    //malloc buffer
    m_dstbuffer = (unsigned char *)malloc(m_dstlen);
    if(!m_dstbuffer){
        ret = false;
    }else{
        memset(m_dstbuffer,0,m_dstlen);
    }
    return ret;
}
bool Combine3DImage::generate3DImageBin(QImage *src0,QImage *src1,int mode,int stride,int dstHeight)
{
    if(src0==0 || src1==0)return false;
    if(src0->width()!=src1->width() ||
       src0->height()!=src1->height())
    {
        qDebug()<<tr("[%1,%2]src size mismatch.").arg(__FILE__).arg(__LINE__);
        return false;
    }

    //do stride work
    QImage* strideImage0=0;
    QImage* strideImage1=0;
    if(stride){
        int strideTmp=0;
        switch(mode){
        case INTERLEAVE_LINE:
            strideTmp = stride;
            break;
        case INTERLEAVE_PIXEL_BY_PIXEL:
            strideTmp = stride / 2;
            break;
        }

        strideImage0 = convertToStrideImage(src0,strideTmp,dstHeight);
        strideImage1 = convertToStrideImage(src1,strideTmp,dstHeight);
        if(strideImage0 || strideImage1){
            //if strideImage generated successfully.
            src0 = strideImage0;//replace the original right image.
            src1 = strideImage1;//replace the original left image.
        }
    }

    //init
    int width = src0->width();
    int height= src0->height();
    int bufferLen = width*height*4*2;//no metter what format is, we malloc the max size;
    bool ret = false;

    //reset the buffer size
    if(!resetDstBuffer((bufferLen))){
        qDebug()<<tr("[%1,%2]Fail to malloc dst buffer.").arg(__FILE__).arg(__LINE__);
        goto FAIL;
    }

    //start processing
    switch(mode){
    case INTERLEAVE_LINE:
        //init the width and height
        m_width = width;
        m_height = height*2;
        ret = interleavingLine(src0,src1);
        break;
    case INTERLEAVE_PIXEL_BY_PIXEL:
        m_width = width*2;
        m_height = height;
        ret = interleavingPixelByPixel(src0,src1);
        break;
    }

    //release buffers
    if(strideImage0)delete strideImage0;
    if(strideImage1)delete strideImage1;
    return ret;

FAIL:
    if(m_dstbuffer){
        free(m_dstbuffer);
        m_dstbuffer = 0;
        m_dstlen = 0;
    }

    //release buffers
    if(strideImage0)delete strideImage0;
    if(strideImage1)delete strideImage1;
    return false;
}

bool Combine3DImage::generate2DImageBin(QImage *srcImage,int stride,int dstHeight)
{
    bool ret = false;
    QImage * strideImage=0;
    if(srcImage==0){
        qDebug()<<tr("[%1,%2]Invalid input source image.").arg(__FILE__).arg(__LINE__);
        return false;
    }

    //process stride image
    if(stride){
        strideImage = convertToStrideImage(srcImage,stride,dstHeight);
        if(strideImage){
            //if strideImage generated successfully.
            srcImage = strideImage;//replace the original image.
        }
    }

    //convert image into bin
    m_width  = srcImage->width();
    m_height = srcImage->height();
    int bufferLen = m_width * m_height * 4;//the maximum image size;

    //reset the buffer size
    if(!resetDstBuffer((bufferLen))){
        qDebug()<<tr("[%1,%2]Fail to malloc dst buffer.").arg(__FILE__).arg(__LINE__);
        goto FAIL;
    }

    ret = convertToRawData(srcImage);//generate the binary file.

    //release the resource
    if(strideImage)delete strideImage;
    return ret;
FAIL:
    //release the buffer.
    if(m_dstbuffer){
        free(m_dstbuffer);
        m_dstbuffer = 0;
        m_dstlen = 0;
    }

    //release the resource
    if(strideImage)delete strideImage;

    return false;
}
bool Combine3DImage::convertLinearToTileBasedBuffer(unsigned char *dstbuffer,
                                                    unsigned char *srcbuffer,
                                                    int srclen,
                                                    int srcw, int srch)
{
    int type = formatType();
    if(type != FMT_3D_BGRX &&
       type != FMT_3D_BGRA &&
       type != FMT_3D_RGBX &&
       type != FMT_3D_RGBA)
    {
        qDebug()<<tr("[%1,%2]unsupported linear color format.")
                  .arg(__FILE__).arg(__LINE__);
        return false;
    }
    if((srcw%64) || (srch%16))
    {
        qDebug()<<tr("[%1,%2]unsupported source image size.srcw=%3,srch=%4.")
                  .arg(__FILE__).arg(__LINE__)
                  .arg(srcw).arg(srch);
        return false;
    }
    int w = srcw/64;//width*4/256
    int h = srch/16;//height/16
    int num = w*h;
    for(int i=0;i<num;i++){
        //init data;
        int x = i % w;
        int y = i / w;
        unsigned char * linebuffer = srcbuffer + (y*srcw+x*4)*64;
        unsigned char * tlbbuffer = dstbuffer + i*TILEBASEMEM_SIZE;
        for(int k=0;k<16;k++){
            memcpy(tlbbuffer+256*k,linebuffer+k*srcw*4,256);
        }
    }
    return true;
}
void Combine3DImage::convertTilebasedToLinearBuffer(unsigned char *dstbuffer,
                                                    unsigned char *tlbbuffer,
                                                    int tlblen,
                                                    int srcw,
                                                    int srch)
{
    if(dstbuffer==0 || tlbbuffer==0)return;
    int w = srcw/64;//srcw*4/256
    int h = srch/16;
    int num = w*h;
    unsigned char *src;
    unsigned char *dst;
    qDebug()<<tr("[%1,%2]num is %3").arg(__FILE__).arg(__LINE__).arg(num);
#if 1
    for(int i=0;i<num;i++){
        int x = i%w;
        int y = i/w;
        src = tlbbuffer + i*TILEBASEMEM_SIZE;
        dst = dstbuffer + (y*srcw+x*4)*64;
        for(int k=0;k<16;k++){
            memcpy(dst + k*srcw*4,src+k*256,256);
        }
    }
#endif
}

QImage * Combine3DImage::convertToStrideImage(QImage *srcImage, int stride,int dstHeight)
{
    if(srcImage==0  || stride==0 || dstHeight==0)return false;
    int w = srcImage->width();
    int h = srcImage->height();
    int dstWidth;
    int srcStride;
    QPainter *dstPainter=0;
    QImage * dstImage=0;
    float bpp = this->combineFMTBpp();

    //get the stride value
    srcStride = w*bpp;
    dstWidth = stride/bpp;
    //qDebug()<<tr("[%1,%2] height are: src_h=%3, dst_h=%4.")
    //          .arg(__FILE__).arg(__LINE__)
    //          .arg(h).arg(dstHeight);
    if(dstHeight>h)
    {/*if the height is 0, then it will not be used.*/
        qDebug()<<tr("[%1,%2] recommand height is used.src_h=%3, dst_h=%4.")
                  .arg(__FILE__).arg(__LINE__)
                  .arg(h).arg(dstHeight);
        h = dstHeight;
    }

    if(srcStride > stride){
        qDebug()<<tr("[%1,%2] input stride parameter error.srcStride=%3,stride=%4")
                  .arg(__FILE__).arg(__LINE__)
                  .arg(srcStride).arg(stride);
        goto FAIL;
    }
    dstImage = new QImage(dstWidth,h,QImage::Format_ARGB32);
    dstPainter = new QPainter(dstImage);
    dstPainter->fillRect(0,0,dstWidth,h,Qt::black);
    dstPainter->drawImage(0,0,*srcImage);

    if(dstPainter)delete dstPainter;
    return dstImage;
FAIL:
    if(dstImage)delete dstImage;
    return 0;
}
int Combine3DImage::tileBasedStride(int width)
{
    int stride = (int)(width*combineFMTBpp());
    int a = stride;
    if(stride%256!=0){
        a = ((int)(stride/256)+1)*256;
    }
    return a;
}
int Combine3DImage::tileBasedHeight(int height)
{
    int h = height;
    if(h%16!=0){
         h = ((int)(height/16)+1)*16;
    }
    return h;
}
bool Combine3DImage::loadBinToImage(QImage *dstImage, unsigned char *buffer, int len)
{
    if(dstImage==0 || buffer==0 || len<=0){
        qDebug()<<tr("[%1,%2]None pointer or invalid data pointer input.").arg(__FILE__).arg(__LINE__);
        return false;
    }
    return true;
}
