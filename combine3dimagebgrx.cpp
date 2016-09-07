#include "combine3dimagebgrx.h"
#include<QDebug>

Combine3DImageBGRX::Combine3DImageBGRX(QObject* parent):
    Combine3DImage(parent)
{
}
bool Combine3DImageBGRX::interleavingPixelByPixel(QImage *srcLeft, QImage *srcRight)
{
    int width = srcLeft->width();
    int height = srcLeft->height();
    CombineColorBGRA *c0,*c1;//the color of srcleft and srcright
    for(int i=0;i<height;i++)
    {
       for(int j=0;j<width;j++){
           int index = i*width+j;
           unsigned int c,d;
           c  = (unsigned int)(srcLeft->pixel(j,i));
           c0 = (CombineColorBGRA *)(&c);
           d  = (unsigned int)(srcRight->pixel(j,i));
           c1 = (CombineColorBGRA *)(&d);
           m_dstbuffer[8*index]   = c0->b;//b
           m_dstbuffer[8*index+1] = c0->g;//g
           m_dstbuffer[8*index+2] = c0->r;//r
           m_dstbuffer[8*index+3] = 0;//set to 0 in bgrx format
           m_dstbuffer[8*index+4] = c1->b;//b
           m_dstbuffer[8*index+5] = c1->g;//g
           m_dstbuffer[8*index+6] = c1->r;//r
           m_dstbuffer[8*index+7] = 0;//set to 0 in bgrx format
       }
    }
    m_dstlen = width*height*2*4;
    return true;
}
bool Combine3DImageBGRX::interleavingLine(QImage *srcLeft, QImage *srcRight)
{
    int width = srcLeft->width();
    int height = srcLeft->height();
    CombineColorBGRA *c0,*c1;//the color of srcleft and srcright
    for(int i=0;i<height;i++)
    {
       for(int j=0;j<width;j++){
           unsigned int c,d;
           c  = (unsigned int)(srcLeft->pixel(j,i));
           c0 = (CombineColorBGRA *)(&c);
           d  = (unsigned int)(srcRight->pixel(j,i));
           c1 = (CombineColorBGRA *)(&d);

           int index = 2*i*width+j;
           m_dstbuffer[4*index]   = c0->b;
           m_dstbuffer[4*index+1] = c0->g;
           m_dstbuffer[4*index+2] = c0->r;
           m_dstbuffer[4*index+3] = 0;

           index = (2*i+1)*width+j;
           m_dstbuffer[4*index]   = c1->b;
           m_dstbuffer[4*index+1] = c1->g;
           m_dstbuffer[4*index+2] = c1->r;
           m_dstbuffer[4*index+3] = 0;

       }
    }
    m_dstlen = width*height*2*4;
    return true;
}
bool Combine3DImageBGRX::convertToRawData(QImage *srcImage)
{
    CombineColorBGRA* c0;
    int width = srcImage->width();
    int height = srcImage->height();

    m_dstlen = width*height*4;
    for(int i=0;i<height;i++)
    {
       for(int j=0;j<width;j++){
           unsigned int c = (unsigned int)(srcImage->pixel(j,i));
           c0 = (CombineColorBGRA *)(&c);

           int index = i*width+j;
           m_dstbuffer[4*index]   = c0->b;
           m_dstbuffer[4*index+1] = c0->g;
           m_dstbuffer[4*index+2] = c0->r;
           m_dstbuffer[4*index+3] = 0;
       }
    }

    return true;
}
bool Combine3DImageBGRX::loadBinToImage(QImage *dstImage, unsigned char *buffer, int len)
{
    bool ret = Combine3DImage::loadBinToImage(dstImage,buffer,len);
    int imageSize;
    int width,height;
    CombineColorBGRA dst;

    if(ret==false){
        return false;
    }
    width = dstImage->width();
    height = dstImage->height();
    imageSize = width*height*4;
    if(imageSize>len){
        qDebug()<<tr("[%1,%2]image size doesn't equal to data len.").arg(__FUNCTION__).arg(__LINE__);
        return false;
    }

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
