#include "mainwindow.h"
#include "controller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller c;
    MainWindow w(&c);
    w.show();
    return a.exec();
}
