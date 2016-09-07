#include "combine3dimagebgra.h"
#include<QDebug>
Combine3DImageBGRA::Combine3DImageBGRA(QObject *parent) :
    Combine3DImage(parent)
{
    m_preAlpha = 1.0f;
    m_enAlpha  = false;
}
void Combine3DImageBGRA::setEnablePreAlpha(bool b)
{
    m_enAlpha = b;
}
void Combine3DImageBGRA::setPreAlpha(float alpha)
{
    if(m_preAlpha<=1.0f && m_preAlpha>=0.0f)
        m_preAlpha = alpha;
}
bool Combine3DImageBGRA::interleavingPixelByPixel(QImage *srcLeft, QImage *srcRight)
{
    int width = srcLeft->width();
    int height = srcLeft->height();
    CombineColorBGRA *c0,*c1;//the color of srcleft and srcright
    float alpha0 = m_preAlpha;
    float alpha1 = m_preAlpha;
    for(int i=0;i<height;i++)
    {
       for(int j=0;j<width;j++){
           int index = i*width+j;
           unsigned int c,d;
           c  = (unsigned int)(srcLeft->pixel(j,i));//ARGB
           c0 = (CombineColorBGRA *)(&c);
           d  = (unsigned int)(srcRight->pixel(j,i));
           c1 = (CombineColorBGRA *)(&d);

           //if the user input alpha is not used
           alpha0 = (m_enAlpha)?m_preAlpha:((float)(c0->a)/ 255);
           alpha1 = (m_enAlpha)?m_preAlpha:((float)(c1->a)/ 255);

           //add a if condition
           m_dstbuffer[8*index]   = (unsigned char)(c0->b * alpha0);//b
           m_dstbuffer[8*index+1] = (unsigned char)(c0->g * alpha0);//g
           m_dstbuffer[8*index+2] = (unsigned char)(c0->r * alpha0);//r
           m_dstbuffer[8*index+3] = (unsigned char)(c0->a * alpha0);//set to 0 in bgrx format
           m_dstbuffer[8*index+4] = (unsigned char)(c1->b * alpha1);//b
           m_dstbuffer[8*index+5] = (unsigned char)(c1->g * alpha1);//g
           m_dstbuffer[8*index+6] = (unsigned char)(c1->r * alpha1);//r
           m_dstbuffer[8*index+7] = (unsigned char)(c1->a * alpha1);//set to 0 in bgrx format
       }
    }
    m_dstlen = width*height*2*4;
    return true;
}
bool Combine3DImageBGRA::interleavingLine(QImage *srcLeft, QImage *srcRight)
{
    int width = srcLeft->width();
    int height = srcLeft->height();
    CombineColorBGRA *c0,*c1;//the color of srcleft and srcright
    float alpha0 = m_preAlpha;
    float alpha1 = m_preAlpha;

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
           m_dstbuffer[4*index]   = (unsigned char)(c0->b * alpha0);
           m_dstbuffer[4*index+1] = (unsigned char)(c0->g * alpha0);
           m_dstbuffer[4*index+2] = (unsigned char)(c0->r * alpha0);
           m_dstbuffer[4*index+3] = (unsigned char)(c0->a * alpha0);

           index = (2*i+1)*width+j;
           m_dstbuffer[4*index]   = (unsigned char)(c1->b * alpha1);
           m_dstbuffer[4*index+1] = (unsigned char)(c1->g * alpha1);
           m_dstbuffer[4*index+2] = (unsigned char)(c1->r * alpha1);
           m_dstbuffer[4*index+3] = (unsigned char)(c1->a * alpha1);

       }
    }
    m_dstlen = width*height*2*4;
    return true;
}

bool Combine3DImageBGRA::convertToRawData(QImage *srcImage)
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
           m_dstbuffer[4*index]   = (unsigned char)(c0->b * alpha);
           m_dstbuffer[4*index+1] = (unsigned char)(c0->g * alpha);
           m_dstbuffer[4*index+2] = (unsigned char)(c0->r * alpha);
           m_dstbuffer[4*index+3] = (unsigned char)(c0->a * alpha);
       }
    }

    return true;
}
bool Combine3DImageBGRA::loadBinToImage(QImage *dstImageRGB32, unsigned char *buffer, int len)
{
    bool ret = Combine3DImage::loadBinToImage(dstImageRGB32,buffer,len);
    int imageSize;
    int width,height;
    CombineColorBGRA dst;

    if(ret==false){
        return false;
    }
    width = dstImageRGB32->width();
    height = dstImageRGB32->height();
    imageSize = width*height*4;

    /*convert image to rgbx*/
    unsigned char * rgbx = (unsigned char *)malloc(imageSize);
    if(rgbx==NULL){
        qDebug()<<tr("[%1,%2]FAIL to allocate the rgbx buffer.")
                  .arg(__FILE__).arg(__LINE__);
        return false;
    }
    convertRGBLocaltoRGBX(rgbx,buffer,width,height);

    /*if(imageSize>len){
        qDebug()<<tr("[%1,%2]image size doesn't equal to data len.imagesize=%3,len=%4")
                  .arg(__FILE__).arg(__LINE__)
                  .arg(imageSize)
                  .arg(len);
        return false;
    }*/

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            unsigned int *pixel;
            int index  =  i*width +j;
            dst.r = rgbx[4*index];
            dst.g = rgbx[4*index+1];
            dst.b = rgbx[4*index+2];
            dst.a = rgbx[4*index+3];
            pixel = (unsigned int*)(&dst);
            dstImageRGB32->setPixel(j,i,*pixel);
        }
    }
    free(rgbx);
    return true;
}
void Combine3DImageBGRA::convertRGBXtoRGBLocal(unsigned char * bgra,
                                               unsigned char * rgbx,
                                               int w,int h)
{
    if(bgra==NULL || rgbx==NULL)return;
    int width=w,height=h;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            int index  =  i*width +j;
            bgra[4*index+2] = rgbx[4*index];   //r
            bgra[4*index+1] = rgbx[4*index+1]; //g
            bgra[4*index]   = rgbx[4*index+2]; //b
            bgra[4*index+3] = rgbx[4*index+3]; //a
        }
    }
}

void Combine3DImageBGRA::convertRGBLocaltoRGBX(unsigned char * rgbx,
                                 unsigned char * bgra,
                                 int w,int h)
{
    if(bgra==NULL || rgbx==NULL)return;
    int width=w,height=h;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            int index  =  i*width +j;
            rgbx[4*index+2] = bgra[4*index];   //b
            rgbx[4*index+1] = bgra[4*index+1]; //g
            rgbx[4*index]   = bgra[4*index+2]; //r
            rgbx[4*index+3] = bgra[4*index+3]; //a
        }
    }
}
