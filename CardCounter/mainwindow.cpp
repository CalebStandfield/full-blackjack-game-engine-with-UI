#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Controller* controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controller(controller)
{
    ui->setupUi(this);

    infoBar = new PlayerInfoView(ui);
    screens = new Screens(ui);

    setUpMainWindowConnects();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete screens;
    delete infoBar;
}

void MainWindow::setUpMainWindowConnects()
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
    connect(screens,
            &Screens::sendSplitButtonPressed,
            controller,
            &Controller::onSplit);

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

    // Round starting
    connect(screens,
            &Screens::dealAnimationComplete,
            controller,
            &Controller::onDealingAnimationComplete);

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

    // Leave game
    connect(screens,
            &Screens::sendStopEverything,
            controller,
            &Controller::onStopEverything);
    connect(screens,
            &Screens::sendStopEverything,
            infoBar,
            &PlayerInfoView::onStopEverything);


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
    connect(controller,
            &Controller::splitPlayers,
            screens,
            &Screens::onsplitPlayers);

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
    connect(controller,
            &Controller::endRound,
            screens,
            &Screens::endRound);
    connect(controller,
            &Controller::gameOver,
            screens,
            &Screens::onGameOver);

    // Controller -> PlayerInfoView
    connect(screens,
            &Screens::sendSettingsAccepted,
            infoBar,
            &PlayerInfoView::onSettingsAccepted);
    connect(controller,
            &Controller::playerUpdated,
            infoBar,
            &PlayerInfoView::onPlayerUpdated);
    connect(controller,
            &Controller::updateAllPlayers,
            infoBar,
            &PlayerInfoView::onUpdateAllPlayers);
    connect(controller,
            &Controller::splitPlayers,
            infoBar,
            &PlayerInfoView::onSplitPlayers);
    connect(controller,
            &Controller::currentPlayerTurn,
            infoBar,
            &PlayerInfoView::onCurrentPlayerTurn);

}
