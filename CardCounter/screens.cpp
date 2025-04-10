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

    // Connects
    setUpConnect();
    tableViewCardTest();
}

void Screens::setUpConnect()
{
    // Gameplay buttons
    connect(ui->blackjackPlayButton,
            &QPushButton::clicked,
            this,
            &Screens::moveToPlayScreen);
    connect(ui->blackjackTutorialButton,
            &QPushButton::clicked,
            this,
            &Screens::moveToPlayScreen);
    connect(ui->countCardsPlayButton,
            &QPushButton::clicked,
            this,
            &Screens::moveToPlayScreen);
    connect(ui->countCardsTutorialButton,
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
    ui->blackjackTutorialButton->setStyleSheet(QPushButtonStyle);
    ui->countCardsPlayButton->setStyleSheet(QPushButtonStyle);
    ui->countCardsTutorialButton->setStyleSheet(QPushButtonStyle);

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

    QLabelStyle =
        "QLabel {"
        "    color: white;"
        "    font-size: 32px;"
        "    font-weight: bold;"
        "    padding: 5px;"
        "}";

    QWidgetStyle =
        "QWidget {"
        "    background-color: rgba(50, 50, 50, 225);"
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
    } else if (name == "countCardsTutorialButton") {
        mode = GAMEPLAYMODE::COUNTCARDSTUTORIAL;
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

void Screens::applyShadowToWidget(QWidget *widget) {
    // Create a shadow effect
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();

    // Set how the shadow looks
    shadow->setBlurRadius(15);
    shadow->setOffset(5, 5);
    shadow->setColor(QColor(0, 0, 0, 160));

    widget->setGraphicsEffect(shadow);
}

void Screens::tableViewCardTest()
{
    QString tempCard = ":/cardImages/cards_pngsource/2_of_spades.png";
    tableView->addCardAt(tempCard, 300, 300);
}
