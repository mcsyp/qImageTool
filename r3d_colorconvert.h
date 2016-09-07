#ifndef R3D_COLORCONVERT_H
#define R3D_COLORCONVERT_H

enum R3D_FMT_YUV422{
    R3D_FMT_YUYV=0,
    R3D_FMT_YVYU=1,
    R3D_FMT_UYVY,
    R3D_FMT_VYUY,
    R3D_FMT_YUV422_NUM
};
/*********************************
 * purpose: transform YCbCr to BGR4
 *********************************/
class R3D_YCbCrtoBGRX
{
public:
    R3D_YCbCrtoBGRX(){initConvertTable();}

    /*******************************************************
     *function:convertI420toBGRX
     *input   : pSrc, one source i420 framebuffer,
     *          srcW, the width of the pSrc, for example 640
     *          srcH, the height of the pSrc, for example 480
     *output  : pDst, the BGRX output buffer
     *purpose :convert one i420 YCbCr framebuffer into BGRX bufffer.
     *******************************************************/
    virtual void convertI420toBGRX(unsigned char * pDst,
                                   unsigned char * pSrc,
                                   int srcW,
                                   int srcH)
    {
        int framesize = srcW*srcH;
        unsigned char * Y  = pSrc;
        unsigned char * Cb  = Y + framesize;
        unsigned char * Cr  = Cb + (framesize>>2);
        int index,indexY,indexU;
        for(int j=0;j<srcH;j++){
            for(int i=0;i<srcW;i++){
                index  = (j*srcW + i)*4;
                indexY = j*srcW+i;
                indexU = (j>>1)*(srcW>>1)+(i>>1);
                pDst[index]   = YCbCrtoB(Y[indexY],Cb[indexU]);//B
                pDst[index+1] = YCbCrtoG(Y[indexY],Cb[indexU],Cr[indexU+1]);//G
                pDst[index+2] = YCbCrtoR(Y[indexY],           Cr[indexU+1]);//R
                //pDst[index+3] = 255;//A
            }
        }
    }

