#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>
#include <QImage>
#include <QFile>

#include "combine3dimagebgrx.h"
#include "combine3dimagebgra.h"
#include "combine3dimagergba.h"
#include "combine3dimagergbx.h"
#include "combine3dimagenv12.h"
#include "combine3dimagei420.h"
#include "combine3dimageyuv422.h"
#include "combine3dimagergb332.h"
#include "combine3dimagergb444.h"
#include "combine3dimagergb565.h"
#include "combine3dimagergb666.h"
#include "combine3dimagebgr565.h"
#include "combine3dimagergbx1010102.h"
#include "combine3dimagergba1010102.h"
#include "combine3dimageyuv411.h"
#include "combine3dimageyuv.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    //init qMessage box
    m_messageBox = new QMessageBox(this);
    m_messageBox->setIcon(QMessageBox::Information);
    m_messageBox->addButton("OK",QMessageBox::YesRole);

    //init the browser box
    m_browser = new QFileDialog(this);//create a file dialog.

    //init combine
    for(int i=0;i<Combine3DImage::FMT_3D_NUM;i++){
        m_combine[i] = 0;
    }
    /* to add a color format, new it here*/
    m_combine[Combine3DImage::FMT_3D_BGRX] = new Combine3DImageBGRX;
    m_combine[Combine3DImage::FMT_3D_BGRA] = new Combine3DImageBGRA;
    m_combine[Combine3DImage::FMT_3D_RGBX] = new Combine3DImageRGBX;
    m_combine[Combine3DImage::FMT_3D_RGBA] = new Combine3DImageRGBA;
    m_combine[Combine3DImage::FMT_3D_BGR565] = new Combine3DImageBGR565;

    m_combine[Combine3DImage::FMT_3D_RGB332] = new Combine3DImageRGB332;
    m_combine[Combine3DImage::FMT_3D_RGB444] = new Combine3DImageRGB444;
    m_combine[Combine3DImage::FMT_3D_RGB565] = new Combine3DImageRGB565;
    m_combine[Combine3DImage::FMT_3D_RGB666] = new Combine3DImageRGB666;
    m_combine[Combine3DImage::FMT_3D_RGBX1010102] = new Combine3DImageRGBX1010102;
    m_combine[Combine3DImage::FMT_3D_RGBA1010102] = new Combine3DImageRGBA1010102;

    m_combine[Combine3DImage::FMT_3D_NV12] = new Combine3DImageNV12;
    m_combine[Combine3DImage::FMT_3D_I420] = new Combine3DImageI420;
    m_combine[Combine3DImage::FMT_3D_YUV411] = new Combine3DImageYUV411;
    m_combine[Combine3DImage::FMT_3D_YUV422] = new Combine3DImageYUV422;
    m_combine[Combine3DImage::FMT_3D_YUV] = new Combine3DImageYUV;

    {//init the step control interface
        connect(ui->preStepbtn,SIGNAL(clicked()),this,SLOT(onPreStepbtnClickedCB()));
        connect(ui->nextStepbtn,SIGNAL(clicked()),this,SLOT(onNextStepbtnClickedCB()));
        connect(ui->exportbtn,SIGNAL(clicked()),this,SLOT(onNextStepbtnClickedCB()));
        connect(ui->stackedWidget,SIGNAL(currentChanged(int)),this,SLOT(onStackedCurretnChangedCB(int)));

        onStackedCurretnChangedCB(0);
    }

    {//init the input image interface
        //init the work type check boxes
        connect(ui->work2dchk,SIGNAL(stateChanged(int)),this,SLOT(onWorktypechkStateChangedCB(int)));
        connect(ui->work3dchk,SIGNAL(stateChanged(int)),this,SLOT(onWorktypechkStateChangedCB(int)));

        //init file input related thing.
        connect(ui->browsebtn,SIGNAL(clicked()),this,SLOT(onInputLeftBrowsebtnCB()));
        connect(ui->browsebtn2,SIGNAL(clicked()),this,SLOT(onInputRightBrowsebtnCB()));
        //init file output
        connect(ui->browsebtn3,SIGNAL(clicked()),this,SLOT(onOutputBrowsebtnCB()));
        //init interface.
        onWorktypechkStateChangedCB(0);
    }

    {//init the color format interface
        //init the pre-alpha related ui
        connect(ui->outputFmtbox,SIGNAL(currentIndexChanged(int)),this,SLOT(onOutputColorFormatIndexChangedCB(int)));
        connect(ui->alphaslide,SIGNAL(valueChanged(int)),this,SLOT(onAlphaValueChangedCB(int)));
        connect(ui->alphachk,SIGNAL(stateChanged(int)),this,SLOT(onAlphaChkStateChangedCB(int)));

        //init yuv422 format layout ui
        connect(ui->yuvPackedbox,SIGNAL(stateChanged(int)),this,SLOT(onYuvLayoutFormatChangedCB(int)));
        connect(ui->yuvPlanarbox,SIGNAL(stateChanged(int)),this,SLOT(onYuvLayoutFormatChangedCB(int)));

        ui->outputFmtbox->setCurrentIndex(0);
        onYuvLayoutFormatChangedCB(0);
    }
    {//init the stride setting interface
        connect(ui->outStridechk,SIGNAL(stateChanged(int)),this,SLOT(onOutStridechkStateChangedCB(int)));
        ui->outStridechk->setChecked(false);
    }
    {//init the browse image dialog
        connect(ui->imageFmtbox,SIGNAL(currentIndexChanged(int)),this,SLOT(onImageFmtboxIndexChangedCB(int)));
        connect(ui->showbtn,SIGNAL(clicked()),this,SLOT(onShowImagebtnClickedCB()));
        connect(ui->browseYuv422Packedchk,SIGNAL(stateChanged(int)),this,SLOT(onBrowseLayoutFormatChangedCB(int)));
        connect(ui->browseYuv422Planarchk,SIGNAL(stateChanged(int)),this,SLOT(onBrowseLayoutFormatChangedCB(int)));
        onBrowseLayoutFormatChangedCB(0);
        connect(ui->imageBrowsebtn,SIGNAL(clicked()),this,SLOT(onResultBrowsebtnCB()));
    }
    ui->stackedWidget->setCurrentIndex(STACK_INPUTIMAGE);

    /*init color formats*/
    {
        ui->outputFmtbox->clear();
        ui->imageFmtbox->clear();
        for(int i=0;i<Combine3DImage::FMT_3D_NUM;i++){
            //qDebug()<<tr("[%1,%2]i=%3").arg(__FUNCTION__).arg(__LINE__).arg(i);
            ui->outputFmtbox->insertItem(i,m_combine[i]->formatName());
            ui->imageFmtbox->insertItem(i,m_combine[i]->formatName());
        }
        ui->outputFmtbox->setCurrentIndex(0);
        ui->imageFmtbox->setCurrentIndex(0);
    }

    {/*init output YUV422 format*/
        QStringList yuvfmtlst;
        yuvfmtlst<<"YUYV"<<"YVYU"<<"UYVY"<<"VYUY";
        ui->yuvFmtbox->clear();
        ui->browseYUV422Fmtbox->clear();
        for(int i=0;i<R3D_FMT_YUV422_NUM;i++){
            ui->yuvFmtbox->insertItem(i,yuvfmtlst.at(i));
            ui->browseYUV422Fmtbox->insertItem(i,yuvfmtlst.at(i));
        }
        ui->yuvFmtbox->setCurrentIndex(R3D_FMT_YUYV);
        ui->browseYUV422Fmtbox->setCurrentIndex(R3D_FMT_YUYV);
    }


    ui->tabWidget->setCurrentIndex(0);
    setIsWorking(false);

