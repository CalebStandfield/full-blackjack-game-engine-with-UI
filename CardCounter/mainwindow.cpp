#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Controller* c, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    std::vector<QString> images = {
        ":/new/prefix1/Cards/2_of_clubs.png"
        ":/new/prefix1/Cards/2_of_diamonds.png"
        ":/new/prefix1/Cards/2_of_hearts.png"
        ":/new/prefix1/Cards/2_of_spades.png"
        ":/new/prefix1/Cards/3_of_clubs.png"
        ":/new/prefix1/Cards/3_of_diamonds.png"
        ":/new/prefix1/Cards/3_of_hearts.png"
        ":/new/prefix1/Cards/3_of_spades.png"
        ":/new/prefix1/Cards/4_of_clubs.png"
        ":/new/prefix1/Cards/4_of_diamonds.png"
        ":/new/prefix1/Cards/4_of_hearts.png"
        ":/new/prefix1/Cards/4_of_spades.png"
        ":/new/prefix1/Cards/5_of_clubs.png"
        ":/new/prefix1/Cards/5_of_diamonds.png"
        ":/new/prefix1/Cards/5_of_hearts.png"
        ":/new/prefix1/Cards/5_of_spades.png"
        ":/new/prefix1/Cards/6_of_clubs.png"
        ":/new/prefix1/Cards/6_of_diamonds.png"
        ":/new/prefix1/Cards/6_of_hearts.png"
        ":/new/prefix1/Cards/6_of_spades.png"
        ":/new/prefix1/Cards/7_of_clubs.png"
        ":/new/prefix1/Cards/7_of_diamonds.png"
        ":/new/prefix1/Cards/7_of_hearts.png"
        ":/new/prefix1/Cards/7_of_spades.png"
        ":/new/prefix1/Cards/8_of_clubs.png"
        ":/new/prefix1/Cards/8_of_diamonds.png"
        ":/new/prefix1/Cards/8_of_hearts.png"
        ":/new/prefix1/Cards/8_of_spades.png"
        ":/new/prefix1/Cards/9_of_clubs.png"
        ":/new/prefix1/Cards/9_of_diamonds.png"
        ":/new/prefix1/Cards/9_of_hearts.png"
        ":/new/prefix1/Cards/9_of_spades.png"
        ":/new/prefix1/Cards/10_of_clubs.png"
        ":/new/prefix1/Cards/10_of_diamonds.png"
        ":/new/prefix1/Cards/10_of_hearts.png"
        ":/new/prefix1/Cards/10_of_spades.png"
        ":/new/prefix1/Cards/ace_of_clubs.png"
        ":/new/prefix1/Cards/ace_of_diamonds.png"
        ":/new/prefix1/Cards/ace_of_hearts.png"
        ":/new/prefix1/Cards/ace_of_spades.png"
        ":/new/prefix1/Cards/jack_of_clubs.png"
        ":/new/prefix1/Cards/jack_of_diamonds.png"
        ":/new/prefix1/Cards/jack_of_hearts.png"
        ":/new/prefix1/Cards/jack_of_spades.png"
        ":/new/prefix1/Cards/queen_of_clubs.png"
        ":/new/prefix1/Cards/queen_of_diamonds.png"
        ":/new/prefix1/Cards/queen_of_hearts.png"
        ":/new/prefix1/Cards/queen_of_spades.png"
        ":/new/prefix1/Cards/king_of_clubs.png"
        ":/new/prefix1/Cards/king_of_diamonds.png"
        ":/new/prefix1/Cards/king_of_hearts.png"
        ":/new/prefix1/Cards/king_of_spades.png"
    };

    ui->setupUi(this);
    // Set up function calls
    setUpTable();
    setUpQStyleSheets();
    setUpStartMenuButtons();

    ui->screens->setCurrentIndex(1);

    QPixmap bgImage(":/table/BlackJackTableMat.png");

    bgImage = bgImage.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(QPalette::Window, bgImage);
    this->setPalette(palette);

    this->setAutoFillBackground(true);

    connect(ui->blackjackTutorialButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onTrainingModeClicked);
    connect(ui->countCardsPlayButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onPlayModeClicked);
    connect(ui->blackjackPlayButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onTutorialModeClicked);
}

void MainWindow::onTrainingModeClicked() {
    //ui->screens->setCurrentIndex(0);
}

void MainWindow::onPlayModeClicked() {
    //ui->screens->setCurrentIndex(1);
}

void MainWindow::onTutorialModeClicked() {
    //ui->screens->setCurrentIndex(2);
}

void MainWindow::setUpTable()
{
    tableView = new TableView(ui->table);
    if (!ui->table->layout()) {
        ui->table->setLayout(new QVBoxLayout());
    }
    ui->table->layout()->addWidget(tableView);
}

void MainWindow::setUpStartMenuButtons()
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

void MainWindow::setUpQStyleSheets()
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

MainWindow::~MainWindow()
{
    delete ui;
}