    /*******************************************************
     *function:convertNV12toBGRX
     *input   : pSrc, one source nv12 framebuffer,
     *          srcW, the width of the pSrc, for example 640
     *          srcH, the height of the pSrc, for example 480
     *output  : pDst, the BGRX output buffer
     *purpose :convert one nv12 YCbCr framebuffer into BGRX bufffer.
     *******************************************************/
    virtual void convertNV12toBGRX(unsigned char * pDst,
                                   unsigned char * pSrc,
                                   int srcw,
                                   int srch)
    {
        unsigned char * Y  = pSrc;
        unsigned char * UV = pSrc + srcw*srch;
        for(int j=0;j<srch;j++){
            for(int i=0;i<srcw;i++){
                int index  = (j*srcw + i)*4;
                int indexY = j*srcw+i;
                int indexUV = ((j>>1)*(srcw>>1)+(i>>1))<<1;
                pDst[index]   = YCbCrtoB(Y[indexY],UV[indexUV]);//B
                pDst[index+1] = YCbCrtoG(Y[indexY],UV[indexUV],UV[indexUV+1]);//G
                pDst[index+2] = YCbCrtoR(Y[indexY],            UV[indexUV+1]);//R
                //pDst[index+3] = 0;
            }
        }
    }
    /*******************************************************
     *function:convertYUVtoBGRX
     *input   : pSrc, one source yuv framebuffer,
     *          srcW, the width of the pSrc, for example 640
     *          srcH, the height of the pSrc, for example 480
     *output  : pDst, the BGRX output buffer
     *purpose :convert one yuv YCbCr framebuffer into BGRX bufffer.
     *******************************************************/
    virtual void convertYUVtoBGRX(unsigned char * pDst,
                                  unsigned char * pSrc,
                                  int srcw,
                                  int srch)
    {
        unsigned char * Y = pSrc;
        unsigned char * U = pSrc + srcw*srch;
        unsigned char * V = U + srcw*srch;
        for(int j=0;j<srch;j++){
            for(int i=0;i<srcw;i++){
                int index  = (j*srcw + i)*4;
                int indexYUV = j*srcw+i;
                pDst[index]   = YCbCrtoB(Y[indexYUV],U[indexYUV]);//B
                pDst[index+1] = YCbCrtoG(Y[indexYUV],U[indexYUV],V[indexYUV]);//G
                pDst[index+2] = YCbCrtoR(Y[indexYUV],            V[indexYUV]);//R
            }
        }
    }
    /*******************************************************
     *function:convertYUV411toBGRX
     *input   : pSrc, one source yuv411 framebuffer,
     *          srcW, the width of the pSrc, for example 640
     *          srcH, the height of the pSrc, for example 480
     *output  : pDst, the BGRX output buffer
     *purpose :convert one nv12 YCbCr framebuffer into BGRX bufffer.
     *******************************************************/
    virtual void convertYUV411toBGRX(unsigned char * pDst,
                                   unsigned char * pSrc,
                                   int srcw,
                                   int srch)
    {
        unsigned char * Y = pSrc;
        unsigned char * U = pSrc + srcw*srch;
        unsigned char * V = U + srcw*srch/4;
        for(int j=0;j<srch;j++){
            for(int i=0;i<srcw;i++){
                int index  = (j*srcw + i)*4;
                int indexY = j*srcw+i;
                int indexU = (j*(srcw>>2)+(i>>2));
                pDst[index]   = YCbCrtoB(Y[indexY],U[indexU]);//B
                pDst[index+1] = YCbCrtoG(Y[indexY],U[indexU],V[indexU]);//G
                pDst[index+2] = YCbCrtoR(Y[indexY],          V[indexU]);//R
            }
        }
    }
    /*******************************************************
     *function:convertYUV422PlanarToBGRX
     *input   : pSrc, one source yuv422 framebuffer,
     *          srcW, the width of the pSrc, for example 640
     *          srcH, the height of the pSrc, for example 480
     *output  : pDst, the BGRX output buffer
     *purpose :convert one yuv422 planar framebuffer into BGRX bufffer.
     *******************************************************/
    virtual void convertYUV422PlanarToBGRX(unsigned char * pDst,unsigned char * pSrc,
                                           int srcW,int srcH)
    {
        int framesize = srcW*srcH;
        unsigned char * Y  = pSrc;
        unsigned char * Cb  = Y + framesize;
        unsigned char * Cr  = Cb + (framesize>>1);
        int index,indexY,indexU;
        for(int j=0;j<srcH;j++){
            for(int i=0;i<srcW;i++){
                index  = (j*srcW + i)*4;
                indexY = j*srcW+i;
                indexU = (j>>1)*srcW+(i>>1);
                pDst[index]   = YCbCrtoB(Y[indexY],Cb[indexU]);//B
                pDst[index+1] = YCbCrtoG(Y[indexY],Cb[indexU],Cr[indexU+1]);//G
                pDst[index+2] = YCbCrtoR(Y[indexY],           Cr[indexU+1]);//R
                //pDst[index+3] = 255;//A
            }
        }
    }
    /*******************************************************
     *function:convertYUV422PackedToBGRX
     *input   : pSrc, one source yuv422 packed framebuffer,
     *          srcW, the width of the pSrc, for example 640
     *          srcH, the height of the pSrc, for example 480
     *          fmt,  the input packed format
     *output  : pDst, the BGRX output buffer
     *purpose :convert one yvu422 packed framebuffer into BGRX bufffer.
     *******************************************************/
    virtual void convertYUV422PackedToBGRX(unsigned char * pDst,unsigned char * pSrc,
                                           int srcW,int srcH,
                                           enum R3D_FMT_YUV422 fmt=R3D_FMT_YUYV)
    {
        unsigned char * yuv  = pSrc;
        unsigned char * bgrx = pDst;
        int width = srcW / 2;
        int height = srcH;