#if CONFIG_SAVE
    loadConfig();
#endif
}

MainWidget::~MainWidget()
{
    delete ui;
}
void MainWidget::closeEvent(QCloseEvent *e)
{
#if CONFIG_SAVE
    saveConfig();
#endif
}
void MainWidget::loadConfig()
{
    FILE* f = fopen(CONFIG_FILE,"r");
    if(f==NULL){
        return;
    }

    char content[128];
    enum CONFIG_SAVE_ITEM item;
    int ret = 0;
    int value;
    QRect rect = this->geometry();
    while(ret!=-1){
        ret = fscanf(f,"[%d]=%s\n",&item,content);
        switch(item){
        case CONFIG_WORKTYPE:
            value = atol(content);
            //load work type
            switch(value){
            case WORK_2D:
                ui->work2dchk->setChecked(true);
                break;
            case WORK_3D_COMBINE:
                ui->work3dchk->setChecked(true);
                break;
            }
            break;
        case CONFIG_IMAGE_0:
            if(strlen(content)!=0){
                ui->leftpath->setText(QString(content));
            }
            break;
        case CONFIG_IMAGE_1:
            if(strlen(content)!=0){
                ui->rightpath->setText(QString(content));
            }
            break;
        case CONFIG_OUTIMAGE:
            if(strlen(content)!=0){
                ui->outpath->setText(QString(content));
            }
            break;
        case CONFIG_INTERLEAVEMODE:
            value = atol(content);
            setInterLeavingMode(value);
            break;
        case CONFIG_OUTPUTCOLORFORMAT:
            value = atol(content);
            setOutputColorFormat((enum  Combine3DImage::FMT_3D_COMBINE)value);
            break;
        case CONFIG_BROWSE_IMAGEPATH:
            if(strlen(content)!=0){
                ui->imagepathtxt->setText(QString(content));
            }
            break;
        case CONFIG_BROWSE_WIDTH:
            if(strlen(content)!=0){
                ui->imageWidthtxt->setText(QString(content));
            }
            break;
        case CONFIG_BROWSE_HEIGHT:
            if(strlen(content)!=0){
                ui->imageHeighttxt->setText(QString(content));
            }
            break;
        case CONFIG_BROWSE_COLORFORMAT:
            value = atol(content);
            ui->imageFmtbox->setCurrentIndex(value);
            break;
        case CONFIG_APP_WIDTH:
            value = atol(content);
            if(value>0){
                rect.setWidth(value);
            }
            break;
        case CONFIG_APP_HEIGHT:
            value = atol(content);
            if(value>0){
                rect.setHeight(value);
            }
            break;
        case CONFIG_STRIDE_ENABLED:
            value = atol(content);
            ui->outStridechk->setChecked(((value)?true:false));
            break;
        case CONFIG_STRIDE_VALUE:
            ui->outStridetxt->setText(QString(content));
            break;
        case CONFIG_MEMORY:
            value = atol(content);
            if(value){
                ui->memLinearradio->setChecked(true);
            }else{
                ui->memTileBasedradio->setChecked(true);
            }
            break;
        case CONFIG_BROWSE_MEMORY:
            value = atol(content);
            if(value){
                ui->imageBrowseLinrdo->setChecked(true);
            }else{
                ui->imageBrowseTLBrdo->setChecked(true);
            }
            break;
        }
    }
    this->setGeometry(rect);
    //onMessageCB("Config info loaded.");
    //updateOutputImageStride();
    fclose(f);
}

