#ifndef COMBINE3DIMAGERGBA_H
#define COMBINE3DIMAGERGBA_H

#include <QObject>
#include "combine3dimagebgra.h"

class Combine3DImageRGBA : public Combine3DImageBGRA
{
    Q_OBJECT
public:
    explicit Combine3DImageRGBA(QObject *parent = 0);

    virtual bool convertBinToImage(QImage * dstImage,unsigned char * buffer, int len);
    virtual float combineFMTBpp(){return 4.0f;}
protected:
    virtual bool interleavingLine(QImage *srcLeft, QImage *srcRight);
    virtual bool interleavingPixelByPixel(QImage *srcLeft, QImage *srcRight);
    virtual bool convertToRawData(QImage *srcImage);
    virtual FMT_3D_COMBINE formatType(){return FMT_3D_RGBA;}

    virtual void convertRGBXtoRGBLocal(unsigned char * rgba,
                                       unsigned char * rgbx,
                                       int w,int h)
    {
        if(rgba==NULL || rgbx==NULL)return;
        int len = w*h*4;
        memcpy(rgba,rgbx,len);
    }

    virtual void convertRGBLocaltoRGBX(unsigned char * rgbx,
                                     unsigned char * rgba,
                                     int w,int h)
    {
        if(rgba==NULL || rgbx==NULL)return;
        int len = w*h*4;
        memcpy(rgbx,rgba,len);
    }
};

#endif // COMBINE3DIMAGERGBA_H
