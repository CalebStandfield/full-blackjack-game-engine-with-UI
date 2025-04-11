#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Controller* controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controller(controller)
{
    ui->setupUi(this);

    screens = new Screens(ui);

    setUpMainWindowConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpMainWindowConnect()
{
    // Blackjack game buttons
    connect(screens,
            &Screens::sendHitButtonPressed,
            controller,
            &Controller::onHit);
    connect(screens,
            &Screens::sendStandbuttonPressed,
            controller,
            &Controller::onStand);
    connect(screens,
            &Screens::sendDoubleButtonPressed,
            controller,
            &Controller::onDoubleDown);
    // connect(screens,
    //         &Screens::sendSplitButtonPressed,
    //         controller,
    //         &Controller::);

}
