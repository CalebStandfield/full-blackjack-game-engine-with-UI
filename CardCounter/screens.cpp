#include "screens.h"
#include <QPalette>
#include <QPixmap>
#include <qdebug.h>
#include <QGraphicsDropShadowEffect>

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
            &Screens::tableViewCardTest);


}

void Screens::setUpTable()
{
    tableView = new TableView(ui->table);
    if (!ui->table->layout()) {
        ui->table->setLayout(new QVBoxLayout());
    }
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
    ui->fiveDollarButton->setStyleSheet(QPushButtonStyle);
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
        "    background: white;"
        "    border-radius: 5px;"
        "    height: 10px;"
        "}"
        "QSlider::groove:horizontal {"
        "    border: 1px solid #ccc;"
        "    height: 10px;"
        "    background: #f0f0f0;"
        "    border-radius: 5px;"
        "}"
        "QSlider::handle:horizontal {"
        "    background: white;"
        "    border: 1px solid #aaa;"
        "    border-radius: 5px;"
        "    width: 20px;"
        "    height: 20px;"
        "    margin-top: 0px;"  // Adjust this margin for centering
        "    margin-left: -10px;" // Center handle horizontally
        "}"
        "QSlider::handle:horizontal:hover {"
        "    background: #e0e0e0;"
        "    border-color: #888;"
        "}"
        "QSlider::sub-page:horizontal {"
        "    background: #ddd;"
        "    border-radius: 5px;"
        "}"
        "QSlider::add-page:horizontal {"
        "    background: #f0f0f0;"
        "    border-radius: 5px;"
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
    QString tempCard = ":/cardImages/cards_pngsource/2_of_spades.png";
    tableView->addCardAnimated(tempCard, QPointF(0, 0), QPointF(400, 200), 45);
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