void MainWidget::setOutputColorFormat(Combine3DImage::FMT_3D_COMBINE index)
{
    if(index<Combine3DImage::FMT_3D_NUM && index>=Combine3DImage::FMT_3D_BGRX)
    {
        ui->outputFmtbox->setCurrentIndex(index);
    }
}
int MainWidget::interleavingMode()
{
    if(ui->lineradio->isChecked()){
        return Combine3DImage::INTERLEAVE_LINE;
    }else{
        return Combine3DImage::INTERLEAVE_PIXEL_BY_PIXEL;
    }
}
void MainWidget::setInterLeavingMode(int mode)
{
    switch(mode){
    case Combine3DImage::INTERLEAVE_LINE:
        ui->lineradio->setChecked(true);
        break;
    case Combine3DImage::INTERLEAVE_PIXEL_BY_PIXEL:
        ui->pixelradio->setChecked(true);
        break;
    }
}
void MainWidget::saveConfig()
{
    FILE* f = fopen(CONFIG_FILE,"w");
    QHash<int, QString> hash;
    if(f==NULL){
        onMessageCB("[ERROR]fail to save config");
        return;
    }
    hash.clear();
    //save the first interface
    qDebug()<<tr("worktype = %1").arg(m_currentWorkType);
    hash.insert(CONFIG_WORKTYPE,tr("%1").arg(m_currentWorkType));
    hash.insert(CONFIG_IMAGE_0,ui->leftpath->text());
    hash.insert(CONFIG_IMAGE_1,ui->rightpath->text());
    hash.insert(CONFIG_OUTIMAGE,ui->outpath->text());
    hash.insert(CONFIG_INTERLEAVEMODE,tr("%1").arg(interleavingMode()));
    hash.insert(CONFIG_OUTPUTCOLORFORMAT,tr("%1").arg(ui->outputFmtbox->currentIndex()));
    hash.insert(CONFIG_BROWSE_IMAGEPATH,ui->imagepathtxt->text());
    hash.insert(CONFIG_BROWSE_WIDTH,ui->imageWidthtxt->text());
    hash.insert(CONFIG_BROWSE_HEIGHT,ui->imageHeighttxt->text());
    hash.insert(CONFIG_BROWSE_COLORFORMAT,tr("%1").arg(ui->imageFmtbox->currentIndex()));
    hash.insert(CONFIG_STRIDE_ENABLED,tr("%1").arg(((ui->outStridechk->isChecked())?1:0)));
    hash.insert(CONFIG_STRIDE_VALUE,ui->outStridetxt->text());
    hash.insert(CONFIG_MEMORY,tr("%1").arg(((ui->memLinearradio->isChecked())?1:0)));
    hash.insert(CONFIG_BROWSE_MEMORY,tr("%1").arg(((ui->imageBrowseLinrdo->isChecked())?1:0)));

    QRect r = this->geometry();
    hash.insert(CONFIG_APP_WIDTH,tr("%1").arg(r.width()));
    hash.insert(CONFIG_APP_HEIGHT,tr("%1").arg(r.height()));
    //save the hash table.
    for(int i=0;i<CONFIG_NUM;i++){
        QString content = hash.value(i);
        if(!content.isEmpty()){
            //printf("[%s,%d]str=%s.\n",__FILE__,__LINE__,content.trimmed().toLatin1().data());
            fprintf(f,"[%d]=%s\n",i,content.trimmed().toLatin1().data());
        }
    }
    fclose(f);
}

