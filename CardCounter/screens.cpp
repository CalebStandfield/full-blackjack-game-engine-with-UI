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

    // Set up timer
    timer = new TimerManager();
}

Screens::~Screens()
{
    delete timer;
    delete tableView;
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
            &Screens::onPressMainMenuButton);
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
    tableView->setStyleSheet(QGraphicsViewStyle);
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
        "    background-color: transparent;"
        "    border: none;"
        "    color: white;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    padding: 6px;"
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
    ui->chipCountSettingsLineEdit->setStyleSheet(QLineEditStyle);
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

    // Next round and menu button
    ui->nextRound->setObjectName("nextRound");
    ui->backToMainMenuFromPlay->setObjectName("backToMenuFromPlay");
    toggleEnabledQPushButton(ui->nextRound, false);
    toggleEnabledQPushButton(ui->backToMainMenuFromPlay, true);
}

void Screens::setUpBettingMenu()
{
    ui->bettingArea->setStyleSheet(QWidgetStyle);
    ui->betSlider->setStyleSheet(QSliderStyle);
    ui->betSlider->setMinimum(1);

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
    QWidgetStyle =
        "QWidget {"
        "    background-color: rgba(50, 25, 20, 200);"
        "    border-radius: 20px;"
        "    border: 1px solid rgba(255, 255, 255, 15);"
        "    padding: 16px;"
        "    color: white;"
        "    font-size: 16px;"
        "}";

    QPushButtonStyle =
        "QPushButton {"
        "    background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #222, stop:1 #333);"
        "    color: white;"
        "    border: 1px solid rgba(255, 255, 255, 0.2);"
        "    border-radius: 12px;"
        "    padding: 12px 24px;"
        "    font-size: 24px;"
        "    font-weight: 600;"
        "}"
        "QPushButton:hover {"
        "    background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #444, stop:1 #555);"
        "    border: 1px solid rgba(255, 255, 255, 0.35);"
        "}"
        "QPushButton:pressed {"
        "    background-color: #111;"
        "    border: 1px solid #aaa;"
        "    padding-left: 14px;"
        "    padding-top: 14px;"
        "}";

    QPushButtonStyleSmallFont =
        "QPushButton {"
        "    background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #222, stop:1 #333);"
        "    color: white;"
        "    border: 1px solid rgba(255, 255, 255, 0.2);"
        "    border-radius: 12px;"
        "    padding: 12px 20px;"
        "    font-size: 10px;"
        "    font-weight: 600;"
        "}"
        "QPushButton:hover {"
        "    background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #444, stop:1 #555);"
        "    border: 1px solid rgba(255, 255, 255, 0.35);"
        "}"
        "QPushButton:pressed {"
        "    background-color: #111;"
        "    border: 1px solid #aaa;"
        "    padding-left: 14px;"
        "    padding-top: 14px;"
        "}";

    QPushButtonDisabledStyle =
        "QPushButton:disabled {"
        "    background-color: #161616;"
        "    color: #555;"
        "    border: 1px solid rgba(255, 255, 255, 0.1);"
        "    border-radius: 12px;"
        "    padding: 12px 24px;"
        "    font-size: 24px;"
        "}";

    QPushButtonDisabledStyleSmallFont =
        "QPushButton:disabled {"
        "    background-color: #161616;"
        "    color: #555;"
        "    border: 1px solid rgba(255, 255, 255, 0.1);"
        "    border-radius: 12px;"
        "    padding: 12px 20px;"
        "    font-size: 10px;"
        "}";

    QSliderStyle =
        "QSlider {"
        "    background: transparent;"
        "    height: 18px;"
        "}"
        "QSlider::groove:horizontal {"
        "    background: rgba(100, 100, 100, 60);"
        "    border: 1px solid rgba(255, 255, 255, 15);"
        "    height: 8px;"
        "    border-radius: 4px;"
        "}"
        "QSlider::handle:horizontal {"
        "    background: radial-gradient(circle, #aaa, #888);"
        "    border: 1px solid #aaa;"
        "    width: 20px;"
        "    height: 20px;"
        "    margin: -6px 0;"
        "    border-radius: 10px;"
        "}"
        "QSlider::handle:horizontal:hover {"
        "    background: radial-gradient(circle, #fff, #aaa);"
        "    border: 1px solid #ccc;"
        "}"
        "QSlider::sub-page:horizontal {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #aaa, stop:1 #666);"
        "    border-radius: 4px;"
        "}"
        "QSlider::add-page:horizontal {"
        "    background: rgba(30, 30, 30, 150);"
        "    border-radius: 4px;"
        "}";

    QLabelStyle =
        "QLabel {"
        "    background-color: transparent;"
        "    border: none;"
        "    color: white;"
        "    font-size: 30px;"
        "    font-weight: bold;"
        "    padding: 6px;"
        "}";

    QBetLabelStyle =
        "QLabel {"
        "    color: #ffffaa;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "    padding: 4px;"
        "    background-color: rgba(0, 0, 0, 0);"
        "    border: none;"
        "    border-radius: 0px;"
        "    qproperty-alignment: AlignCenter;"
        "}";

    QTextBrowserStyle =
        "QTextBrowser {"
        "    background-color: rgba(50, 25, 20, 220);"
        "    border-radius: 12px;"
        "    padding: 10px;"
        "    color: white;"
        "    font-size: 12px;"
        "}";

    QGraphicsViewStyle =
        "QGraphicsView {"
        "    background-color: transparent;"
        "    border: none;"
        "}";

    QStackedWidgetStyle =
        "QStackedWidget {"
        "    background-color: transparent;"
        "    border: none;"
        "}";

    QLineEditStyle =
        "QLineEdit {"
        "    background-color: transparent;"
        "    border: none;"
        "    color: white;"
        "    font-size: 14px;"
        "    font-weight: 600;"
        "    padding: 6px;"
        "}";
}