        int y0,y1,u,v;
        //asign the yuv index
        switch(fmt){
        case R3D_FMT_YUYV:
            y0 = 0;
            u  = 1;
            y1 = 2;
            v  = 3;
            break;
        case R3D_FMT_YVYU:
            y0 = 0;
            v  = 1;
            y1 = 2;
            u  = 3;
            break;
        case R3D_FMT_UYVY:
            u  = 0;
            y0 = 1;
            v  = 2;
            y1 = 3;
            break;
        default://R3D_FMT_VYUY
            v  = 0;
            y0 = 1;
            u  = 2;
            y1 = 3;
            break;
        }
        for(int y=0;y<height;y++){
            for(int x=0;x<width;x++){
                int i = (y*width + x)<<2;
                int j = i<<1;
                yuv = pSrc+i;
                bgrx = pDst+j;
                //first pixel
                bgrx[0] = YCbCrtoB(yuv[y0],yuv[u]);
                bgrx[1] = YCbCrtoG(yuv[y0],yuv[u],yuv[v]);
                bgrx[2] = YCbCrtoR(yuv[y0],       yuv[v]);
                //second pixel
                bgrx[4] = YCbCrtoB(yuv[y1],yuv[u]);
                bgrx[5] = YCbCrtoG(yuv[y1],yuv[u],yuv[v]);
                bgrx[6] = YCbCrtoR(yuv[y1],       yuv[v]);
            }
        }
    }

protected:
    /*******************************************************
     *function:initConvertTable
     *purpose :init the YCbCr to BGRX convert table.
     *******************************************************/
    virtual void initConvertTable()
    {
        for(int i=0;i<256;i++){
            unsigned char a = (unsigned char)i;
            m_iY[i]   = 1.164*(a-16);
            m_iRCr[i] = 1.596*(a-128);
            m_iGCr[i] = 0.813*(a-128);
            m_iGCb[i] = 0.392*(a-128);
            m_iBCb[i] = 2.017*(a-128);
        }
    }

    /*******************************************************
     *function:YCbCrtoBGRX
     *input   :y, cb, cr, the YCbCr value.
     *purpose :convert the YCbCr into RGB value.
     *******************************************************/
    inline unsigned char YCbCrtoR(unsigned char Y,unsigned char Cr){
        //int R=1.164*(Y-16)+1.596*(Cr-128);
        int R = m_iY[Y]+m_iRCr[Cr];
        return (unsigned char)(R>255?255:R<0?0:R);
    }
    inline unsigned char YCbCrtoG(unsigned char Y,unsigned char Cb,unsigned char Cr){
        //int G=1.164*(Y-16)-0.813*(Cr-128)-0.392*(Cb-128);
        int G = m_iY[Y]-m_iGCr[Cr]-m_iGCb[Cb];
        return (unsigned char)(G>255?255:G<0?0:G);
    }
    inline unsigned char YCbCrtoB(unsigned char Y,unsigned char Cb){
        //int B=1.164*(Y-16)+2.017*(Cb-128);
        int B = m_iY[Y]+m_iBCb[Cb];
        return (unsigned char)(B>255?255:B<0?0:B);
    }
protected:
    //RGB to nv12 convert table.
    short m_iY[256];
    short m_iRCr[256];
    short m_iGCr[256];
    short m_iGCb[256];
    short m_iBCb[256];
};

/*********************************
 * purpose: transform YCbCr to BGRX
 *********************************/
class R3D_BGRXtoYCbCr
{
public:
    R3D_BGRXtoYCbCr(){initConvertTable();}
    /*******************************************************
     *function:convertBGRXtoI420
     *input   :pDst,the i420 framebuffer
     *         pSrc,the BGRX source framebuffer
     *         width,  the width  of source framebuffer
     *         height, the height of source framebuffer
     *purpose :convert the BGRX framebuffer to I420 planar format.
     *******************************************************/
    virtual void convertBGRXtoI420(unsigned char *pDst,
                                  unsigned char *pSrc,
                                  int width,
                                  int height)
    {
        /***********************************************
         *i420 format is: Y=width*height|
         *                U=width*height/4|
         *                V=width*height/4|
         ***********************************************/
        int framesize = width*height;
        unsigned char * Y = pDst;
        unsigned char * U = pDst+framesize;
        unsigned char * V = U+(framesize>>2);
        int rowsize = (width<<2);

        for(int y=0;y<height;y++){
            for(int x=0;x<width;x++)
            {
                int j = y*width+x;
                int i = j<<2;//j*4
                /******************************************
                 *RGBA color in memory format is B|G|R|A|
                 ******************************************/
                Y[j] = RGBtoY(pSrc[i+2],pSrc[i+1],pSrc[i]);
                if(x%2==1 && y%2==1)
                {
                    j = (width>>1) * (y>>1) + (x>>1);
                    U[j] =((RGBtoU(pSrc[i+2],          pSrc[i+1],          pSrc[i])+
                            RGBtoU(pSrc[i-4+2],        pSrc[i-4+1],        pSrc[i-4])+
                            RGBtoU(pSrc[i-rowsize+2],  pSrc[i-rowsize+1],  pSrc[i-rowsize])+
                            RGBtoU(pSrc[i-rowsize-4+2],pSrc[i-rowsize-4+1],pSrc[i-rowsize-4]))>>2);
                    V[j] =((RGBtoV(pSrc[i+2],          pSrc[i+1],          pSrc[i])+
                            RGBtoV(pSrc[i-4+2],        pSrc[i-4+1],        pSrc[i-4])+
                            RGBtoV(pSrc[i-rowsize+2],  pSrc[i-rowsize+1],  pSrc[i-rowsize])+
                            RGBtoV(pSrc[i-rowsize-4+2],pSrc[i-rowsize-4+1],pSrc[i-rowsize-4]))>>2);
                }
             }
        }
    }

