#ifndef COMBINE3DIMAGEYUV411_H
#define COMBINE3DIMAGEYUV411_H
#include "combine3dimagei420.h"
#include <QObject>
class Combine3DImageYUV411 : public Combine3DImageI420
{
    Q_OBJECT
public:
    Combine3DImageYUV411(QObject * p=0);
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
    virtual bool interleavingLine(QImage *srcLeft,QImage* srcRight);
    virtual bool interleavingPixelByPixel(QImage *srcLeft,QImage* srcRight);
    virtual bool convertToRawData(QImage *srcImage);
    virtual FMT_3D_COMBINE formatType(){return FMT_3D_YUV411;}
};

#endif // COMBINE3DIMAGEYUV411_H
