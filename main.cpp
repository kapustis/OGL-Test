#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    QSurfaceFormat format;
    format.setSamples(32);
    format.setDepthBufferSize(48);
    QSurfaceFormat::setDefaultFormat(format);
    Widget w;
    w.resize(1440,900);
    w.show();
    //w.showFullScreen();

    return a.exec();
}
