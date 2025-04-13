#include "screens.h"
#include <QPalette>
#include <QPixmap>
#include <qdebug.h>
#include <QGraphicsDropShadowEffect>
#include <QRandomGenerator>
#include <QTimer>

Screens::Screens(Ui::MainWindow *ui, QWidget *parent)
    : QStackedWidget(parent), ui(ui)
{
    // Ensure the start Screen in displayed
    moveToStartScreen();

    // Set up function calls
    setUpTable();
    setUpQStyleSheets();
    setUpStartMenuButtons();
    setUpGamePlayButtons();
    setUpSettingsPopup();
    setUpBackGround();
    hideSettingsPopup();
    setUpBasicStrategyCharts();
    setUpBettingMenu();

    // Connects
    setUpScreenConnect();
    tableViewCardTest();
}

void Screens::setUpScreenConnect()
{
    // Gameplay buttons
    connect(ui->blackjackPlayButton,
            &QPushButton::clicked,
            this,
            &Screens::moveToPlayScreen);
    connect(ui->countCardsPlayButton,
            &QPushButton::clicked,
            this,
            &Screens::moveToPlayScreen);
    connect(ui->blackjackTutorialButton,
            &QPushButton::clicked,
            this,
            &Screens::moveToPlayScreen);

    // Settings buttons
    connect(ui->acceptSettingsButton,
            &QPushButton::clicked,
            this,
            &Screens::hideSettingsPopup);
    connect(ui->acceptSettingsButton,
            &QPushButton::clicked,
            this,
            &Screens::acceptSettingsButtonPressed);
    connect(ui->cancelSettingsButton,
            &QPushButton::clicked,
            this,
            &Screens::moveToStartScreen);

    //Tutorial Pages
    connect(ui->basicStrategyChartButton,
            &QPushButton::clicked,
            this,
            &Screens::moveToInforScreen);
    connect(ui->infoMenuButton,
            &QPushButton::clicked,
            this,
            &Screens::moveToStartScreen);

    // Gameplay Buttons
    connect(ui->hitButton,
            &QPushButton::clicked,
            this,
            &Screens::hitButtonOnPress);

    // Betting Buttons
    connect(ui->placeBetButton,
            &QPushButton::clicked,
            this,
            &Screens::placedBetButtonOnPress);


}

void Screens::setUpTable()
{
    tableView = new TableView(ui->table);
    if (!ui->table->layout()) {
        ui->table->setLayout(new QVBoxLayout());
    }
    ui->table->setStyleSheet(QWidgetStyle);

    ui->table->layout()->addWidget(tableView);

}

void Screens::setUpStartMenuButtons()
{
    // Button Area
    ui->startMenuButtonArea->setStyleSheet(QWidgetStyle);

    // TitleCard
    ui->startMenuTitleCard->setStyleSheet(QLabelStyle);
    ui->startMenuTitleCard->setAlignment(Qt::AlignCenter);
    ui->startMenuTitleCard->setText("Blackjack \nCardCounting");

    // Buttons
    ui->blackjackPlayButton->setStyleSheet(QPushButtonStyle);
    ui->basicStrategyChartButton->setStyleSheet(QPushButtonStyle);
    ui->countCardsPlayButton->setStyleSheet(QPushButtonStyle);
    ui->blackjackTutorialButton->setStyleSheet(QPushButtonStyle);

}

void Screens::setUpSettingsPopup()
{
    ui->settingsPopUp->setStyleSheet(QWidgetStyle);
    applyShadowToWidget(ui->settingsPopUp);
    ui->acceptSettingsButton->setStyleSheet(QPushButtonStyle);
    ui->cancelSettingsButton->setStyleSheet(QPushButtonStyle);
}

void Screens::setUpGamePlayButtons()
{
    // Buttons Area
    ui->gamePlayButtons->setStyleSheet(QWidgetStyle);

    // Buttons
    ui->hitButton->setStyleSheet(QPushButtonStyle);
    ui->standButton->setStyleSheet(QPushButtonStyle);
    ui->doubleButton->setStyleSheet(QPushButtonStyle);
    ui->splitButton->setStyleSheet(QPushButtonStyle);
}

