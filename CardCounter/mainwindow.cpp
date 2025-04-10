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

    // ui->screens->setCurrentIndex(0);

    QPixmap bgImage(":/table/BlackJackTableMat.png");

    bgImage = bgImage.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(QPalette::Window, bgImage);
    this->setPalette(palette);

    this->setAutoFillBackground(true);

    ui->CardCountring->setStyleSheet("color: white; background-color: transparent;");

    // Set up the tableView
    tableView = new TableView(ui->table);
    if (!ui->table->layout()) {
        ui->table->setLayout(new QVBoxLayout());
    }
    ui->table->layout()->addWidget(tableView);

    connect(ui->trainingMode,
            &QPushButton::clicked,
            this,
            &MainWindow::onTrainingModeClicked);
    connect(ui->playMode,
            &QPushButton::clicked,
            this,
            &MainWindow::onPlayModeClicked);
    connect(ui->tutorialMode,
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

MainWindow::~MainWindow()
{
    delete ui;
}
