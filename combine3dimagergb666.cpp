#include "combine3dimagergb666.h"
Combine3DImageRGB666::Combine3DImageRGB666(QObject* parent):Combine3DImageRGB332(parent)
{
}

void Combine3DImageRGB666::convertRGBLocaltoRGBX(unsigned char *rgbx,
                                                 unsigned char *rgb666,
                                                 int w, int h)
{
    int len = w*h*combineFMTBpp();
    swapEndian(rgb666,len);

    int src_index=0;
    int dst_index=0;
    int index;
    unsigned char * src;//rgb666
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
            src_index = 3*index;
            src = rgb666 + src_index;

            //convert
            dst[0] = src[0]<<2;
            dst[1] = src[1]<<2;
            dst[2] = src[2]<<2;
            dst[3] = 0;
        }
    }
}
void Combine3DImageRGB666::convertRGBXtoRGBLocal(unsigned char *rgb666,
                                                 unsigned char *rgbx,
                                                 int w, int h)
{
    int src_index=0;
    int dst_index=0;
    int index = 0;
    unsigned char * src;//to rgbx
    unsigned char * dst;//to rgb565
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++){
            index = i*w+j;

            src_index = 4*index;
            src = rgbx + src_index;

            dst_index = 3*index;
            dst = rgb666 + dst_index;

            //convert
            dst[0] = (src[0]>>2);
            dst[1] = (src[1]>>2);
            dst[2] = (src[2]>>2);
            //dst[0] = (src[0]&0x3f);
            //dst[1] = (src[1]&0x3f);
            //dst[2] = (src[2]&0x3f);
        }
    }

    int len = w*h*combineFMTBpp();
    swapEndian(rgb666,len);
}

