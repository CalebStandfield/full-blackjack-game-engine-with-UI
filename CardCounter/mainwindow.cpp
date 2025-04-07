#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    std::vector<std::string> images = {
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
}

MainWindow::~MainWindow()
{
    delete ui;
}