    /*******************************************************
     *function:convertBGRXtoNV12
     *input   :pDst,the i420 framebuffer
     *         pSrc,the BGRX source framebuffer
     *         width,  the width  of source framebuffer
     *         height, the height of source framebuffer
     *purpose :convert the BGRX framebuffer to nv12 planar format.
     *******************************************************/
    virtual void convertBGRXtoNV12(unsigned char *pDst,
                                  unsigned char *pSrc,
                                  int width,
                                  int height)
    {
        /***********************************************
         *nv12 format is: Y=width*height|
         *                UV=2*width*height/4|
         ***********************************************/
        int framesize = width*height;
        unsigned char * Y = pDst;
        unsigned char * U = pDst+framesize;
        unsigned char * V = U;
        int rowsize = (width<<2);//width*4

        for(int y=0;y<height;y++){
            for(int x=0;x<width;x++)
            {
                int j = y*width+x;
                int i = j<<2;//j*4
                /******************************************
                 *RGBA color in memory format is B|G|R|A|
                 ******************************************/
                Y[j] = RGBtoY(pSrc[i+2],pSrc[i+1],pSrc[i]);
                if(x%2==1 && y%2==1)
                {
                    j = (width>>1) * (y>>1) + (x>>1);
                    U[2*j] = ((RGBtoU(pSrc[i+2],          pSrc[i+1],          pSrc[i])+
                               RGBtoU(pSrc[i-4+2],        pSrc[i-4+1],        pSrc[i-4])+
                               RGBtoU(pSrc[i-rowsize+2],  pSrc[i-rowsize+1],  pSrc[i-rowsize])+
                               RGBtoU(pSrc[i-rowsize-4+2],pSrc[i-rowsize-4+1],pSrc[i-rowsize-4]))>>2);
                    V[2*j+1]=((RGBtoV(pSrc[i+2],          pSrc[i+1],          pSrc[i])+
                               RGBtoV(pSrc[i-4+2],        pSrc[i-4+1],        pSrc[i-4])+
                               RGBtoV(pSrc[i-rowsize+2],  pSrc[i-rowsize+1],  pSrc[i-rowsize])+
                               RGBtoV(pSrc[i-rowsize-4+2],pSrc[i-rowsize-4+1],pSrc[i-rowsize-4]))>>2);
                }
            }
        }
    }
    /*******************************************************
     *function:convertBGRXtoYUV
     *input   :pDst,the YUV framebuffer
     *         pSrc,the BGRX source framebuffer
     *         width,  the width  of source framebuffer, eg. 640x480 width is 640
     *         height, the height of source framebuffer
     *purpose :convert the BGRX framebuffer to yuv
     *******************************************************/
    virtual void convertBGRXtoYUV(unsigned char *pDst,
                                  unsigned char *pSrc,
                                  int width,
                                  int height)
    {
        /***********************************************
         *yuv format is: Y=w h |
         *               U=w h |
         *               V=w h |
         ***********************************************/
        int framesize = width*height;
        unsigned char * Y = pDst;
        unsigned char * U = Y+framesize;
        unsigned char * V = U+framesize;

        for(int y=0;y<height;y++){
            for(int x=0;x<width;x++)
            {
                int j = y*width+x;
                int i = j<<2;//j*4
                /******************************************
                 *RGBA color in memory format is B|G|R|A|
                 ******************************************/
                Y[j] = RGBtoY(pSrc[i+2],pSrc[i+1],pSrc[i]);
                U[j] = RGBtoU(pSrc[i+2],pSrc[i+1],pSrc[i]);
                V[j] = RGBtoV(pSrc[i+2],pSrc[i+1],pSrc[i]);

            }
        }
    }
    /*******************************************************
     *function:convertBGRXtoYUV411
     *input   :pDst,the YUV411 framebuffer
     *         pSrc,the BGRX source framebuffer
     *         width,  the width  of source framebuffer, eg. 640x480 width is 640
     *         height, the height of source framebuffer
     *purpose :convert the BGRX framebuffer to nv12 planar format.
     *******************************************************/
    virtual void convertBGRXtoYUV411(unsigned char *pDst,
                                    unsigned char *pSrc,
                                    int width,
                                    int height)
    {
        /***********************************************
         *yuv411 format is: Y=w   h |
         *                  U=w/4 h |
         *                  V=w/4 h |
         ***********************************************/
        int framesize = width*height;
        unsigned char * Y = pDst;
        unsigned char * U = Y+framesize;
        unsigned char * V = U+framesize/4;

        for(int y=0;y<height;y++){
            for(int x=0;x<width;x++)
            {
                int j = y*width+x;
                int i = j<<2;//j*4
                /******************************************
                 *RGBA color in memory format is B|G|R|A|
                 ******************************************/
                Y[j] = RGBtoY(pSrc[i+2],pSrc[i+1],pSrc[i]);
                if(x%4==3){//sample to the every last 4.
                    j = (width>>2)*y + (x>>2);
                    U[j]=(RGBtoU(pSrc[i+2],pSrc[i+1],pSrc[i])
                            +RGBtoU(pSrc[i-4+2],pSrc[i-4+1],pSrc[i-4])
                            +RGBtoU(pSrc[i-8+2],pSrc[i-8+1],pSrc[i-8])
                            +RGBtoU(pSrc[i-12+2],pSrc[i-12+1],pSrc[i-12]))/4;
                    V[j]=(RGBtoV(pSrc[i+2],pSrc[i+1],pSrc[i])
                          +RGBtoV(pSrc[i-4+2],pSrc[i-4+1],pSrc[i-4])
                          +RGBtoV(pSrc[i-8+2],pSrc[i-8+1],pSrc[i-8])
                          +RGBtoV(pSrc[i-12+2],pSrc[i-12+1],pSrc[i-12]))/4;
                }
            }
        }
    }
    /*******************************************************
     *function:convertBGRXtoYUV422Packed
     *input   :pDst,the i420 framebuffer
     *         pSrc,the BGRX source framebuffer
     *         width,  the width  of source framebuffer
     *         height, the height of source framebuffer
     *purpose :convert the BGRX framebuffer to YUV422 packed format.
     *******************************************************/
    virtual void convertBGRXtoYUV422Packed(unsigned char *pDst,unsigned char *pSrc,
                                           int width,int height,
                                           enum R3D_FMT_YUV422 fmt=R3D_FMT_YUYV)
    {
        unsigned char * yuv4;//yuv4 is one of YUYV YVYU UYVY VYUY
        int w = width / 2;
        unsigned char y0,y1,u,v;
        int i,j;