void Screens::setUpBettingMenu()
{
    ui->bettingArea->setStyleSheet(QWidgetStyle);
    ui->betSlider->setStyleSheet(QSliderStyle);
    ui->betLabel->setStyleSheet(QBetLabelStyle);
    ui->allInButton->setStyleSheet(QPushButtonStyle);
    ui->halfButton->setStyleSheet(QPushButtonStyle);
    ui->minimumBettingButton->setStyleSheet(QPushButtonStyle);
    ui->placeBetButton->setStyleSheet(QPushButtonStyle);
    connect(ui->betSlider, &QSlider::valueChanged, this, &Screens::updateBetLabelText);
}

void Screens::updateBetLabelText(int value)
{
    ui->betLabel->setText("Bet Amount: $" + QString::number(value));
}

void Screens::setUpQStyleSheets()
{
    QPushButtonStyle =
        "QPushButton {"
        "    background-color: #404040;"
        "    color: white;"
        "    border: 2px solid #444444;"
        "    border-radius: 5px;"
        "    padding: 10px 20px;"
        "    font-size: 24px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #505050;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #646464;"
        "}";

    QSliderStyle =
        "QSlider {"
        "    background: transparent;"
        "    height: 12px;"
        "}"
        "QSlider::groove:horizontal {"
        "    background: rgba(80, 80, 80, 180);"
        "    border: 1px solid rgba(255, 255, 255, 20);"
        "    height: 6px;"
        "    border-radius: 3px;"
        "}"
        "QSlider::handle:horizontal {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #aaaaaa, stop:1 #dddddd);"
        "    border: 1px solid #444;"
        "    width: 14px;"
        "    height: 14px;"
        "    margin: -4px 0;"
        "    border-radius: 7px;"
        "}"
        "QSlider::handle:horizontal:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #cccccc, stop:1 #eeeeee);"
        "    border: 1px solid #666;"
        "}"
        "QSlider::sub-page:horizontal {"
        "    background: rgba(160, 160, 160, 150);"
        "    border-radius: 3px;"
        "}"
        "QSlider::add-page:horizontal {"
        "    background: rgba(60, 60, 60, 100);"
        "    border-radius: 3px;"
        "}";

    QLabelStyle =
        "QLabel {"
        "    color: white;"
        "    font-size: 32px;"
        "    font-weight: bold;"
        "    padding: 5px;"
        "}";

    QBetLabelStyle =
        "QLabel {"
        "    color: white;"
        "    font-size: 15px;"
        "    font-weight: bold;"
        "    padding: 5px;"
        "}";

    QWidgetStyle =
        "QWidget {"
        "    background-color: rgba(50, 50, 50, 225);"
        "    border-radius: 15px;"
        "    border: 1px solid rgba(255, 255, 255, 30);"
        "    padding: 10px;"
        "    color: white;"
        "    font-size: 14px;"
        "}"
        "QScrollBar:vertical, QScrollBar:horizontal {"
        "    height: 0px;"
        "    width: 0px;"
        "    background: transparent;"
        "}";

    QTextBrowserStyle =
        "QTextBrowser {"
        "    background-color: #404040;"
        "    border-radius: 15px;"
        "    color: white;"
        "}";

    QGraphicsViewStyle =
        "QGraphicsView {"
        "    background-color: #404040;"
        "}";
}

void Screens::setUpBackGround()
{
    QPixmap bgImage(":/table/BlackJackTableMat.png");

    bgImage = bgImage.scaled(ui->centralwidget->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(bgImage));
    ui->centralwidget->setPalette(palette);
    ui->centralwidget->setAutoFillBackground(true);
}

void Screens::moveToStartScreen()
{
    ui->screens->setCurrentIndex(0);
    hideSettingsPopup();
    mode = UNSELECTED;
}

void Screens::moveToPlayScreen()
{
    ui->screens->setCurrentIndex(1);
    showSettingsPopup();
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    QString name = button->objectName();

    if (name == "blackjackPlayButton") {
        mode = GAMEPLAYMODE::BLACKJACK;
    } else if (name == "blackjackTutorialButton") {
        mode = GAMEPLAYMODE::BLACKJACKTUTORIAL;
    } else if (name == "countCardsPlayButton") {
        mode = GAMEPLAYMODE::COUNTCARDS;
    } else {
        mode = GAMEPLAYMODE::UNSELECTED;
    }
}

void Screens::hideSettingsPopup()
{
    ui->settingsPopUp->hide();
}

void Screens::showSettingsPopup()
{
    ui->settingsPopUp->show();
}

