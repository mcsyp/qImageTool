#include <QApplication>
#include <QDesktopWidget>

#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDesktopWidget *w = QApplication::desktop();
    MainWidget tool;
    int sw = w->width();
    int sh = w->height();
    int x = (sw-tool.width())/2;
    int y = (sh-tool.height())/2;
    tool.setGeometry(x,y,tool.width(),tool.height());
    tool.show();
    
    return a.exec();
}
