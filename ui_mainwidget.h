/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created: Wed Mar 13 16:52:26 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QSlider>
#include <QSpacerItem>
#include <QStackedWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_21;
    QLabel *pageTitlelbl;
    QSpacerItem *horizontalSpacer_16;
    QLabel *pageTitlelbl2;
    QStackedWidget *stackedWidget;
    QWidget *page_start;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QCheckBox *work2dchk;
    QCheckBox *work3dchk;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *leftlbl;
    QLineEdit *leftpath;
    QPushButton *browsebtn;
    QHBoxLayout *horizontalLayout_5;
    QLabel *rightlbl;
    QLineEdit *rightpath;
    QPushButton *browsebtn2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QLineEdit *outpath;
    QPushButton *browsebtn3;
    QSpacerItem *verticalSpacer_2;
    QWidget *page_format;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *memPixelgroup;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_12;
    QRadioButton *memLinearradio;
    QRadioButton *memTileBasedradio;
    QSpacerItem *horizontalSpacer_13;
    QGroupBox *Combinebox;
    QHBoxLayout *horizontalLayout_14;
    QLabel *interlbl;
    QRadioButton *lineradio;
    QRadioButton *pixelradio;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *verticalSpacer;
    QWidget *page;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_5;
    QComboBox *outputFmtbox;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *bgrabox;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_10;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_20;
    QCheckBox *alphachk;
    QSlider *alphaslide;
    QLabel *alphavallbl;
    QGroupBox *yuvbox;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_7;
    QComboBox *yuvFmtbox;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_9;
    QCheckBox *yuvPlanarbox;
    QCheckBox *yuvPackedbox;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *verticalSpacer_3;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_14;
    QLabel *outStridelbl;
    QSpacerItem *horizontalSpacer_17;
    QHBoxLayout *horizontalLayout_23;
    QCheckBox *outStridechk;
    QLineEdit *outStridetxt;
    QSpacerItem *horizontalSpacer_15;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_15;
    QLabel *outHeightlbl;
    QSpacerItem *horizontalSpacer_18;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *preStepbtn;
    QPushButton *nextStepbtn;
    QPushButton *exportbtn;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_4;
    QLineEdit *imagepathtxt;
    QPushButton *imageBrowsebtn;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label;
    QLineEdit *imageWidthtxt;
    QLabel *label_2;
    QLineEdit *imageHeighttxt;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QComboBox *imageFmtbox;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *browsePixelMemgroup;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_13;
    QRadioButton *imageBrowseLinrdo;
    QRadioButton *imageBrowseTLBrdo;
    QSpacerItem *horizontalSpacer_14;
    QGroupBox *browseYUV422group;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_10;
    QComboBox *browseYUV422Fmtbox;
    QSpacerItem *horizontalSpacer_11;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_11;
    QCheckBox *browseYuv422Planarchk;
    QCheckBox *browseYuv422Packedchk;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *showbtn;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
        MainWidget->resize(552, 362);
        horizontalLayout = new QHBoxLayout(MainWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(MainWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        pageTitlelbl = new QLabel(tab);
        pageTitlelbl->setObjectName(QString::fromUtf8("pageTitlelbl"));

        horizontalLayout_21->addWidget(pageTitlelbl);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_16);

        pageTitlelbl2 = new QLabel(tab);
        pageTitlelbl2->setObjectName(QString::fromUtf8("pageTitlelbl2"));
        pageTitlelbl2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_21->addWidget(pageTitlelbl2);


        verticalLayout->addLayout(horizontalLayout_21);

        stackedWidget = new QStackedWidget(tab);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setFrameShape(QFrame::NoFrame);
        stackedWidget->setFrameShadow(QFrame::Plain);
        page_start = new QWidget();
        page_start->setObjectName(QString::fromUtf8("page_start"));
        verticalLayout_8 = new QVBoxLayout(page_start);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_8 = new QLabel(page_start);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(70, 0));
        label_8->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_7->addWidget(label_8);

        work2dchk = new QCheckBox(page_start);
        work2dchk->setObjectName(QString::fromUtf8("work2dchk"));
        work2dchk->setChecked(true);
        work2dchk->setAutoExclusive(true);

        horizontalLayout_7->addWidget(work2dchk);

        work3dchk = new QCheckBox(page_start);
        work3dchk->setObjectName(QString::fromUtf8("work3dchk"));
        work3dchk->setAutoExclusive(true);

        horizontalLayout_7->addWidget(work3dchk);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);


        verticalLayout_8->addLayout(horizontalLayout_7);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        leftlbl = new QLabel(page_start);
        leftlbl->setObjectName(QString::fromUtf8("leftlbl"));
        leftlbl->setMinimumSize(QSize(70, 0));
        leftlbl->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_4->addWidget(leftlbl);

        leftpath = new QLineEdit(page_start);
        leftpath->setObjectName(QString::fromUtf8("leftpath"));

        horizontalLayout_4->addWidget(leftpath);

        browsebtn = new QPushButton(page_start);
        browsebtn->setObjectName(QString::fromUtf8("browsebtn"));

        horizontalLayout_4->addWidget(browsebtn);


        verticalLayout_8->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        rightlbl = new QLabel(page_start);
        rightlbl->setObjectName(QString::fromUtf8("rightlbl"));
        rightlbl->setMinimumSize(QSize(70, 0));
        rightlbl->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_5->addWidget(rightlbl);

        rightpath = new QLineEdit(page_start);
        rightpath->setObjectName(QString::fromUtf8("rightpath"));

        horizontalLayout_5->addWidget(rightpath);

        browsebtn2 = new QPushButton(page_start);
        browsebtn2->setObjectName(QString::fromUtf8("browsebtn2"));

        horizontalLayout_5->addWidget(browsebtn2);


        verticalLayout_8->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_3 = new QLabel(page_start);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(70, 0));
        label_3->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_6->addWidget(label_3);

        outpath = new QLineEdit(page_start);
        outpath->setObjectName(QString::fromUtf8("outpath"));

        horizontalLayout_6->addWidget(outpath);

        browsebtn3 = new QPushButton(page_start);
        browsebtn3->setObjectName(QString::fromUtf8("browsebtn3"));

        horizontalLayout_6->addWidget(browsebtn3);


        verticalLayout_8->addLayout(horizontalLayout_6);

        verticalSpacer_2 = new QSpacerItem(20, 102, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_2);

        stackedWidget->addWidget(page_start);
        page_format = new QWidget();
        page_format->setObjectName(QString::fromUtf8("page_format"));
        verticalLayout_6 = new QVBoxLayout(page_format);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        memPixelgroup = new QGroupBox(page_format);
        memPixelgroup->setObjectName(QString::fromUtf8("memPixelgroup"));
        horizontalLayout_18 = new QHBoxLayout(memPixelgroup);
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_12 = new QLabel(memPixelgroup);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMinimumSize(QSize(80, 0));
        label_12->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_18->addWidget(label_12);

        memLinearradio = new QRadioButton(memPixelgroup);
        memLinearradio->setObjectName(QString::fromUtf8("memLinearradio"));
        memLinearradio->setMinimumSize(QSize(70, 0));
        memLinearradio->setMaximumSize(QSize(70, 16777215));
        memLinearradio->setChecked(true);

        horizontalLayout_18->addWidget(memLinearradio);

        memTileBasedradio = new QRadioButton(memPixelgroup);
        memTileBasedradio->setObjectName(QString::fromUtf8("memTileBasedradio"));

        horizontalLayout_18->addWidget(memTileBasedradio);

        horizontalSpacer_13 = new QSpacerItem(225, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_13);


        verticalLayout_6->addWidget(memPixelgroup);

        Combinebox = new QGroupBox(page_format);
        Combinebox->setObjectName(QString::fromUtf8("Combinebox"));
        horizontalLayout_14 = new QHBoxLayout(Combinebox);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        interlbl = new QLabel(Combinebox);
        interlbl->setObjectName(QString::fromUtf8("interlbl"));
        interlbl->setMinimumSize(QSize(80, 0));
        interlbl->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_14->addWidget(interlbl);

        lineradio = new QRadioButton(Combinebox);
        lineradio->setObjectName(QString::fromUtf8("lineradio"));
        lineradio->setMinimumSize(QSize(70, 0));
        lineradio->setMaximumSize(QSize(70, 16777215));
        lineradio->setChecked(true);

        horizontalLayout_14->addWidget(lineradio);

        pixelradio = new QRadioButton(Combinebox);
        pixelradio->setObjectName(QString::fromUtf8("pixelradio"));

        horizontalLayout_14->addWidget(pixelradio);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_9);


        verticalLayout_6->addWidget(Combinebox);

        verticalSpacer = new QSpacerItem(20, 105, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);

        stackedWidget->addWidget(page_format);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout_9 = new QVBoxLayout(page);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_5 = new QLabel(page);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(70, 0));
        label_5->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_9->addWidget(label_5);

        outputFmtbox = new QComboBox(page);
        outputFmtbox->setObjectName(QString::fromUtf8("outputFmtbox"));
        outputFmtbox->setMinimumSize(QSize(120, 0));
        outputFmtbox->setLayoutDirection(Qt::LeftToRight);
        outputFmtbox->setAutoFillBackground(false);

        horizontalLayout_9->addWidget(outputFmtbox);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);


        verticalLayout_9->addLayout(horizontalLayout_9);

        bgrabox = new QGroupBox(page);
        bgrabox->setObjectName(QString::fromUtf8("bgrabox"));
        verticalLayout_5 = new QVBoxLayout(bgrabox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        checkBox = new QCheckBox(bgrabox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setChecked(true);
        checkBox->setAutoExclusive(true);

        horizontalLayout_10->addWidget(checkBox);

        horizontalSpacer_6 = new QSpacerItem(118, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_6);


        verticalLayout_5->addLayout(horizontalLayout_10);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        alphachk = new QCheckBox(bgrabox);
        alphachk->setObjectName(QString::fromUtf8("alphachk"));
        alphachk->setChecked(false);
        alphachk->setAutoExclusive(true);

        horizontalLayout_20->addWidget(alphachk);

        alphaslide = new QSlider(bgrabox);
        alphaslide->setObjectName(QString::fromUtf8("alphaslide"));
        alphaslide->setMinimumSize(QSize(150, 0));
        alphaslide->setMaximum(100);
        alphaslide->setValue(100);
        alphaslide->setOrientation(Qt::Horizontal);
        alphaslide->setTickInterval(1);

        horizontalLayout_20->addWidget(alphaslide);

        alphavallbl = new QLabel(bgrabox);
        alphavallbl->setObjectName(QString::fromUtf8("alphavallbl"));

        horizontalLayout_20->addWidget(alphavallbl);


        verticalLayout_5->addLayout(horizontalLayout_20);


        verticalLayout_9->addWidget(bgrabox);

        yuvbox = new QGroupBox(page);
        yuvbox->setObjectName(QString::fromUtf8("yuvbox"));
        verticalLayout_3 = new QVBoxLayout(yuvbox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_7 = new QLabel(yuvbox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(70, 0));
        label_7->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_11->addWidget(label_7);

        yuvFmtbox = new QComboBox(yuvbox);
        yuvFmtbox->setObjectName(QString::fromUtf8("yuvFmtbox"));

        horizontalLayout_11->addWidget(yuvFmtbox);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_8);


        verticalLayout_3->addLayout(horizontalLayout_11);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_9 = new QLabel(yuvbox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(70, 0));
        label_9->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_15->addWidget(label_9);

        yuvPlanarbox = new QCheckBox(yuvbox);
        yuvPlanarbox->setObjectName(QString::fromUtf8("yuvPlanarbox"));
        yuvPlanarbox->setChecked(true);
        yuvPlanarbox->setAutoExclusive(true);

        horizontalLayout_15->addWidget(yuvPlanarbox);

        yuvPackedbox = new QCheckBox(yuvbox);
        yuvPackedbox->setObjectName(QString::fromUtf8("yuvPackedbox"));
        yuvPackedbox->setAutoExclusive(true);

        horizontalLayout_15->addWidget(yuvPackedbox);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_10);


        verticalLayout_3->addLayout(horizontalLayout_15);


        verticalLayout_9->addWidget(yuvbox);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_3);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        verticalLayout_10 = new QVBoxLayout(page_2);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        label_14 = new QLabel(page_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_22->addWidget(label_14);

        outStridelbl = new QLabel(page_2);
        outStridelbl->setObjectName(QString::fromUtf8("outStridelbl"));

        horizontalLayout_22->addWidget(outStridelbl);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_17);


        verticalLayout_10->addLayout(horizontalLayout_22);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        outStridechk = new QCheckBox(page_2);
        outStridechk->setObjectName(QString::fromUtf8("outStridechk"));
        outStridechk->setChecked(false);

        horizontalLayout_23->addWidget(outStridechk);

        outStridetxt = new QLineEdit(page_2);
        outStridetxt->setObjectName(QString::fromUtf8("outStridetxt"));
        outStridetxt->setEnabled(false);
        outStridetxt->setMinimumSize(QSize(80, 0));
        outStridetxt->setMaximumSize(QSize(80, 16777215));
        outStridetxt->setAlignment(Qt::AlignCenter);

        horizontalLayout_23->addWidget(outStridetxt);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_23->addItem(horizontalSpacer_15);


        verticalLayout_10->addLayout(horizontalLayout_23);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        label_15 = new QLabel(page_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_24->addWidget(label_15);

        outHeightlbl = new QLabel(page_2);
        outHeightlbl->setObjectName(QString::fromUtf8("outHeightlbl"));

        horizontalLayout_24->addWidget(outHeightlbl);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_24->addItem(horizontalSpacer_18);


        verticalLayout_10->addLayout(horizontalLayout_24);

        verticalSpacer_5 = new QSpacerItem(20, 164, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer_5);

        stackedWidget->addWidget(page_2);

        verticalLayout->addWidget(stackedWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        preStepbtn = new QPushButton(tab);
        preStepbtn->setObjectName(QString::fromUtf8("preStepbtn"));

        horizontalLayout_2->addWidget(preStepbtn);

        nextStepbtn = new QPushButton(tab);
        nextStepbtn->setObjectName(QString::fromUtf8("nextStepbtn"));

        horizontalLayout_2->addWidget(nextStepbtn);

        exportbtn = new QPushButton(tab);
        exportbtn->setObjectName(QString::fromUtf8("exportbtn"));

        horizontalLayout_2->addWidget(exportbtn);


        verticalLayout->addLayout(horizontalLayout_2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_2 = new QVBoxLayout(tab_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFlat(true);
        groupBox->setCheckable(false);
        verticalLayout_7 = new QVBoxLayout(groupBox);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(40, 0));
        label_4->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_8->addWidget(label_4);

        imagepathtxt = new QLineEdit(groupBox);
        imagepathtxt->setObjectName(QString::fromUtf8("imagepathtxt"));

        horizontalLayout_8->addWidget(imagepathtxt);

        imageBrowsebtn = new QPushButton(groupBox);
        imageBrowsebtn->setObjectName(QString::fromUtf8("imageBrowsebtn"));

        horizontalLayout_8->addWidget(imageBrowsebtn);


        verticalLayout_7->addLayout(horizontalLayout_8);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(40, 0));
        label->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_12->addWidget(label);

        imageWidthtxt = new QLineEdit(groupBox);
        imageWidthtxt->setObjectName(QString::fromUtf8("imageWidthtxt"));
        imageWidthtxt->setMinimumSize(QSize(60, 0));
        imageWidthtxt->setMaximumSize(QSize(60, 16777215));
        imageWidthtxt->setAlignment(Qt::AlignCenter);

        horizontalLayout_12->addWidget(imageWidthtxt);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(40, 0));
        label_2->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_12->addWidget(label_2);

        imageHeighttxt = new QLineEdit(groupBox);
        imageHeighttxt->setObjectName(QString::fromUtf8("imageHeighttxt"));
        imageHeighttxt->setMinimumSize(QSize(60, 0));
        imageHeighttxt->setMaximumSize(QSize(60, 16777215));
        imageHeighttxt->setAlignment(Qt::AlignCenter);

        horizontalLayout_12->addWidget(imageHeighttxt);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_2);


        verticalLayout_7->addLayout(horizontalLayout_12);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(70, 0));
        label_6->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_3->addWidget(label_6);

        imageFmtbox = new QComboBox(groupBox);
        imageFmtbox->setObjectName(QString::fromUtf8("imageFmtbox"));
        imageFmtbox->setMinimumSize(QSize(120, 0));
        imageFmtbox->setLayoutDirection(Qt::LeftToRight);
        imageFmtbox->setAutoFillBackground(false);

        horizontalLayout_3->addWidget(imageFmtbox);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);


        verticalLayout_7->addLayout(horizontalLayout_3);

        browsePixelMemgroup = new QGroupBox(groupBox);
        browsePixelMemgroup->setObjectName(QString::fromUtf8("browsePixelMemgroup"));
        horizontalLayout_19 = new QHBoxLayout(browsePixelMemgroup);
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_13 = new QLabel(browsePixelMemgroup);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_19->addWidget(label_13);

        imageBrowseLinrdo = new QRadioButton(browsePixelMemgroup);
        imageBrowseLinrdo->setObjectName(QString::fromUtf8("imageBrowseLinrdo"));
        imageBrowseLinrdo->setChecked(true);

        horizontalLayout_19->addWidget(imageBrowseLinrdo);

        imageBrowseTLBrdo = new QRadioButton(browsePixelMemgroup);
        imageBrowseTLBrdo->setObjectName(QString::fromUtf8("imageBrowseTLBrdo"));

        horizontalLayout_19->addWidget(imageBrowseTLBrdo);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_14);


        verticalLayout_7->addWidget(browsePixelMemgroup);

        browseYUV422group = new QGroupBox(groupBox);
        browseYUV422group->setObjectName(QString::fromUtf8("browseYUV422group"));
        verticalLayout_4 = new QVBoxLayout(browseYUV422group);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_10 = new QLabel(browseYUV422group);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_16->addWidget(label_10);

        browseYUV422Fmtbox = new QComboBox(browseYUV422group);
        browseYUV422Fmtbox->setObjectName(QString::fromUtf8("browseYUV422Fmtbox"));

        horizontalLayout_16->addWidget(browseYUV422Fmtbox);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_11);


        verticalLayout_4->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_11 = new QLabel(browseYUV422group);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_17->addWidget(label_11);

        browseYuv422Planarchk = new QCheckBox(browseYUV422group);
        browseYuv422Planarchk->setObjectName(QString::fromUtf8("browseYuv422Planarchk"));
        browseYuv422Planarchk->setChecked(true);
        browseYuv422Planarchk->setAutoExclusive(true);

        horizontalLayout_17->addWidget(browseYuv422Planarchk);

        browseYuv422Packedchk = new QCheckBox(browseYUV422group);
        browseYuv422Packedchk->setObjectName(QString::fromUtf8("browseYuv422Packedchk"));
        browseYuv422Packedchk->setAutoExclusive(true);

        horizontalLayout_17->addWidget(browseYuv422Packedchk);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_12);


        verticalLayout_4->addLayout(horizontalLayout_17);


        verticalLayout_7->addWidget(browseYUV422group);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_4);


        verticalLayout_2->addWidget(groupBox);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_7);

        showbtn = new QPushButton(tab_2);
        showbtn->setObjectName(QString::fromUtf8("showbtn"));
        showbtn->setMinimumSize(QSize(100, 0));
        showbtn->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_13->addWidget(showbtn);


        verticalLayout_2->addLayout(horizontalLayout_13);

        tabWidget->addTab(tab_2, QString());

        horizontalLayout->addWidget(tabWidget);


        retranslateUi(MainWidget);

        tabWidget->setCurrentIndex(1);
        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QApplication::translate("MainWidget", "Image Tool", 0));
        pageTitlelbl->setText(QApplication::translate("MainWidget", "TextLabel", 0  ));
        pageTitlelbl2->setText(QApplication::translate("MainWidget", "TextLabel", 0  ));
        label_8->setText(QApplication::translate("MainWidget", "work type:", 0  ));
        work2dchk->setText(QApplication::translate("MainWidget", "2D image", 0  ));
        work3dchk->setText(QApplication::translate("MainWidget", "3D image combine", 0  ));
        leftlbl->setText(QApplication::translate("MainWidget", "input_0 path:", 0  ));
        browsebtn->setText(QApplication::translate("MainWidget", "browse", 0  ));
        rightlbl->setText(QApplication::translate("MainWidget", "input_1 path:", 0  ));
        browsebtn2->setText(QApplication::translate("MainWidget", "browse", 0  ));
        label_3->setText(QApplication::translate("MainWidget", "output path:", 0  ));
        browsebtn3->setText(QApplication::translate("MainWidget", "browse", 0  ));
        memPixelgroup->setTitle(QApplication::translate("MainWidget", "Pixel Layout Settings:", 0  ));
        label_12->setText(QApplication::translate("MainWidget", "memory layout:", 0  ));
        memLinearradio->setText(QApplication::translate("MainWidget", "linear", 0  ));
        memTileBasedradio->setText(QApplication::translate("MainWidget", "tile-based", 0  ));
        Combinebox->setTitle(QApplication::translate("MainWidget", "3D Combine Settings:", 0  ));
        interlbl->setText(QApplication::translate("MainWidget", "interleaving:", 0  ));
        lineradio->setText(QApplication::translate("MainWidget", "line", 0  ));
        pixelradio->setText(QApplication::translate("MainWidget", "pixel-by-pixel", 0  ));
        label_5->setText(QApplication::translate("MainWidget", "color format:", 0  ));
        outputFmtbox->clear();
        outputFmtbox->insertItems(0, QStringList()
         << QApplication::translate("MainWidget", "BGRX", 0)
         << QApplication::translate("MainWidget", "BGRA", 0  )
         << QApplication::translate("MainWidget", "RGBA", 0  )
         << QApplication::translate("MainWidget", "RGBX", 0  )
         << QApplication::translate("MainWidget", "NV12", 0  )
        );
        bgrabox->setTitle(QApplication::translate("MainWidget", "32bit Picture Alpha Settings:", 0  ));
        checkBox->setText(QApplication::translate("MainWidget", "use picture's alpha channel", 0  ));
        alphachk->setText(QApplication::translate("MainWidget", "input  pre-alpha:", 0  ));
        alphavallbl->setText(QApplication::translate("MainWidget", "100%", 0  ));
        yuvbox->setTitle(QApplication::translate("MainWidget", "YUV422 Settings:", 0  ));
        label_7->setText(QApplication::translate("MainWidget", "color format:", 0  ));
        label_9->setText(QApplication::translate("MainWidget", "pixel layouts:", 0  ));
        yuvPlanarbox->setText(QApplication::translate("MainWidget", "planar", 0  ));
        yuvPackedbox->setText(QApplication::translate("MainWidget", "packed", 0  ));
        label_14->setText(QApplication::translate("MainWidget", "Recommand stride value:", 0  ));
        outStridelbl->setText(QString());
        outStridechk->setText(QApplication::translate("MainWidget", "Custom stride value:", 0  ));
        outStridetxt->setText(QApplication::translate("MainWidget", "0", 0  ));
        label_15->setText(QApplication::translate("MainWidget", "Recommand height value:", 0  ));
        outHeightlbl->setText(QApplication::translate("MainWidget", "TextLabel", 0  ));
        preStepbtn->setText(QApplication::translate("MainWidget", "Previous", 0  ));
        nextStepbtn->setText(QApplication::translate("MainWidget", "Next", 0  ));
        exportbtn->setText(QApplication::translate("MainWidget", "Export", 0  ));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWidget", "Image Generater", 0  ));
        groupBox->setTitle(QApplication::translate("MainWidget", "Image Review:", 0  ));
        label_4->setText(QApplication::translate("MainWidget", "path:", 0  ));
        imageBrowsebtn->setText(QApplication::translate("MainWidget", "browse", 0  ));
        label->setText(QApplication::translate("MainWidget", "width:", 0  ));
        imageWidthtxt->setText(QApplication::translate("MainWidget", "640", 0  ));
        label_2->setText(QApplication::translate("MainWidget", "height:", 0  ));
        imageHeighttxt->setText(QApplication::translate("MainWidget", "480", 0  ));
        label_6->setText(QApplication::translate("MainWidget", "color format:", 0  ));
        imageFmtbox->clear();
        imageFmtbox->insertItems(0, QStringList()
         << QApplication::translate("MainWidget", "BGRX", 0  )
         << QApplication::translate("MainWidget", "BGRA", 0  )
         << QApplication::translate("MainWidget", "RGBA", 0  )
         << QApplication::translate("MainWidget", "RGBX", 0  )
         << QApplication::translate("MainWidget", "NV12", 0  )
        );
        browsePixelMemgroup->setTitle(QApplication::translate("MainWidget", "pixel settings:", 0  ));
        label_13->setText(QApplication::translate("MainWidget", "memory layout:", 0  ));
        imageBrowseLinrdo->setText(QApplication::translate("MainWidget", "linear", 0  ));
        imageBrowseTLBrdo->setText(QApplication::translate("MainWidget", "tile-based", 0  ));
        browseYUV422group->setTitle(QApplication::translate("MainWidget", "YUV422 Settings:", 0  ));
        label_10->setText(QApplication::translate("MainWidget", "color format:", 0  ));
        label_11->setText(QApplication::translate("MainWidget", "pixel layouts:", 0  ));
        browseYuv422Planarchk->setText(QApplication::translate("MainWidget", "planar", 0  ));
        browseYuv422Packedchk->setText(QApplication::translate("MainWidget", "packed", 0  ));
        showbtn->setText(QApplication::translate("MainWidget", "show", 0  ));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWidget", "Image Browser", 0  ));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