void Screens::setUpBackGround()
{
    QPixmap bgImage(":/backGround/brown_wooden_background.png");

    bgImage = bgImage.scaled(ui->centralwidget->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette bgPalette;
    bgPalette.setBrush(QPalette::Window, QBrush(bgImage));
    ui->centralwidget->setPalette(bgPalette);
    ui->centralwidget->setAutoFillBackground(true);

    QPixmap widgetImage(":/backGround/start_menu_screen.png");

    widgetImage = widgetImage.scaled(ui->startMenuMainWidget->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette widgetPalette;
    widgetPalette.setBrush(QPalette::Window, QBrush(widgetImage));
    ui->startMenuMainWidget->setPalette(widgetPalette);
    ui->startMenuMainWidget->setAutoFillBackground(true);

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
    tableView->clearTable();
    toggleEnabledQPushButton(ui->nextRound, false);

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

    //userIndex = QRandomGenerator::global()->bounded(playerCount);
    //qDebug() << userIndex;
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
        endPos = QPointF(950, 250); // far right
        rotation = -20;
        break;
    case 1:
        endPos = QPointF(750, 350); // middle right
        rotation = -10;
        break;
    case 2:
        endPos = QPointF(550, 400); // middle
        rotation = 0;
        break;
    case 3:
        endPos = QPointF(350, 350); // middle left
        rotation = 10;
        break;
    case 4:
        endPos = QPointF(150, 250); // far left
        rotation = 20;
        break;
    default:
        endPos = QPointF(550, 50);
        rotation = 0;
        break;
    }

    tableView->addCardAnimated(seatIndex, cardPNG, startPos, endPos, rotation);
}

void Screens::playerUpdated(int playerIndex, const Hand& hand, int total, int money, PLAYERSTATUS status)
{
    if(hand.getCards().size() == 1)
    {
        dealCard(playerIndex, hand.getCards()[0].getImagePath());
        players[playerIndex].hand.addCard(hand.getCards()[0]);

        // if(players[playerIndex].isUser)
        // {
        //     qDebug() << "After hand update: ";
        //     for(const Card& card : players[playerIndex].hand.getCards())
        //     {
        //         qDebug() << Rank::toString(card.getRank());
        //     }
        // }
    }
    else if(hand.getCards().size() >= 2)
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
            timer->scheduleSingleShot(800, [=]() {
                dealCard(playerIndex, hand.getCards()[i].getImagePath());});
        }
        players[playerIndex].hand = hand;
    }
    players[playerIndex].money = money;
    players[playerIndex].status = status;
}