void MainWidget::onPreStepbtnClickedCB()
{
    int index = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(index-1);
}
void MainWidget::onNextStepbtnClickedCB()
{
    int index = ui->stackedWidget->currentIndex();
    bool ret = false;
    int dstindex=-1;
    switch(index)
    {
    case STACK_INPUTIMAGE://the input image interface
        ret = stackedCheckInputImages();
        break;
    case STACK_PIXELLAYOUT://the pixel layout interface
        ret = stackedCheckPixelLayout();
        break;
    case STACK_OUTPUTFORMAT:
        ret = stackedCheckOutputColorFormat();
        break;
    case STACK_OUTPUTSTRIDE:
        ret = exportImage();
        dstindex = 0;
        break;
    default:
        qDebug()<<tr("[%1,%2]unknown interface index.").arg(__FUNCTION__).arg(__LINE__);
        return;
        break;
    }
    if(ret){
        if(dstindex<0){
            ui->stackedWidget->setCurrentIndex(index+1);
        }else{
            ui->stackedWidget->setCurrentIndex(dstindex);
        }
    }else{
        /*TODO error message;*/
        //onMessageCB(tr("ERROR: invalid input parameters in %1 section.").arg(index));
    }
}
void MainWidget::onStackedCurretnChangedCB(int index)
{
    QString name[]={"Image Input",
                     "Pixel Layout",
                     "Color Format",
                     "Stride Setting"};
    /*update ui settings*/
    ui->preStepbtn->setVisible(true);
    ui->nextStepbtn->setVisible(true);
    ui->exportbtn->setVisible(false);
    if(index<=0){
        ui->preStepbtn->setVisible(false);
    }
    if(index==ui->stackedWidget->count()-1){
        ui->exportbtn->setVisible(true);
        ui->nextStepbtn->setVisible(false);
    }

    ui->pageTitlelbl->setText(name[index]);
    ui->pageTitlelbl2->setText(tr("step:%1/%2")
                              .arg(index+1)
                              .arg(ui->stackedWidget->count()));
}
bool MainWidget::stackedCheckInputImages()
{
    QImage image0(ui->leftpath->text());
    QImage image1(ui->rightpath->text());
    bool ret = true;

    if(ui->outpath->text().isNull() ||
       ui->outpath->text().isEmpty()){
        return false;
    }
    switch(m_currentWorkType)
    {
    case WORK_2D:
        if(image0.isNull()){
            onMessageCB("Input invalid image path.");
            ret = false;
        }
        break;
    case WORK_3D_COMBINE:
        if(image0.isNull()  ||
           image1.isNull()  ||
           image0.width()!=image1.width()||
           image0.height()!=image1.height())
        {
            onMessageCB("Either left or right images is invalid image.");
            qDebug()<<tr("[%1,%2]Left and right images are not valid images.\n")
                      .arg(__FUNCTION__).arg(__LINE__);
            ret = false;
        }
        break;
    }
    return ret;
}
bool MainWidget::stackedCheckPixelLayout()
{
    /*TODO: currently nothing to check in this section*/
    return true;
}
bool MainWidget::stackedCheckOutputColorFormat()
{
    bool isTlb = ui->memTileBasedradio->isChecked();
    bool is3D  = ui->work3dchk->isChecked();

    int stride;
    int index = ui->outputFmtbox->currentIndex();
    int num = 1;
    QImage image(ui->leftpath->text());

    if(image.isNull())return false;

    //if 3D is enabled
    if(is3D && ui->pixelradio->isChecked()){
        num = 2;
    }
    float bpp = this->m_combine[index]->combineFMTBpp();
    stride = bpp*num*image.width();
    int height = image.height();

    //if tlb is enabled.
    if(isTlb){
        stride = m_combine[index]->tileBasedStride(num*image.width());
        height = m_combine[index]->tileBasedHeight(height);
    }

    ui->outStridelbl->setText(tr("%1").arg(stride));
    ui->outStridetxt->setText(tr("%1").arg(stride));
    ui->outHeightlbl->setText(tr("%1").arg(height));

    return true;
}
bool MainWidget::exportImage()
{
    bool ret=false;
    Combine3DImage* comb = m_combine[ui->outputFmtbox->currentIndex()];
    setIsWorking(true);
    switch(m_currentWorkType){
    case WORK_2D:
        ret = generate2DImageBin(comb);
        break;
    case WORK_3D_COMBINE:
        ret = generate3DImageBin(comb);
        break;
    default:
        onMessageCB(tr("[ERROR]No valid work type is selected."));
        break;
    }

    if(ret){
        //save the data to file.
        const char * fname = ui->outpath->text().toLatin1().data();
        printf("[%s,%d]str=%s.\n",__FILE__,__LINE__,fname);
        FILE * fdst = fopen(fname,"wb+");
        if(fdst==0){//check if the output file path is correct.
            onMessageCB("[ERROR]Output image path parameter error.");
            ret = false;
            return ret;
        }
        unsigned char * rawbuffer = comb->data();
        int rawlen = comb->datasize();

        //convert linear binary into tile based memory.
        if(ui->memTileBasedradio->isChecked())
        {
            unsigned char * tlbbuffer = (unsigned char *)malloc(rawlen*2);
            if(tlbbuffer==0){
                ret=false;
                onMessageCB(tr("[ERROR]Fail to malloc the tile based buffer."));
                return ret;
            }

            if(comb->convertLinearToTileBasedBuffer(tlbbuffer,
                                                    rawbuffer,rawlen,
                                                    comb->width(),comb->height()))
            {
                int dstlen = comb->datasize();
                ret = true;
                fwrite(tlbbuffer,1,dstlen,fdst);
            }else{
                ret = false;
            }
            free(tlbbuffer);
        }else{//still linear memory.
            //save to a output file
            fwrite(rawbuffer,1,rawlen,fdst);
        }

        if(fdst){
            fflush(fdst);
            fclose(fdst);
            fdst = 0;
        }
    }

    setIsWorking(false);

    if(!ret){
        if(ui->outStridechk->isChecked())
            onMessageCB("[FAIL]Please check your stride value setting.");
        else
            onMessageCB("[FAIL]fail to convert the input images.");
    }else{
        onMessageCB(tr("[SUCCESS]output image width=%1 , height=%2, buffer len=%3")
                    .arg(comb->width())
                    .arg(comb->height())
                    .arg(comb->datasize()));
        ui->imagepathtxt->setText(ui->outpath->text());
        ui->imageFmtbox->setCurrentIndex(ui->outputFmtbox->currentIndex());
        ui->imageWidthtxt->setText(tr("%1").arg(comb->width()));
        ui->imageHeighttxt->setText(tr("%1").arg(comb->height()));
        ui->browseYuv422Packedchk->setChecked(ui->yuvPackedbox->isChecked());
        ui->browseYUV422Fmtbox->setCurrentIndex(ui->yuvFmtbox->currentIndex());

        ui->imageBrowseLinrdo->setChecked(ui->memLinearradio->isChecked());
        ui->imageBrowseTLBrdo->setChecked(ui->memTileBasedradio->isChecked());
    }
    return ret;
}
void MainWidget::setIsWorking(bool b)
{
    ui->tabWidget->setEnabled(!b);
}
bool MainWidget::generate3DImageBin(Combine3DImage* comb)
{
    int inter_mode = Combine3DImage::INTERLEAVE_LINE;
    int fmt_index = ui->outputFmtbox->currentIndex();
    bool ret = false;

    QImage image0(ui->leftpath->text());
    QImage image1(ui->rightpath->text());
    if(image0.isNull() ||
       image1.isNull()){
        onMessageCB("[ERROR]Input image path parameters error.");
        ret = false;
        goto FAIL;
    }

    //turn off the UI
    //setIsWorking(true);

    //set interleaving mode
    inter_mode = Combine3DImage::INTERLEAVE_LINE;
    if(ui->pixelradio->isChecked()){
        inter_mode = Combine3DImage::INTERLEAVE_PIXEL_BY_PIXEL;
    }
    //check if we have this combiner.
    if(comb==0){
        onMessageCB(tr("[ERROR]not supported output format."));
        ret = false;
        goto FAIL;
    }

    //start processing
    if(fmt_index == Combine3DImage::FMT_3D_BGRA ||
       fmt_index==Combine3DImage::FMT_3D_RGBA){
        Combine3DImageBGRA* comb_alpha = (Combine3DImageBGRA*)comb;
        //set pre-alpha value
        comb_alpha->setEnablePreAlpha(ui->alphachk->isChecked());//set if use the user input alpha value
        float pre_alpha = (float)(ui->alphaslide->value())/100;//calculate the pre-alpha value.
        comb_alpha->setPreAlpha(pre_alpha);//set to the alpha combiner.
        if(comb_alpha->enableAlpha()){
            onMessageCB(tr("User set pre-alpha value set to %1").arg(pre_alpha));
        }else{
            onMessageCB(tr("The image's alpha channel value is used."));
        }
    }

    {
        int stride=ui->outStridetxt->text().toInt();
        int dstHeight = ui->outHeightlbl->text().toInt();
        ret = comb->generate3DImageBin(&image0,&image1,inter_mode,stride,dstHeight);
    }

FAIL:
    //setIsWorking(false);
    return ret;
}
bool MainWidget::generate2DImageBin(Combine3DImage* comb)
{
    int fmt_index = ui->outputFmtbox->currentIndex();
    bool ret = false;
    QImage image0(ui->leftpath->text().trimmed());
    if(image0.isNull()){
        onMessageCB(tr("[ERROR]Input image path parameters error."));
        ret = false;
        goto FAIL;
    }

    //turn off the UI
    //setIsWorking(true);

    //check if we have this combiner.
    if(comb==0){
        onMessageCB(tr("[ERROR]not supported output format."));
        ret = false;
        goto FAIL;
    }

    //start processing
    switch(fmt_index){
    case Combine3DImage::FMT_3D_BGRA:
    case Combine3DImage::FMT_3D_RGBA:
    case Combine3DImage::FMT_3D_RGBA1010102:
    {
            Combine3DImageBGRA* comb_alpha = (Combine3DImageBGRA*)comb;
            //set pre-alpha value
            comb_alpha->setEnablePreAlpha(ui->alphachk->isChecked());//set if use the user input alpha value
            float pre_alpha = (float)(ui->alphaslide->value())/100;//calculate the pre-alpha value.
            comb_alpha->setPreAlpha(pre_alpha);//set to the alpha combiner.
            if(comb_alpha->enableAlpha()){
               onMessageCB(tr("User set pre-alpha value set to %1").arg(pre_alpha));
            }else{
               onMessageCB(tr("The image's alpha channel value is used."));
            }
    }
        break;
    case Combine3DImage::FMT_3D_YUV422:
    {
        Combine3DImageYUV422 *comb_yuv422 = (Combine3DImageYUV422*)comb;
        //set layout format
        comb_yuv422->setIsPlanar(ui->yuvPlanarbox->isChecked());//set if we use planar format
        comb_yuv422->setYUV422Format((R3D_FMT_YUV422)ui->yuvFmtbox->currentIndex());//set the packed color format.

    }
        break;
    }

    {
        int stride=ui->outStridetxt->text().toInt();
        int dstHeight = ui->outHeightlbl->text().toInt();
        qDebug()<<tr("[%1,%2]stride=%3,dst_height=%4.").arg(__FILE__).arg(__LINE__).arg(stride).arg(dstHeight);
        ret = comb->generate2DImageBin(&image0,stride,dstHeight);
    }

FAIL:
    //setIsWorking(false);
    return ret;
}
void MainWidget::setPreAlphaVisible(bool b)
{
    ui->bgrabox->setVisible(b);

    //set if enable the UI;
    bool e = ui->alphachk->isChecked();
    ui->alphavallbl->setEnabled(e);
    ui->alphaslide->setEnabled(e);
}

