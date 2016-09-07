#ifndef COMBINE3DIMAGEYUV422_H
#define COMBINE3DIMAGEYUV422_H
#include "combine3dimagenv12.h"
#include "combine3dimagebgrx.h"
#include "r3d_colorconvert.h"

class Combine3DImageYUV422 : public Combine3DImageNV12
{
    Q_OBJECT
public:
    Combine3DImageYUV422(QObject* parent=0);

    void setIsPlanar(bool b);
    void setYUV422Format(enum R3D_FMT_YUV422 fmt = R3D_FMT_YUYV);
    virtual float combineFMTBpp(){return 1.0f;}
    virtual bool convertBinToImage(QImage *dstImage, unsigned char *buffer, int len);
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
protected:
    virtual bool interleavingLine(QImage *srcLeft, QImage *srcRight);
    virtual bool interleavingPixelByPixel(QImage *srcLeft, QImage *srcRight);
    virtual bool convertToRawData(QImage *srcImage);
    virtual FMT_3D_COMBINE formatType(){return FMT_3D_YUV422;}
protected:
    R3D_BGRXtoYCbCr m_bgrxToYuv;
    Combine3DImageBGRX m_combBgrx;

    bool m_isPlanar;
    enum R3D_FMT_YUV422 m_outputFmt;
};

#endif // COMBINE3DIMAGEYUV422_H
