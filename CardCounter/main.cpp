/**
 * @brief Main class is responsible for starting the application and passing controller to mainwindow for connections
 *
 * @authors Noah Zaffos, Caleb Standfield, Ethan Perkins, Jas Sandhu, Nash Hawkins
 * @date 4/15/2025
 */

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