void MainWidget::onOutStridechkStateChangedCB(int state)
{
    bool e=false;
    switch(state)
    {
    case Qt::Checked:
        e = true;
        break;
    case Qt::Unchecked:
        e = false;
        break;
    }
    ui->outStridetxt->setEnabled(e);
    ui->outStridelbl->setEnabled(e);
}

void MainWidget::onOutputColorFormatIndexChangedCB(int index)
{
    //calc the color setting components visible.
    setPreAlphaVisible(false);
    ui->yuvbox->setVisible(false);
    switch(index){
    case Combine3DImage::FMT_3D_BGRA:
    case Combine3DImage::FMT_3D_RGBA:
    case Combine3DImage::FMT_3D_RGBA1010102:
        setPreAlphaVisible(true);
        break;
    case Combine3DImage::FMT_3D_YUV422:
        ui->yuvbox->setVisible(true);
        break;
    }
}

void MainWidget::onAlphaChkStateChangedCB(int state)
{//if the chkbox is checked, enable the alpha slide
    bool e = false;
    switch(state)
    {
    case Qt::Checked:
        e = true;
        break;
    case Qt::Unchecked:
        e = false;
        break;
    }
    ui->alphavallbl->setEnabled(e);
    ui->alphaslide->setEnabled(e);
}
void MainWidget::onAlphaValueChangedCB(int value){ui->alphavallbl->setText(tr("%1%").arg(value));}
void MainWidget::onYuvLayoutFormatChangedCB(int state)
{
    bool e = ui->yuvPackedbox->isChecked();
    ui->yuvFmtbox->setEnabled(e);
}
QString MainWidget::openInputImageFile()
{
    QString file_path;
    //open the dialog
    m_browser->setAcceptMode(QFileDialog::AcceptOpen);
    m_browser->setFileMode(QFileDialog::ExistingFile);
    m_browser->exec();

    QStringList files = m_browser->selectedFiles();
    if(!files.size()){
        return QString();
    }
    //get the selected file.
    file_path = m_browser->selectedFiles().at(0);
#if 0
    QString fmt = file_path.toLower();
    if(! fmt.endsWith(FMT_BMP) &&
       ! fmt.endsWith(FMT_JPG) &&
       ! fmt.endsWith(FMT_JPG2))
    {
        return QString();
    }
#else
    QImage image(file_path);
    if(image.isNull()){
        return QString();
    }
#endif
    return file_path;
}
void MainWidget::onInputLeftBrowsebtnCB()
{
    QString file = openInputImageFile();
    if(!file.isEmpty()){
        ui->leftpath->setText(file);
    }else{
        onMessageCB("[ERROR]Fail to load the left image file.");
    }
}
void MainWidget::onInputRightBrowsebtnCB()
{
    QString file = openInputImageFile();
    if(!file.isEmpty()){
        ui->rightpath->setText(file);
    }else{
        onMessageCB("[ERROR]Fail to load the left image file.");
    }
}
void MainWidget::onOutputBrowsebtnCB()
{
    m_browser->setAcceptMode(QFileDialog::AcceptOpen);
    m_browser->setFileMode(QFileDialog::AnyFile);
    m_browser->exec();
    //get the value
    QString file_path = m_browser->selectedFiles().at(0);
    //parse the dir value
    QDir dir(file_path);
    dir.setFilter(QDir::NoDotAndDotDot);
    QStringList list = dir.entryList();
    if(!list.size()){
        ui->outpath->setText(file_path);
    }else{
        onMessageCB(tr("Invalid output file name."));
    }
}

