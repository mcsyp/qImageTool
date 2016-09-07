#ifndef COMBINE3DIMAGERGBX_H
#define COMBINE3DIMAGERGBX_H
#include "combine3dimage.h"

class Combine3DImageRGBX : public Combine3DImage
{
    Q_OBJECT
public:
    explicit Combine3DImageRGBX(QObject *parent = 0);

    virtual bool convertBinToImage(QImage * dstImage,unsigned char * buffer, int len);
    virtual float combineFMTBpp(){return 4.0f;}
    virtual bool loadBinToImage(QImage *dstImage, unsigned char *buffer, int len);
protected:
    virtual bool interleavingLine(QImage *srcLeft, QImage *srcRight);
    virtual bool interleavingPixelByPixel(QImage *srcLeft, QImage *srcRight);
    virtual bool convertToRawData(QImage *srcImage);
    virtual FMT_3D_COMBINE formatType(){return FMT_3D_RGBX;}
};
#endif // COMBINE3DIMAGERGBX_H
