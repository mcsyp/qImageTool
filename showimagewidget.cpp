#include "showimagewidget.h"
#include <QPainter>
#include <QImage>
#include <QRect>
#include <QDebug>
#include <QDesktopWidget>

#include "r3d_colorconvert.h"

#include "combine3dimagebgrx.h"
#include "combine3dimagebgra.h"
#include "combine3dimagergba.h"
#include "combine3dimagergbx.h"
#include "combine3dimagenv12.h"
#include "combine3dimagei420.h"
ShowImageWidget::ShowImageWidget(QWidget *parent) :
    QWidget(parent)
{
    m_image = 0;
}
bool ShowImageWidget::showImage(unsigned char *buffer,
                                int len,
                                int width,
                                int height,
                                Combine3DImage * combine)
{
    Combine3DImage *comb = combine;
    bool ret = false;
    if(comb==0)return false;

    /*malloc new image*/
    if(m_image)delete m_image;
    m_image = new QImage(width,height,QImage::Format_RGB32);
    if(m_image->isNull()){
        qDebug()<<tr("[%1,%2]fail to notify the image data.").arg(__FILE__).arg(__LINE__);
        goto FAIL;
    }

    /*load image*/
    ret = comb->loadBinToImage(m_image,buffer,len);
    if(!ret){
        qDebug()<<tr("[%1,%2]fail to load the buffer data to image.").arg(__FILE__).arg(__LINE__);
        goto FAIL;
    }


    //set the dialog size
    update();
    setVisible(true);
    return ret;
FAIL:
    if(m_image){
        delete m_image;
        m_image = 0;
    }
    return false;
}
void ShowImageWidget::paintEvent(QPaintEvent *e)
{
    //QWidget::paintEvent(e);
    if(m_image){
        QPainter painter(this);
        QRect rect(0,0,width(),height());
        painter.drawImage(rect,*m_image);
    }
}
