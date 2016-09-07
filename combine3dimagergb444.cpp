#include "combine3dimagergb444.h"
#include <QDebug>

Combine3DImageRGB444::Combine3DImageRGB444(QObject* parent):Combine3DImageRGB332(parent)
{
}

void Combine3DImageRGB444::convertRGBLocaltoRGBX(unsigned char * rgbx,
                                               unsigned char * rgb444,
                                               int w,int h)
{
    int len = w*h*combineFMTBpp();
    swapEndian(rgb444,len);

    int src_index=0;
    int dst_index=0;
    int index;
    unsigned char * src;//rgb444
    unsigned char * dst;//rgbx
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            index = w*i+j;

            //set dest index
            dst_index = 4*index;
            dst = rgbx + dst_index;

            //set src index
            src_index = 2*index;
            src = rgb444 + src_index;

            //convert
            dst[0] = (src[0]&0x0f)*16;//r
            dst[1] = ((src[1]&0xf0)>>4)*16;//g
            dst[2] = (src[1]&0x0f)*16;//b
            dst[3] = 0;
        }
    }
}
void Combine3DImageRGB444::convertRGBXtoRGBLocal(unsigned char *rgb444,
                                               unsigned char *rgbx,
                                               int w, int h)
{
    int src_index=0;
    int dst_index=0;
    int index = 0;
    unsigned char * src;//to rgbx
    unsigned char * dst;//to rgb444
    unsigned char r0,g0,b0;
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++){
            index = i*w+j;

            src_index = 4*index;
            src = rgbx + src_index;

            dst_index = 2*index;
            dst = rgb444 + dst_index;

            //convert
            r0 = (src[0]/16)&0x0f;
            g0 = (src[1]/16)&0x0f;
            b0 = (src[2]/16)&0x0f;

            dst[0] = r0;
            dst[1] = (g0<<4) | b0;
        }
    }

    int len = w*h*combineFMTBpp();
    swapEndian(rgb444,len);
}
