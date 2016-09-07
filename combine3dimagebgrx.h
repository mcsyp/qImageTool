#ifndef COMBINE3DIMAGEBGRX_H
#define COMBINE3DIMAGEBGRX_H
#include "combine3dimage.h"
class Combine3DImageBGRX : public Combine3DImage
{
    Q_OBJECT
public:
    Combine3DImageBGRX(QObject* parent=0);

    virtual bool loadBinToImage(QImage * dstImage,unsigned char * buffer, int len);
    virtual float combineFMTBpp(){return 4.0f;}
protected:
    virtual bool interleavingLine(QImage *srcLeft, QImage *srcRight);
    virtual bool interleavingPixelByPixel(QImage *srcLeft, QImage *srcRight);
    virtual bool convertToRawData(QImage *srcImage);
    virtual FMT_3D_COMBINE formatType(){return FMT_3D_BGRX;}
};

#endif // COMBINE3DIMAGEBGRX_H