void MainWidget::onResultBrowsebtnCB()
{
    m_browser->setAcceptMode(QFileDialog::AcceptOpen);
    m_browser->setFileMode(QFileDialog::AnyFile);
    m_browser->exec();
    //get the value
    QString file_path = m_browser->selectedFiles().at(0);
    //parse the dir value
    QDir dir(file_path);
    dir.setFilter(QDir::NoDotAndDotDot);
    QStringList list = dir.entryList();
    if(!list.size()){
        ui->imagepathtxt->setText(file_path);
    }else{
        onMessageCB(tr("Invalid output file name."));
    }
}
void MainWidget::updateOutputImageStride()
{
    int stride;
    int index = ui->outputFmtbox->currentIndex();
    int num = 1;
    QImage image(ui->leftpath->text());

    if(image.isNull())return;
    if(ui->work3dchk->isChecked() && ui->pixelradio->isChecked()) num = 2;

    float bpp = this->m_combine[index]->combineFMTBpp();
    stride = bpp*num*image.width();
    ui->outStridelbl->setText(tr("recommand: %1 x %2 x %3")
                              .arg(image.width())
                              .arg(bpp)
                              .arg(num));
    ui->outStridetxt->setText(tr("%1").arg(stride));
}
void MainWidget::onWorktypechkStateChangedCB(int)
{
    bool e=ui->work3dchk->isChecked();
    if(!e){//judge current work type.
        m_currentWorkType = WORK_2D;
        ui->leftlbl->setText("input image:");
    }else{
        m_currentWorkType = WORK_3D_COMBINE;
        ui->leftlbl->setText("left image:");
        ui->rightlbl->setText("right image:");
    }
    //set if the right input UI components are visible.
#if 0
    ui->rightlbl->setEnabled(e);
    ui->rightpath->setEnabled(e);
    ui->browsebtn2->setEnabled(e);
#else
    ui->rightlbl->setVisible(e);
    ui->rightpath->setVisible(e);
    ui->browsebtn2->setVisible(e);
#endif
    //set if the interleaving UI is displayed
    ui->Combinebox->setEnabled(e);
}