void Screens::allPlayersUpdated(const std::vector<Player>& players)
{
    unsigned int waitTime = 0;
    Hand tempHand;
    for(int j = 0; j < 2; j++)
    {
        for(int i = 0; i < static_cast<int>(players.size()); i++)
        {
            tempHand = Hand(players[i].hand.getBet());
            tempHand.addCard(players[i].hand.getCards()[j]);
            timer->scheduleSingleShot(waitTime, [=]() {
                playerUpdated(i, tempHand, tempHand.getTotal(), players[i].money, players[i].status);
            });
            waitTime += 800;
        }
        waitTime += 800;
    }

    timer->scheduleSingleShot(waitTime, [=]() {
        emit dealAnimationComplete();
        toggleEnabledGamePlayButtons(true);
    });
}

void Screens::dealerUpdated(const Hand& hand, int total)
{
    int prevHandSize = dealerHand.getCards().size();
    dealerHand = hand;

    if (!showDealerCard && dealerHand.getCards().size() > 0)
    {
        dealerHand.setCardImagePath(0, ":/cardImages/cards_pngsource/back_of_card.png");
    }
    unsigned int waitTime = 800 * players.size();

    if (showDealerCard)
    {
        waitTime = 800;

        QString imagePath = dealerHand.getCards().at(0).getImagePath();
        tableView->revealDealerCard(imagePath);
    }

    for (int i = prevHandSize; i < static_cast<int>(dealerHand.getCards().size()); i++)
    {
        timer->scheduleSingleShot(waitTime, [=]() {
            dealCard(-1, dealerHand.getCards()[i].getImagePath());
        });
        waitTime = (waitTime * 2) + 800;
    }
}

void Screens::updateShowDealerCardBool(bool flipped)
{
    showDealerCard = flipped;
}

void Screens::currentPlayerTurn(int nextPlayerIndex)
{
    //TODO
    //Change POV to player at received index
    if(players[nextPlayerIndex].isUser)
    {
        toggleEnabledGamePlayButtons(true);
    }
    else
    {
        toggleEnabledGamePlayButtons(false);
    }
}

void Screens::endBetting()
{
    ui->bettingArea->hide();
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
        if (button->objectName() == "nextRound" || button->objectName() == "backToMenuFromPlay")
        {
            button->setStyleSheet(QPushButtonStyleSmallFont);
        }
        else
        {
            button->setStyleSheet(QPushButtonStyle);
        }
        button->setEnabled(enabled);
        return;
    }
    if (button->objectName() == "nextRound" || button->objectName() == "backToMenuFromPlay")
    {
        button->setStyleSheet(QPushButtonDisabledStyleSmallFont);
    }
    else
    {
        button->setStyleSheet(QPushButtonDisabledStyle);
    }
    button->setEnabled(enabled);
}

void Screens::endRound(QString message)
{
    toggleEnabledQPushButton(ui->nextRound, true);
    toggleEnabledGamePlayButtons(false);
}

void Screens::onPressNextRound()
{
    tableView->clearTable();

    emit sendNewRound();
    toggleEnabledQPushButton(ui->nextRound, false);
    toggleEnabledGamePlayButtons(false);

    tableView->createDealerPile();
    ui->betSlider->setMaximum(players[userIndex].money);
    ui->bettingArea->show();
}

void Screens::onPressMainMenuButton()
{
    emit sendStopEverything();
    timer->cancelAllTimers();
    players.clear();
    ui->screens->setCurrentIndex(0);
}
