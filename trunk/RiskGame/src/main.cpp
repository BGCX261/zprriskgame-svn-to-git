#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QTime midnight(0, 0, 0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}

