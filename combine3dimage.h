#ifndef CONVERT3DIMAGE_H
#define CONVERT3DIMAGE_H

#include <QObject>
#include <QImage>


typedef struct CombineColorBGRA_s{
    unsigned char b;
    unsigned char g;
    unsigned char r;
    unsigned char a;
}CombineColorBGRA;

class Combine3DImage : public QObject
{
    Q_OBJECT
public:
    explicit Combine3DImage(QObject *parent = 0);
    ~Combine3DImage();

    /*generate 3D image with input left and right image*/
    virtual bool generate3DImageBin(QImage *srcLeft,QImage* srcRight,int mode = INTERLEAVE_LINE,int stride=0,int dstHeight=0);
    /*generate 2D image binary file*/
    virtual bool generate2DImageBin(QImage * srcImage,int stride=0,int dstHeight=0);

    virtual float combineFMTBpp()=0;
    /*width is the width of the image. 640x480, the width is 640
      this function return the nearest 256x width image stride*/
    virtual int tileBasedStride(int width);
    /*this function rerutns the nearest 16x pixel image height*/
    virtual int tileBasedHeight(int height);

    #define TILEBASEMEM_SIZE 4096
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
    void setEnableLinear(bool b){m_isLinear = b;}
    bool isLinear(){return m_isLinear;}

    /*load a binary raw buffer into a image*/
    virtual bool loadBinToImage(QImage * dstImage,unsigned char * buffer, int len);

    //get output buffer and size;
    virtual int  datasize(){return m_dstlen;}
    virtual unsigned char * data(){return m_dstbuffer;}

    //get output width and height
    virtual int width(){return m_width;}
    virtual int height(){return m_height;}
public:
    enum INTERLEAVE_MODE
    {
        INTERLEAVE_LINE=0,
        INTERLEAVE_PIXEL_BY_PIXEL
    };

    /*combine color foramt defination*/
    /*to add a color format, add the enum value here and the name here.*/
    enum FMT_3D_COMBINE
    {
        FMT_3D_NONE=-1,
        FMT_3D_BGRX=0,
        FMT_3D_BGRA=1,
        FMT_3D_BGR565,

        FMT_3D_RGBX,
        FMT_3D_RGBA,
        FMT_3D_RGB332,
        FMT_3D_RGB444,
        FMT_3D_RGB565,
        FMT_3D_RGB666,
        FMT_3D_RGBA1010102,
        FMT_3D_RGBX1010102,

        FMT_3D_NV12,
        FMT_3D_I420,
        FMT_3D_YUV411,
        FMT_3D_YUV422,
        FMT_3D_YUV,
        FMT_3D_NUM
    };
    virtual QString formatName()
    {
        FMT_3D_COMBINE format = formatType();
        QString name[FMT_3D_NUM];
        name[FMT_3D_BGRX]="BGRX";
        name[FMT_3D_BGRA]="BGRA";
        name[FMT_3D_RGBX]="RGBX";
        name[FMT_3D_RGBA]="RGBA";

        name[FMT_3D_NV12]="NV12";
        name[FMT_3D_I420]="I420";
        name[FMT_3D_YUV422]="YUV422";
        name[FMT_3D_YUV411]="YUV411";
        name[FMT_3D_YUV]="YUV";

        name[FMT_3D_RGB332]="RGB332";
        name[FMT_3D_RGB444]="RGB444";
        name[FMT_3D_RGB565]="RGB565";
        name[FMT_3D_RGB666]="RGB666";

        name[FMT_3D_BGR565]="BGR565";
        name[FMT_3D_RGBX1010102]="RGBX10:10:10:2";
        name[FMT_3D_RGBA1010102]="RGBA10:10:10:2";
        return name[format];

    }
protected:
    virtual bool interleavingLine(QImage *srcLeft,QImage* srcRight)=0;
    virtual bool interleavingPixelByPixel(QImage *srcLeft,QImage* srcRight)=0;
    virtual bool convertToRawData(QImage *srcImage)=0;
    //convert the current dstbuffer into the stride buffer.
    virtual QImage * convertToStrideImage(QImage* srcImage,int stride,int height=0);
    //return the current class color format
    virtual FMT_3D_COMBINE formatType()=0;
private:
    bool resetDstBuffer(int len);

protected:
    unsigned char * m_dstbuffer;
    int m_dstlen;

    int m_width;
    int m_height;

    bool m_isLinear;
};

#endif // CONVERT3DIMAGE_H
