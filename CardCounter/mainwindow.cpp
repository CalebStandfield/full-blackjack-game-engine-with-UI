#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Controller* c, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Set up function calls

    screens = new Screens(ui);
}

MainWindow::~MainWindow()
{
    delete ui;
}
