#ifndef COMBINE3DIMAGERGB332_H
#define COMBINE3DIMAGERGB332_H
#include <QObject>
#include "combine3dimagergba.h"

class Combine3DImageRGB332 : public Combine3DImageRGBA
{
    Q_OBJECT
public:
    explicit Combine3DImageRGB332(QObject *parent = 0);
    ~Combine3DImageRGB332();

    virtual bool convertBinToImage(QImage * dstImage,unsigned char * buffer, int len);

    virtual float combineFMTBpp(){return 1.0f;}
protected:
    virtual bool interleavingLine(QImage *srcLeft, QImage *srcRight);
    virtual bool interleavingPixelByPixel(QImage *srcLeft, QImage *srcRight);
    virtual bool convertToRawData(QImage *srcImage);
    virtual FMT_3D_COMBINE formatType(){return FMT_3D_RGB332;}

    virtual bool convertLinearToTileBasedBuffer(unsigned char *dstbuffer,
                                                unsigned char *srcbuffer,
                                                int srclen,
                                                int srcw, int srch);
    virtual void convertTilebasedToLinearBuffer(unsigned char *dstbuffer,
                                                unsigned char *srcbuffer,
                                                int tlblen,
                                                int srcw,int srch);

    virtual void convertRGBXtoRGBLocal(unsigned char * rgb332,
                                     unsigned char * rgbx,
                                     int w,int h);

    virtual void convertRGBLocaltoRGBX(unsigned char * rgbx,
                                     unsigned char * rgb332,
                                     int w,int h);

    virtual void swapEndian(unsigned char * buffer,int len);//swap every 2 bytes.
protected:
    unsigned char * m_rgbtmp;
};

#endif // COMBINE3DIMAGERGB332_H
