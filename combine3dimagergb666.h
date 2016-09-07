#ifndef COMBINE3DIMAGERGB666_H
#define COMBINE3DIMAGERGB666_H
#include "combine3dimagergb332.h"

class Combine3DImageRGB666 : public Combine3DImageRGB332
{
public:
    Combine3DImageRGB666(QObject *parent=0);

    virtual float combineFMTBpp(){return 3.0f;}//3 bytes / pixel

protected:
    virtual FMT_3D_COMBINE formatType(){return FMT_3D_RGB666;}
    virtual void convertRGBXtoRGBLocal(unsigned char * rgb666,
                                       unsigned char * rgbx,
                                       int w,int h);

    virtual void convertRGBLocaltoRGBX(unsigned char * rgbx,
                                       unsigned char * rgb666,
                                       int w,int h);
};

#endif // COMBINE3DIMAGERGB666_H
