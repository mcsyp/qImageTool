#ifndef COMBINE3DIMAGENV12_H
#define COMBINE3DIMAGENV12_H

#include <QObject>
#include "combine3dimage.h"
#include "combine3dimagebgrx.h"
#include "r3d_colorconvert.h"
class Combine3DImageNV12 : public Combine3DImage
{
    Q_OBJECT
public:
    explicit Combine3DImageNV12(QObject *parent = 0);

    virtual bool loadBinToImage(QImage * dstImage,unsigned char * buffer, int len);
    /*************************************************
     *purpose:convert linear mem into tilebased buffer. now only work for 32bit raw buffer.
     *input:  srcbuffer, the 32bit buffer. RGBA BGRA RGBX BGRX
     *        srclen, the length of the source buffer.
     *        srcw, the width of the src image buffer, eg.640x480 srcw=640.
     *        srch, the height of the src image buffer
     *output: dstbuffer, the tile based buffer.
     *return: true if successful.
     *************************************************/
    virtual bool convertLinearToTileBasedBuffer(unsigned char * dstbuffer,
                                                unsigned char * srcbuffer,
                                                int srclen,
                                                int srcw,int srch);
    /*************************************************
     *purpose:convert tilebased mem into linear buffer. now only work for 32bit raw buffer.
     *input:  tlbbuffer, the tile-based buffer.
     *        tlblen, the length of the tile-based buffer.
     *        srcw, the width of the src image buffer, eg.640x480 srcw=640.
     *        srch, the height of the src image buffer
     *output: dstbuffer, the linear 32bit buffer.RGBA BGRA RGBX BGRX
     *return: true if successful.
     *************************************************/
    virtual void convertTilebasedToLinearBuffer(unsigned char *dstbuffer,
                                                unsigned char *tlbbuffer,
                                                int tlblen,
                                                int srcw,int srch);

    virtual float combineFMTBpp(){return 1.0f;}
    virtual int tileBasedStride(int width);
    virtual int tileBasedHeight(int height);
protected:
    virtual bool loadBGRXBinToImage(QImage *dstImage, unsigned char *buffer,int width, int height);
    virtual bool interleavingLine(QImage *srcLeft, QImage *srcRight);
    virtual bool interleavingPixelByPixel(QImage *srcLeft, QImage *srcRight);
    virtual bool convertToRawData(QImage *srcImage);
    virtual FMT_3D_COMBINE formatType(){return FMT_3D_NV12;}
private:
    R3D_BGRXtoYCbCr m_rgbToYuv;
    Combine3DImageBGRX m_combBgrx;
};

#endif // COMBINE3DIMAGENV12_H
