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
    setUpScreenConnects();
    tableViewCardTest();
}

void Screens::setUpScreenConnects()
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
    connect(ui->playerCountSettingsSlider,
            &QSlider::valueChanged,
            this,
            &Screens::updateSettingsSlider);
    connect(ui->deckCountSettingsSlider,
            &QSlider::valueChanged,
            this,
            &Screens::updateSettingsSlider);
    connect(ui->chipCountSettingsLineEdit,
            &QLineEdit::textChanged,
            this,
            &Screens::onEditChipCountLineEdit);

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
            &Screens::onPressHitButton);
    connect(ui->standButton,
            &QPushButton::clicked,
            this,
            &Screens::onPressStandButton);
    connect(ui->doubleButton,
            &QPushButton::clicked,
            this,
            &Screens::onPressDoubleButton);

    // Betting Buttons
    connect(ui->placeBetButton,
            &QPushButton::clicked,
            this,
            &Screens::onPressPlacedBetButton);
    connect(ui->betSlider,
            &QSlider::valueChanged,
            this,
            &Screens::updateBetLabelText);
    connect(ui->minimumBettingButton,
            &QPushButton::clicked,
            this,
            &Screens::onPressBettingAmountButtons);
    connect(ui->halfButton,
            &QPushButton::clicked,
            this,
            &Screens::onPressBettingAmountButtons);
    connect(ui->allInButton,
            &QPushButton::clicked,
            this,
            &Screens::onPressBettingAmountButtons);

    // Continue or leave
    connect(ui->backToMainMenuFromPlay,
            &QPushButton::clicked,
            this,
            [this] () {ui->screens->setCurrentIndex(0);});
    connect(ui->nextRound,
            &QPushButton::clicked,
            this,
            &Screens::onPressNextRound);
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

    // Make font smaller for text boxes
    QString tempQLabelStyle =
        "QLabel {"
        "    color: white;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    padding: 5px;"
        "}";

    // Labels
    ui->settingsMenuTitle->setStyleSheet(QLabelStyle);

    ui->playerCountTextSettingsLabel->setStyleSheet(tempQLabelStyle);

    ui->deckCountTextSettingsLabel->setStyleSheet(tempQLabelStyle);

    ui->chipCountTextSettingsLabel->setStyleSheet(tempQLabelStyle);

    // Sliders
    ui->playerCountSettingsSlider->setStyleSheet(QSliderStyle);

    ui->deckCountSettingsSlider->setStyleSheet(QSliderStyle);

    toggleEnabledQPushButton(ui->acceptSettingsButton, false);
    ui->cancelSettingsButton->setStyleSheet(QPushButtonStyle);

    // LineEdit
    ui->chipCountSettingsLineEdit->setPlaceholderText("Chip count: (minimum $1)");
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
    toggleEnabledQPushButton(ui->placeBetButton, false);
}

void Screens::updateBetLabelText(unsigned int value)
{
    toggleEnabledQPushButton(ui->placeBetButton, true);
    ui->betLabel->setText("Bet Amount: $" + QString::number(value));
}

void Screens::updateSettingsSlider(unsigned int value)
{
    QSlider *slider = qobject_cast<QSlider *>(sender());

    QString name = slider->objectName();

    if (name == "playerCountSettingsSlider")
    {
        ui->playerCountTextSettingsLabel->setText("Player Count: " + QString::number(value));
        playerCount =  value;
    }
    else if (name == "deckCountSettingsSlider")
    {
        ui->deckCountTextSettingsLabel->setText("Deck Count: " + QString::number(value));
        playerCount = value;
    }

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

    QPushButtonDisabledStyle =
        "QPushButton:disabled {"
        "    background-color: #2a2a2a;"
        "    color: #888888;"
        "    border: 2px solid #333333;"
        "    border-radius: 5px;"
        "    padding: 10px 20px;"
        "    font-size: 24px;"
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
        "    background-color: transparent;"
        "    border: none;"
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

    ui->screens->setStyleSheet(QStackedWidgetStyle);
}

void Screens::moveToStartScreen()
{
    ui->screens->setCurrentIndex(0);
    hideSettingsPopup();
    mode = UNSELECTED;
}

