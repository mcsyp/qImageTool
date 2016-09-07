#ifndef COMBINE3DIMAGEBGR565_H
#define COMBINE3DIMAGEBGR565_H
#include "combine3dimagergb565.h"
#include <QObject>
class Combine3DImageBGR565 : public Combine3DImageRGB565
{
    Q_OBJECT
public:
    Combine3DImageBGR565(QObject *p=0);
    virtual float combineFMTBpp(){return 2.0f;}

protected:
    virtual FMT_3D_COMBINE formatType(){return FMT_3D_BGR565;}
    virtual void convertRGBXtoRGBLocal(unsigned char * bgr565,
                                     unsigned char * rgbx,
                                     int w,int h);

    virtual void convertRGBLocaltoRGBX(unsigned char * rgbx,
                                     unsigned char * bgr565,
                                     int w,int h);
};

#endif // COMBINE3DIMAGEBGR565_H
