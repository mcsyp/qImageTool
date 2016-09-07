#include "combine3dimagergb565.h"
#include <QDebug>
Combine3DImageRGB565::Combine3DImageRGB565(QObject* parent):Combine3DImageRGB332(parent)
{}
void Combine3DImageRGB565::convertRGBLocaltoRGBX(unsigned char *rgbx, unsigned char *rgb565, int w, int h)
{
    int len = w*h*combineFMTBpp();
    swapEndian(rgb565,len);

    int src_index=0;
    int dst_index=0;
    int index;
    unsigned char * src;//rgb565
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
            src = rgb565 + src_index;

            //convert
            /*ori code*/
            //dst[0] = ((src[0]&0xf8)>>3)*8;//r
            //dst[1] = (((src[0]&0x07)<<3)|((src[1]&0xe0)>>5))*4;//g
            //dst[2] = (src[1]&0x1f)*8;//b
            //dst[3] = 0;
            dst[0] = (src[1]&0x1f)*8;//r
            dst[1] = (((src[1]&0xe0)>>5)|((src[0]&0x7)<<3))*4;//g
            dst[2] = (src[0]&0xf8);//b
            dst[3] = 0;
        }
    }
}
void Combine3DImageRGB565::convertRGBXtoRGBLocal(unsigned char *rgb565, unsigned char *rgbx, int w, int h)
{
    int src_index=0;
    int dst_index=0;
    int index = 0;
    unsigned char * src;//to rgbx
    unsigned char * dst;//to rgb565
    unsigned char r0,g0,b0;
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++){
            index = i*w+j;

            src_index = 4*index;
            src = rgbx + src_index;

            dst_index = 2*index;
            dst = rgb565 + dst_index;

            //convert
            r0 = (src[0]/8)&0x1f;
            g0 = (src[1]/4)&0x3f;
            b0 = (src[2]/8)&0x1f;

            /*ori code*/
            //dst[0] = (r0<<3) | (g0>>3);
            //dst[1] = (g0<<5) | b0;
            dst[0] = (b0<<3) | (g0>>3);
            dst[1] = (g0<<5) | r0;
        }
    }

    int len = w*h*combineFMTBpp();
    swapEndian(rgb565,len);

}
