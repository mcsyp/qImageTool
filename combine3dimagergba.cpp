#include "combine3dimagergba.h"
#include<QDebug>

Combine3DImageRGBA::Combine3DImageRGBA(QObject* parent):Combine3DImageBGRA(parent)
{
}
bool Combine3DImageRGBA::interleavingPixelByPixel(QImage *srcLeft, QImage *srcRight)
{
    int width = srcLeft->width();
    int height = srcLeft->height();
    CombineColorBGRA *c0,*c1;//the color of srcleft and srcright
    float alpha0;
    float alpha1;

    for(int i=0;i<height;i++)
    {
       for(int j=0;j<width;j++){
           int index = i*width+j;
           unsigned int c,d;
           c  = (unsigned int)(srcLeft->pixel(j,i));
           c0 = (CombineColorBGRA *)(&c);
           d  = (unsigned int)(srcRight->pixel(j,i));
           c1 = (CombineColorBGRA *)(&d);

           //if the user input alpha is not used
           alpha0 = (m_enAlpha)?m_preAlpha:((float)(c0->a)/ 255);
           alpha1 = (m_enAlpha)?m_preAlpha:((float)(c1->a)/ 255);

           m_dstbuffer[8*index]   = (unsigned char)(c0->r * alpha0);//r
           m_dstbuffer[8*index+1] = (unsigned char)(c0->g * alpha0);//g
           m_dstbuffer[8*index+2] = (unsigned char)(c0->b * alpha0);//b
           m_dstbuffer[8*index+3] = (unsigned char)(c0->a * alpha0);//set to 0 in bgrx format
           m_dstbuffer[8*index+4] = (unsigned char)(c1->r * alpha1);//r
           m_dstbuffer[8*index+5] = (unsigned char)(c1->g * alpha1);//g
           m_dstbuffer[8*index+6] = (unsigned char)(c1->b * alpha1);//b
           m_dstbuffer[8*index+7] = (unsigned char)(c1->a * alpha1);//set to 0 in bgrx format
       }
    }
    m_dstlen = width*height*2*4;
    return true;
}
bool Combine3DImageRGBA::interleavingLine(QImage *srcLeft, QImage *srcRight)
{
    int width = srcLeft->width();
    int height = srcLeft->height();
    CombineColorBGRA *c0,*c1;//the color of srcleft and srcright
    float alpha0;
    float alpha1;

    for(int i=0;i<height;i++)
    {
       for(int j=0;j<width;j++){
           unsigned int c,d;
           c  = (unsigned int)(srcLeft->pixel(j,i));
           c0 = (CombineColorBGRA *)(&c);
           d  = (unsigned int)(srcRight->pixel(j,i));
           c1 = (CombineColorBGRA *)(&d);

           //if the user input alpha is not used
           alpha0 = (m_enAlpha)?m_preAlpha:((float)(c0->a)/ 255);
           alpha1 = (m_enAlpha)?m_preAlpha:((float)(c1->a)/ 255);

           int index = 2*i*width+j;
           m_dstbuffer[4*index]   = (unsigned char)(c0->r * alpha0);
           m_dstbuffer[4*index+1] = (unsigned char)(c0->g * alpha0);
           m_dstbuffer[4*index+2] = (unsigned char)(c0->b * alpha0);
           m_dstbuffer[4*index+3] = (unsigned char)(c0->a * alpha0);

           index = (2*i+1)*width+j;
           m_dstbuffer[4*index]   = (unsigned char)(c1->r * alpha1);
           m_dstbuffer[4*index+1] = (unsigned char)(c1->g * alpha1);
           m_dstbuffer[4*index+2] = (unsigned char)(c1->b * alpha1);
           m_dstbuffer[4*index+3] = (unsigned char)(c1->a * alpha1);

       }
    }
    m_dstlen = width*height*2*4;
    return true;
}
bool Combine3DImageRGBA::convertToRawData(QImage *srcImage)
{
    CombineColorBGRA* c0;
    int width = srcImage->width();
    int height = srcImage->height();
    float alpha;

    m_dstlen = width*height*4;
    for(int i=0;i<height;i++)
    {
       for(int j=0;j<width;j++){
           unsigned int c = (unsigned int)(srcImage->pixel(j,i));
           c0 = (CombineColorBGRA *)(&c);

           //if the user input alpha is not used
           alpha = (m_enAlpha)?m_preAlpha:((float)(c0->a)/ 255);

           int index = i*width+j;
           m_dstbuffer[4*index]   = (unsigned char)(c0->r * alpha);
           m_dstbuffer[4*index+1] = (unsigned char)(c0->g * alpha);
           m_dstbuffer[4*index+2] = (unsigned char)(c0->b * alpha);
           m_dstbuffer[4*index+3] = (unsigned char)(c0->a * alpha);
       }
    }

    return true;
}
bool Combine3DImageRGBA::convertBinToImage(QImage *dstImage, unsigned char *buffer, int len)
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
            dst.r = buffer[4*index];
            dst.g = buffer[4*index+1];
            dst.b = buffer[4*index+2];
            dst.a = buffer[4*index+3];
            pixel = (unsigned int*)(&dst);
            dstImage->setPixel(j,i,*pixel);
        }
    }
    return true;
}
