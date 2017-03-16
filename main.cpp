#include "mainwindow.h"
#include "LMS_Singleton.h"
#include "libitem.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setUpLMSVectors(LMS_Singleton :: getMySystem());
    w.show();
    return a.exec();
}