void Screens::moveToPlayScreen()
{
    toggleEnabledGamePlayButtons(false);
    ui->screens->setCurrentIndex(1);
    ui->bettingArea->hide();
    showSettingsPopup();
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    QString name = button->objectName();

    if (name == "blackjackPlayButton")
    {
        mode = GAMEPLAYMODE::BLACKJACK;
    }
    else if (name == "blackjackTutorialButton")
    {
        mode = GAMEPLAYMODE::BLACKJACKTUTORIAL;
    }
    else if (name == "countCardsPlayButton")
    {
        mode = GAMEPLAYMODE::COUNTCARDS;
    }
    else
    {
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

void Screens::onPressHitButton()
{
    emit sendHitButtonPressed();
}

void Screens::onPressStandButton()
{
    emit sendStandButtonPressed();
}

void Screens::onPressDoubleButton()
{
    emit sendDoubleButtonPressed();
}

void Screens::onPressSplitButton()
{
    emit sendSplitButtonPressed();
}

void Screens::onPressPlacedBetButton()
{
    ui->bettingArea->hide();
    emit sendOnBet(currentBet);
}

void Screens::onPressBettingAmountButtons()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    QString name = button->objectName();

    if (name == "allInButton")
    {
        currentBet = players[userIndex].money;
    }
    else if (name == "halfButton") {
        currentBet = players[userIndex].money / 2;
    }
    else
    {
        // Called when the minimum button is pressed
        currentBet = 1;
    }
    ui->betSlider->setValue(currentBet);
    updateBetLabelText(currentBet);
}

void Screens::onEditChipCountLineEdit()
{
    QString input = ui->chipCountSettingsLineEdit->text();

    bool ok;
    int value = input.toInt(&ok);

    if (!ok || value < 1) {
        value = 1;
    } else if (value > 1000000) {
        value = 1000000;
    }

    if (input.isEmpty())
    {
        toggleEnabledQPushButton(ui->acceptSettingsButton, false);
        return;
    }

    // Set the clamped value back into the line edit
    ui->chipCountSettingsLineEdit->setText(QString::number(value));
    initialMoney = value;
    toggleEnabledQPushButton(ui->acceptSettingsButton, true);
}

void Screens::acceptSettingsButtonPressed()
{
    ui->bettingArea->show();
    ui->betSlider->setMaximum(initialMoney);

    //playerIndex = QRandomGenerator::global()->bounded(playerCount);
    userIndex = 0;

    for (unsigned int i = 0; i < playerCount; i++) {
        players.emplace_back(initialMoney, 1, i == userIndex);
    }

    tableView->createPlayerCardContainers(playerCount);

    emit sendSettingsAccepted(players, deckCount, 0);
    // timer between start and bet/anims
    emit sendGameSetupCompleteStartBetting();

    toggleEnabledGamePlayButtons(false);

    tableView->createDealerPile();
}

void Screens::dealCard(int seatIndex, QString imagePath)
{
    QString cardPNG = imagePath;
    QPointF startPos(500, 49);
    QPointF endPos;
    qreal rotation = 0;

    switch (seatIndex) {
    case 0:
        endPos = QPointF(955, 250); // far right
        rotation = -20;
        break;
    case 1:
        endPos = QPointF(755, 330); // middle right
        rotation = -10;
        break;
    case 2:
        endPos = QPointF(555, 400); // middle
        rotation = 0;
        break;
    case 3:
        endPos = QPointF(355, 330); // middle left
        rotation = 10;
        break;
    case 4:
        endPos = QPointF(155, 250); // far left
        rotation = 20;
        break;
    default:
        endPos = QPointF(555, 50);
        rotation = 0;
        break;
    }

    tableView->addCardAnimated(seatIndex, cardPNG, startPos, endPos, rotation);
}

void Screens::playerUpdated(int playerIndex, const Hand& hand, int total, int money, PLAYERSTATUS status)
{
    if (hand.getCards().size() == 0)
    {
        return;
    }
    else if (hand.getCards().size() == 1)
    {
        // do split logic
    }
    else
    {
        int prevHandSize = players[playerIndex].hand.getCards().size();

        bool firstLoop = true;
        for (int i = prevHandSize; i < static_cast<int>(hand.getCards().size()); i++)
        {
            if (firstLoop)
            {
                dealCard(playerIndex, hand.getCards()[i].getImagePath());
                firstLoop = false;
                continue;
            }
            QTimer::singleShot(850, this, [=]() {
                dealCard(playerIndex, hand.getCards()[i].getImagePath());
            });

        }
    }
    players[playerIndex].hand = hand;
    players[playerIndex].money = money;
    players[playerIndex].status = status;
}

void Screens::allPlayersUpdated(const std::vector<Player>& players)
{
    // Need to implement
    // Updates all players in order with a time delay
    unsigned int waitTime = 0;

    for(int i = 0; i < static_cast<int>(players.size()); i++)
    {
        QTimer::singleShot(waitTime, this, [=]() {
            playerUpdated(i, players[i].hand, players[i].hand.getTotal(), players[i].money, players[i].status);
        });
        waitTime += 1500;
    }
}

void Screens::dealerUpdated(const Hand& hand, int total)
{
    int prevHandSize = dealerHand.getCards().size();
    dealerHand = hand;

    if (!showDealerCard && dealerHand.getCards().size() > 0)
    {
        dealerHand.setCardImagePath(0, ":/cardImages/cards_pngsource/back_of_card.png");
    }

    bool firstLoop = true;
    for (int i = prevHandSize; i < static_cast<int>(dealerHand.getCards().size()); i++)
    {
        if (firstLoop)
        {
            dealCard(-1, dealerHand.getCards()[i].getImagePath());
            firstLoop = false;
            continue;
        }
        QTimer::singleShot(3000, this, [=]() {
            dealCard(-1, dealerHand.getCards()[i].getImagePath());
        });
    }
    toggleEnabledGamePlayButtons(true);
}

void Screens::updateShowDealerCardBool(bool flipped)
{
    showDealerCard = flipped;
}

void Screens::currentPlayerTurn(int nextPlayerIndex)
{
    //TODO
    //Change POV to player at received index
}

void Screens::endBetting()
{
    ui->bettingArea->hide();
    toggleEnabledGamePlayButtons(true);
}

void Screens::toggleEnabledGamePlayButtons(bool enabled)
{
    toggleEnabledQPushButton(ui->hitButton, enabled);
    toggleEnabledQPushButton(ui->standButton, enabled);
    toggleEnabledQPushButton(ui->doubleButton, enabled);
    toggleEnabledQPushButton(ui->splitButton, enabled);
}

void Screens::toggleEnabledQPushButton(QPushButton *button, bool enabled)
{
    if (enabled)
    {
        button->setStyleSheet(QPushButtonStyle);
        button->setEnabled(enabled);
        return;
    }
    button->setStyleSheet(QPushButtonDisabledStyle);
    button->setEnabled(enabled);
}

void Screens::onPressNextRound()
{
    tableView->clearTable();
    emit sendNewRound();

    tableView->createDealerPile();
    ui->bettingArea->show();
}

