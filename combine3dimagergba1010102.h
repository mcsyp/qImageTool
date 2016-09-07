#ifndef COMBINE3DIMAGERGBA1010102_H
#define COMBINE3DIMAGERGBA1010102_H
#include "combine3dimagergb332.h"
#include <QObject>
class Combine3DImageRGBA1010102: public Combine3DImageRGB332
{
    Q_OBJECT
public:
    Combine3DImageRGBA1010102(QObject* parent=0);
    virtual float combineFMTBpp(){return 4.0f;}

protected:
    virtual FMT_3D_COMBINE formatType(){return FMT_3D_RGBA1010102;}
    virtual void convertRGBXtoRGBLocal(unsigned char * rgb32,
                                     unsigned char * rgbx,
                                     int w,int h);

    virtual void convertRGBLocaltoRGBX(unsigned char * rgbx,
                                     unsigned char * rgb32,
                                     int w,int h);
};


#endif // COMBINE3DIMAGERGBA1010102_H
