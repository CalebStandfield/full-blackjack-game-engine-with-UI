#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Controller* controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controller(controller)
{
    ui->setupUi(this);

    screens = new Screens(ui);

    m_scene = new box2dPhysicsScene(this);

    ui->coinAnimView_2->setStyleSheet("background: transparent");
    ui->coinAnimView_2->setScene(m_scene);

    // Disable scrolling and anchor the view
    ui->coinAnimView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->coinAnimView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->coinAnimView_2->setRenderHint(QPainter::Antialiasing);

    ui->coinAnimView_2->setSceneRect(m_scene->sceneRect());
    ui->coinAnimView_2->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatioByExpanding);

    // ui->coinAnimView->setStyleSheet("background: transparent");
    // ui->coinAnimView->setScene(m_scene);

    // // Disable scrolling and anchor the view
    // ui->coinAnimView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // ui->coinAnimView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // ui->coinAnimView->setRenderHint(QPainter::Antialiasing);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, m_scene, &box2dPhysicsScene::advance);
    timer->start(1000 / 60);

    setUpMainWindowConnects();
}

MainWindow::~MainWindow()
{
    delete ui;
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
    connect(controller,
            &Controller::endRound,
            screens,
            &Screens::endRound);
}
