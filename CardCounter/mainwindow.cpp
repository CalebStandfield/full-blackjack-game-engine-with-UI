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
            &Screens::sendStandButtonPressed,
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

    // Settings
    connect(screens,
            &Screens::sendSettingsAccepted,
            controller,
            &Controller::createNewGame);

    // Setup complete
    connect(screens,
            &Screens::sendGameSetupCompleteStartBetting,
            controller,
            &Controller::startBetting);


    // Betting
    connect(screens,
            &Screens::sendOnBet,
            controller,
            &Controller::onBet);

    // Next round
    connect(screens,
            &Screens::sendNewRound,
            controller,
            &Controller::startBetting);


    // Controller -> Screens

    // Updating Hands
    connect(controller,
            &Controller::playerUpdated,
            screens,
            &Screens::playerUpdated);
    connect(controller,
            &Controller::dealerUpdated,
            screens,
            &Screens::dealerUpdated);
    connect(controller,
            &Controller::showDealerCard,
            screens,
            &Screens::updateShowDealerCardBool);
    connect(controller,
            &Controller::updateAllPlayers,
            screens,
            &Screens::allPlayersUpdated);

    // POV updater
    connect(controller,
            &Controller::currentPlayerTurn,
            screens,
            &Screens::currentPlayerTurn);

    // Phase changing
    connect(controller,
            &Controller::endBetting,
            screens,
            &Screens::endBetting);
}