void MainWidget::onShowImagebtnClickedCB()
{
    QString path = ui->imagepathtxt->text();
    const char* fname = (const char*)path.toLatin1().data();
    printf("[%s,%d]str=%s.\n",__FILE__,__LINE__,fname);
    FILE * fsrc = fopen(fname,"rb+");
    if(fsrc==0){
        onMessageCB(tr("[ERROR]fail to open file %1").arg(path));
        return;
    }
    int len;
    unsigned char * showbuffer;
    unsigned char * buffer=0;
    unsigned char * tmpbuffer=0;
    int width = ui->imageWidthtxt->text().toInt();
    int height = ui->imageHeighttxt->text().toInt();
    int colorIndex = ui->imageFmtbox->currentIndex();
    Combine3DImage *comb = m_combine[colorIndex];
    if(width<=0 || height<=0){
        onMessageCB(tr("[ERROR]invalid input image size."));
        goto FAIL;
    }

    //calculate the file size.
    fseek(fsrc,0,SEEK_END);
    len = ftell(fsrc);
    fseek(fsrc,0,SEEK_SET);

    //malloc the buffer
    buffer = (unsigned char *)malloc(len);
    tmpbuffer = (unsigned char *)malloc(len);
    if(buffer==0 || tmpbuffer==0){
        onMessageCB("[ERROR]fail to malloc the buffer.");
        goto FAIL;
    }

    //load the file to the buffer;
    if(len == fread(buffer,1,len,fsrc)){
        m_showImage.setWindowTitle(tr("Image:%1 Size:%2,%3")
                                   .arg(path)
                                   .arg(width)
                                   .arg(height));
        int scale = 1;
        if(height>=768){scale = 2;}
        int x = this->x()+(this->width()-width/scale)/2;
        int y = this->y()+(this->height()-height/scale)/2;
        if(y<=0)y=10;
        m_showImage.setGeometry(x,y,width/scale,height/scale+20);

        if(colorIndex == Combine3DImage::FMT_3D_YUV422){
            Combine3DImageYUV422 *comb422 = (Combine3DImageYUV422*)comb;
            comb422->setIsPlanar(ui->browseYuv422Planarchk->isChecked());
            comb422->setYUV422Format((R3D_FMT_YUV422)ui->browseYUV422Fmtbox->currentIndex());
        }
        showbuffer = buffer;
        if(ui->imageBrowseTLBrdo->isChecked()){
            memset(tmpbuffer,0,len);
            showbuffer = tmpbuffer;
            comb->convertTilebasedToLinearBuffer(tmpbuffer,buffer,len,width,height);
            qDebug()<<tr("[%1,%2]Tile based memory converted to linear memory").arg(__FILE__).arg(__LINE__);
        }
        bool ret = m_showImage.showImage(showbuffer,len,
                                         width,height,
                                         comb);
        if(!ret){
            onMessageCB(tr("[ERROR]fail to display the input image."));
        }
    }


FAIL:
    fclose(fsrc);
    if(buffer)free(buffer);
    if(tmpbuffer)free(tmpbuffer);
}

void MainWidget::onImageFmtboxIndexChangedCB(int index)
{
    //init all special color group to false;
    ui->browseYUV422group->setVisible(false);
    //set selected special color format index to true.
    switch(index){
    case Combine3DImage::FMT_3D_YUV422:
        ui->browseYUV422group->setVisible(true);
        break;
    default:
        break;
    }
}

void MainWidget::onBrowseLayoutFormatChangedCB(int state)
{
    ui->browseYUV422Fmtbox->setEnabled(ui->browseYuv422Packedchk->isChecked());
}

void MainWidget::onMessageCB(QString message){
    //ui->textBrowser->append(message);
    m_messageBox->setText(message);
    m_messageBox->setVisible(true);

    const int w = m_messageBox->width();
    const int h = m_messageBox->height();
    int x = this->x()+(this->width()-w)/2;
    int y = this->y()+(this->height()-h)/2;
    m_messageBox->setGeometry(x,y,w,h);
}
