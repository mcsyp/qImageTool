#include "combine3dimagergbx1010102.h"

Combine3DImageRGBX1010102::Combine3DImageRGBX1010102(QObject* parent)
    :Combine3DImageRGB332(parent)
{
}

void Combine3DImageRGBX1010102::convertRGBLocaltoRGBX(unsigned char *rgbx, unsigned char *rgb32, int w, int h)
{
    int len = w*h*combineFMTBpp();
    //swapEndian(rgb32,len);

    int src_index=0;
    int dst_index=0;
    int index;
    unsigned char * src;//rgb1010102
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
            src_index = 4*index;
            src = rgb32 + src_index;

            //convert
            /*ori code
             *dst[0] = src[0];//r
             *dst[1] = ((src[1]&0x3f)<<2)| ((src[2]&0xc0)>>6);//g
             *dst[2] = ((src[2]&0xf)<<4)|((src[3]&0xf0)>>4);//b
             *dst[3] = 0;
             */
            unsigned short r=src[0]|((src[1]&0x3)<<8);
            unsigned short g=((src[1]&0xfc)>>2)|((src[2]&0xf)<<6);
            unsigned short b=((src[2]&0xf0)>>4) |((src[3]&0x3f)<<4);
            dst[0] = r>>2;//r
            dst[1] = g>>2;//g
            dst[2] = b>>2;//b
            dst[3] = 0;//x
        }
    }
}
void Combine3DImageRGBX1010102::convertRGBXtoRGBLocal(unsigned char *rgb32, unsigned char *rgbx, int w, int h)
{
    int src_index=0;
    int dst_index=0;
    int index = 0;
    unsigned char * src;//to rgbx
    unsigned char * dst;//to rgb32
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++){
            index = i*w+j;

            src_index = 4*index;
            src = rgbx + src_index;

            dst_index = 4*index;
            dst = rgb32 + dst_index;

            //convert
            /*ori code
             *dst[0] = src[0];//r
             *dst[1] = (src[1]&0xfc)>>2;//g_6
             *dst[2] = ((src[1]&0x3)<<6) | ((src[2]&0xf0)>>4);//g_2 b_4
             *dst[3] = (src[2]&0xf)<<4;//b_4
             */
            unsigned short r = src[0]<<2;
            unsigned short g = src[1]<<2;
            unsigned short b = src[2]<<2;
            dst[0]=r&0xff;
            dst[1]=((r&0x0300)>>8)| ((g&0x3f)<<2);
            dst[2]=((g&0x3c0)>>6)| ((b&0xf)<<4);
            dst[3]=(b>>4)&0xff;
        }
    }

    int len = w*h*combineFMTBpp();
    //swapEndian(rgb32,len);

}
