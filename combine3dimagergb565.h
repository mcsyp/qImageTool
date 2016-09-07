#ifndef COMBINE3DIMAGERGB565_H
#define COMBINE3DIMAGERGB565_H
#include "combine3dimagergb332.h"
#include <QObject>
class Combine3DImageRGB565 : public Combine3DImageRGB332
{
public:
    Combine3DImageRGB565(QObject* parent=0);

    virtual float combineFMTBpp(){return 2.0f;}

protected:
    virtual FMT_3D_COMBINE formatType(){return FMT_3D_RGB565;}
    virtual void convertRGBXtoRGBLocal(unsigned char * rgb565,
                                     unsigned char * rgbx,
                                     int w,int h);

    virtual void convertRGBLocaltoRGBX(unsigned char * rgbx,
                                     unsigned char * rgb565,
                                     int w,int h);
};

#endif // COMBINE3DIMAGERGB565_H
