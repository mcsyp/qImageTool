#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QHash>

#include "combine3dimage.h"
#include "showimagewidget.h"

namespace Ui {
class MainWidget;
}
#define CONFIG_FILE "./qImage3DTool_config.txt"
#define CONFIG_SAVE 1
enum CONFIG_SAVE_ITEM
{
    CONFIG_APP_WIDTH=0,
    CONFIG_APP_HEIGHT=1,
    CONFIG_WORKTYPE=2,
    CONFIG_IMAGE_0,
    CONFIG_IMAGE_1,
    CONFIG_OUTIMAGE,
    CONFIG_INTERLEAVEMODE,
    CONFIG_OUTPUTCOLORFORMAT,
    CONFIG_BROWSE_IMAGEPATH,
    CONFIG_BROWSE_WIDTH,
    CONFIG_BROWSE_HEIGHT,
    CONFIG_BROWSE_COLORFORMAT,
    CONFIG_STRIDE_ENABLED,
    CONFIG_STRIDE_VALUE,
    CONFIG_MEMORY,
    CONFIG_BROWSE_MEMORY,
    CONFIG_NUM
};

class MainWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
protected slots:
    void onMessageCB(QString message);

    void onPreStepbtnClickedCB();
    void onNextStepbtnClickedCB();
    void onStackedCurretnChangedCB(int);

    void onWorktypechkStateChangedCB(int);
    void onInputLeftBrowsebtnCB();
    void onInputRightBrowsebtnCB();
    void onOutputBrowsebtnCB();
    void onResultBrowsebtnCB();

    void onShowImagebtnClickedCB();
    void onImageFmtboxIndexChangedCB(int index);
    void onBrowseLayoutFormatChangedCB(int state);

    void onOutputColorFormatIndexChangedCB(int index);
    void onYuvLayoutFormatChangedCB(int value);
    void onAlphaValueChangedCB(int value);
    void onAlphaChkStateChangedCB(int state);

    void onOutStridechkStateChangedCB(int state);
protected:
    void updateOutputImageStride();
    QString openInputImageFile();
    void setPreAlphaVisible(bool b);

    bool stackedCheckInputImages();
    bool stackedCheckPixelLayout();
    bool stackedCheckOutputColorFormat();
    bool exportImage();

    bool generate3DImageBin(Combine3DImage* comb);
    bool generate2DImageBin(Combine3DImage* comb);

    void setIsWorking(bool);

    //save and load config file when program ends and starts.
    void saveConfig();
    void loadConfig();
    void closeEvent(QCloseEvent *);
    void setOutputColorFormat(Combine3DImage::FMT_3D_COMBINE index);
    int  interleavingMode();
    void setInterLeavingMode(int mode);
private:
    Ui::MainWidget *ui;
    QFileDialog * m_browser;
    Combine3DImage * m_combine[Combine3DImage::FMT_3D_NUM];
    /*supported work type*/

    ShowImageWidget m_showImage;
    QMessageBox *m_messageBox;

public:
    enum WORK_TYPE{
        WORK_2D=0,
        WORK_3D_COMBINE=1
    };
    int m_currentWorkType;

    enum STACK_INTERFACE{
        STACK_INPUTIMAGE=0,
        STACK_PIXELLAYOUT=1,
        STACK_OUTPUTFORMAT=2,
        STACK_OUTPUTSTRIDE,
        STACK_NUM
    };
};

#endif // MAINWIDGET_H