        for(int y=0;y<height;y++){
            for(int x=0;x<w;x++)
            {
                i = (y*w+x)<<2;
                j = i<<1;//i*2
                yuv4 = pDst+i;
                y0 = RGBtoY(pSrc[j+2],pSrc[j+1],pSrc[j]);//y0
                y1 = RGBtoY(pSrc[j+6],pSrc[j+5],pSrc[j+4]);//y1
                u  = ((RGBtoU(pSrc[j+2],pSrc[j+1],pSrc[j])+
                       RGBtoU(pSrc[j+6],pSrc[j+5],pSrc[j+4]))>>1);//u
                v  = ((RGBtoV(pSrc[j+2],pSrc[j+1],pSrc[j])+
                       RGBtoV(pSrc[j+6],pSrc[j+5],pSrc[j+4]))>>1);//v
                switch(fmt){
                case R3D_FMT_YUYV:
                    yuv4[0]=y0;
                    yuv4[1]=u;
                    yuv4[2]=y1;
                    yuv4[3]=v;
                    break;
                case R3D_FMT_YVYU:
                    yuv4[0]=y0;
                    yuv4[1]=v;
                    yuv4[2]=y1;
                    yuv4[3]=u;
                    break;
                case R3D_FMT_UYVY:
                    yuv4[0]=u;
                    yuv4[1]=y0;
                    yuv4[2]=v;
                    yuv4[3]=y1;
                    break;
                default://R3D_FMT_VYUY
                    yuv4[0]=v;
                    yuv4[1]=y0;
                    yuv4[2]=u;
                    yuv4[3]=y1;
                    break;
                }
            }
        }
    }
    virtual void convertBGRXtoYUV422Planar(unsigned char *pDst,unsigned char *pSrc,
                                           int width,int height)
    {
        int framesize = width*height;
        unsigned char * Y = pDst;
        unsigned char * U = pDst+framesize;
        unsigned char * V = U+framesize/2;

        for(int y=0;y<height;y++){
            for(int x=0;x<width;x++)
            {
                int i = (y*width+x);
                int j = i<<2;//j=i*4
                Y[i] = RGBtoY(pSrc[j+2],pSrc[j+1],pSrc[j]);
                if(x%2==1){
                    i = (width>>1) * y + (x>>1);
                    U[i] = ((RGBtoU(pSrc[j+2],pSrc[j+1],pSrc[j])+
                             RGBtoU(pSrc[j-2],pSrc[j-3],pSrc[j-4]))>>1);//u
                    V[i] = ((RGBtoV(pSrc[j+2],pSrc[j+1],pSrc[j])+
                             RGBtoV(pSrc[j-2],pSrc[j-3],pSrc[j-4]))>>1);//v
                }
            }
        }
    }
protected:
    virtual  void initConvertTable()
    {
        for(int i=0;i<256;i++)
        {
            //y channel table
            m_iYR[i] = (unsigned short)((1053*i)>>12);
            m_iYG[i] = (unsigned short)((2064*i)>>12);
            m_iYB[i] = (unsigned short)(( 401*i)>>12);

            //u channel table
            m_iUR[i] = (unsigned short)(( 606*i)>>12);
            m_iUG[i] = (unsigned short)((1192*i)>>12);
            m_iUB[i] = (unsigned short)((1798*i)>>12);

            //v channel table
            m_iVR[i] = (unsigned short)((1798*i)>>12);
            m_iVG[i] = (unsigned short)((1507*i)>>12);
            m_iVB[i] = (unsigned short)(( 291*i)>>12);
        }
    }
    inline unsigned char RGBtoY(unsigned char r, unsigned char g, unsigned char b){
        unsigned char Y =  m_iYR[r]+m_iYG[g]+m_iYB[b]+16;
        return (Y>255?255:Y<0?0:Y);
    }