void Screens::applyShadowToWidget(QWidget *widget)
{
    // Create a shadow effect
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();

    // Set how the shadow looks
    shadow->setBlurRadius(15);
    shadow->setOffset(5, 5);
    shadow->setColor(QColor(0, 0, 0, 160));

    widget->setGraphicsEffect(shadow);
}

void Screens::moveToInforScreen()
{
    ui->screens->setCurrentIndex(2);
}

void Screens::setUpBasicStrategyCharts()
{
    // Set up the basic strategy charts
    QPixmap originalPixmap(":/BasicStrategyCharts.png");
    QGraphicsPixmapItem *imageItem = new QGraphicsPixmapItem(originalPixmap);
    imageItem->setScale(0.48);
    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->addItem(imageItem);
    scene->setSceneRect(imageItem->sceneBoundingRect());
    ui->basicStrategyChart->setScene(scene);
    ui->basicStrategyChart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->basicStrategyChart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->basicStrategyChart->setStyleSheet(QGraphicsViewStyle);

    //Set up for the textBrowser
    ui->infoTextBrowser->setStyleSheet(QTextBrowserStyle);
}

void Screens::tableViewCardTest()
{

    // TEST FUNCTION

}

void Screens::hitButtonOnPress()
{
    emit sendHitButtonPressed();
}

void Screens::standButtonOnPress()
{
    emit sendStandbuttonPressed();
}

void Screens::doubleButtonOnPress()
{
    emit sendDoubleButtonPressed();
}

void Screens::splitButtonOnPress()
{
    emit sendSplitButtonPressed();
}

void Screens::placedBetButtonOnPress()
{
    currentBet = 1; // DELETE LATER
    emit sendOnBet(currentBet);
}

void Screens::acceptSettingsButtonPressed()
{
    // TODO

    // FAKE NUMBERS DELETE NUMBER
    playerCount = 5;
    deckCount = 1;
    initialMoney = 1000;

    playerIndex = QRandomGenerator::global()->bounded(playerCount);

    for (unsigned int i = 0; i < playerCount; i++) {
        players.emplace_back(initialMoney, 1, i == playerIndex);
    }

    // Get settings
    // Reenable gameplay buttons

    emit sendSettingsAccepted(players, deckCount);
    // timer between start and bet/anims
    emit sendGameSetupCompleteStartBetting();
}

void Screens::dealCard(int seatIndex, QString imagePath)
{
    QString cardPNG = imagePath;
    if (seatIndex == 0)
    {
        tableView->addCardAnimated(cardPNG, QPointF(555, 50), QPointF(955, 250), -20); // far right
    }
    else if (seatIndex == 1)
    {
        tableView->addCardAnimated(cardPNG, QPointF(555, 50), QPointF(755, 330), -10); // middle right
    }
    else if (seatIndex == 2)
    {
        tableView->addCardAnimated(cardPNG, QPointF(555, 50), QPointF(555, 400), 0); // middle
    }
    else if (seatIndex == 3)
    {
        tableView->addCardAnimated(cardPNG, QPointF(555, 50), QPointF(355, 330), 10); // middle left
    }
    else if (seatIndex == 4)
    {
        tableView->addCardAnimated(cardPNG, QPointF(555, 50), QPointF(155, 250), 20); // far left
    }

}

void Screens::playerUpdated(int playerIndex, const Hand& hand, int total, int money, PLAYERSTATUS status)
{
    if (hand.getCards().size() == 0)
    {
        tableView->clearTable();
    }
    else if (hand.getCards().size() == 1)
    {
        // do split logic
    }
    else if (hand.getCards().size() >= 2)
    {
        int prevHandSize = players[playerIndex].hand.getCards().size();

        bool firstLoop = true;
        for (int i = prevHandSize + 1; i < hand.getCards().size(); i++)
        {
            if (firstLoop)
            {
                dealCard(playerIndex, hand.getCards()[i].getImagePath());
                firstLoop = false;
                continue;
            }
            QTimer::singleShot(3000, this, [=]() {
                dealCard(playerIndex, hand.getCards()[i].getImagePath());
            });

        }
    }

}

void Screens::dealerUpdated(const Hand& hand, int total)
{
    //TODO
    //Dealer hand updated visually
}

void Screens::currentPlayerTurn(int nextPlayerIndex)
{
    //TODO
    //Change POV to player at received index
}

void Screens::endBetting()
{
    //TODO
    //Deactivate betting
    //Reactivate hit/stand/double/split
}


