#ifndef COMBINE3DIMAGEBGRA_H
#define COMBINE3DIMAGEBGRA_H

#include <QObject>
#include "combine3dimage.h"

class Combine3DImageBGRA : public Combine3DImage
{
    Q_OBJECT
public:
    explicit Combine3DImageBGRA(QObject *parent = 0);

    /**************************************************************
     *purpose:set if enable the user set pre alpha value.
     *input  :true,  use the m_preAlpha value to pre-multi each color channel
     *        false, use the image's alpha channel to pre-multi, ignore the m_preAlpha
     **************************************************************/
    void setEnablePreAlpha(bool b);
    bool enableAlpha(){return m_enAlpha;}
    /**************************************************************
     *purpose:set the pre-alpha value to multi with each color pixel channels
     *input  :0.0f~1.0f of the alpha value.
     **************************************************************/
    void setPreAlpha(float preAlpha);
    float preAlpha(){return m_preAlpha;}

    virtual bool loadBinToImage(QImage * dstImage,unsigned char * buffer, int len);

    virtual float combineFMTBpp(){return 4.0f;}

protected:
    virtual bool interleavingLine(QImage *srcLeft, QImage *srcRight);
    virtual bool interleavingPixelByPixel(QImage *srcLeft, QImage *srcRight);
    virtual bool convertToRawData(QImage *srcImage);
    virtual FMT_3D_COMBINE formatType(){return FMT_3D_BGRA;}


    virtual void convertRGBXtoRGBLocal(unsigned char * bgra,
                                     unsigned char * rgbx,
                                     int w,int h);

    virtual void convertRGBLocaltoRGBX(unsigned char * rgbx,
                                     unsigned char * bgra,
                                     int w,int h);
protected:
    float m_preAlpha;
    bool  m_enAlpha;
};

#endif // COMBINE3DIMAGEBGRA_H