    inline unsigned char RGBtoU(unsigned char r, unsigned char g, unsigned char b){
        unsigned char U =  -m_iUR[r]-m_iUG[g]+m_iUB[b]+128;
        return (U>255?255:U<0?0:U);
    }

    inline unsigned char RGBtoV(unsigned char r, unsigned char g, unsigned char b){
        unsigned char V =  m_iVR[r]-m_iVG[g]-m_iVB[b]+128;
        return (V>255?255:V<0?0:V);
    }

protected:
    //the yuv tables for rgb to yuv conversion
    unsigned short m_iYR[256];
    unsigned short m_iYG[256];
    unsigned short m_iYB[256];

    unsigned short m_iUR[256];
    unsigned short m_iUG[256];
    unsigned short m_iUB[256];

    unsigned short m_iVR[256];
    unsigned short m_iVG[256];
    unsigned short m_iVB[256];
};

#if 0
/****************************************************
 *YUV and RGB color space converting
 ****************************************************/
/*****************************************************
 *purpose :transform RGB to YUV.
 ******************************************************/
#define R3D_RGB_Y(R,G,B) ((unsigned char)(0.299*(R)+0.587*(G)+0.114*(B)))
#define R3D_RGB_U(R,G,B) ((unsigned char)(-0.147*(R)-0.289*(G)+0.436*(B)))
#define R3D_RGB_V(R,G,B) ((unsigned char)(0.615*(R)-0.515*(G)-0.100*(B)))
/*****************************************************
 *purpose :transform YUV to RGB.
 ******************************************************/
#define R3D_YUV_R(Y,U,V) ((unsigned char)((Y)+1.140*(V)))
#define R3D_YUV_G(Y,U,V) ((unsigned char)((Y)-0.394*(U)-0.581*(V)))
#define R3D_YUV_B(Y,U,V) ((unsigned char)((Y)+2.032*(U)))

#endif
#endif // R3D_COLORCONVERT_H
