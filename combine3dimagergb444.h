#ifndef COMBINE3DIMAGERGB444_H
#define COMBINE3DIMAGERGB444_H
#include <QObject>
#include "combine3dimagergb332.h"
class Combine3DImageRGB444 : public Combine3DImageRGB332
{
    Q_OBJECT
public:
    Combine3DImageRGB444(QObject *parent=0);

    virtual float combineFMTBpp(){return 2.0f;}
protected:
    virtual FMT_3D_COMBINE formatType(){return FMT_3D_RGB444;}
    virtual void convertRGBXtoRGBLocal(unsigned char * rgb444,
                                     unsigned char * rgbx,
                                     int w,int h);

    virtual void convertRGBLocaltoRGBX(unsigned char * rgbx,
                                     unsigned char * rgb444,
                                     int w,int h);
};

#endif // COMBINE3DIMAGERGB444_H
