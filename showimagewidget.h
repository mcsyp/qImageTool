#ifndef SHOWIMAGEWIDGET_H
#define SHOWIMAGEWIDGET_H

#include <QWidget>
#include <QImage>
#include "combine3dimage.h"

class ShowImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShowImageWidget(QWidget *parent = 0);
    bool showImage(unsigned char* buffer,
                   int len,
                   int width,
                   int height,
                   Combine3DImage * comb);
protected:
    void paintEvent(QPaintEvent *);
protected:
    QImage * m_image;
};

#endif // SHOWIMAGEWIDGET_H
