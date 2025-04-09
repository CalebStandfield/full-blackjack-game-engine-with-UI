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

    static const QString HardTable[16][10] = {
        // Hard 5
        { "H","H","H","H","H","H","H","H","H","H" },
        // Hard 6
        { "H","H","H","H","H","H","H","H","H","H" },
        // Hard 7
        { "H","H","H","H","H","H","H","H","H","H" },
        // Hard 8
        { "H","H","H","H","H","H","H","H","H","H" },
        // Hard 9
        { "H","D","D","D","D","H","H","H","H","H" },
        // Hard 10
        { "D","D","D","D","D","D","D","D","H","H" },
        // Hard 11
        { "D","D","D","D","D","D","D","D","D","D" },
        // Hard 12
        { "H","H","ST","ST","ST","H","H","H","H","H"},
        // Hard 13
        { "ST","ST","ST","ST","ST","H","H","H","H","H" },
        // Hard 14
        { "ST","ST","ST","ST","ST","H","H","H","H","H" },
        // Hard 15
        { "ST","ST","ST","ST","ST","H","H","H","H","H" },
        // Hard 16
        { "ST","ST","ST","ST","ST","H","H","H","H","H" },
        // Hard 17
        { "ST","ST","ST","ST","ST","ST","ST","ST","ST","ST" },
        // Hard 18
        { "ST","ST","ST","ST","ST","ST","ST","ST","ST","ST" },
        // Hard 19
        { "ST","ST","ST","ST","ST","ST","ST","ST","ST","ST" },
        // Hard 20
        { "ST","ST","ST","ST","ST","ST","ST","ST","ST","ST" },
    };

    static const QString SoftHands[8][10] = {
        // A,2
        { "H","H","H","D","D","H","H","H","H","H" },
        // A,3
        { "H","H","H","D","D","H","H","H","H","H" },
        // A,4
        { "H","H","D","D","D","H","H","H","H","H" },
        // A,5
        { "H","H","D","D","D","H","H","H","H","H" },
        // A,6
        { "H","D","D","D","D","H","H","H","H","H" },
        // A,7
        { "D","D","D","D","D","ST","ST","H","H","H" },
        // A,8
        { "ST","ST","ST","ST","D","ST","ST","ST","ST","ST" },
        // A,9
        { "ST","ST","ST","ST","ST","ST","ST","ST","ST","ST" },
    };

    static const QString PairHands[10][10] = {
        // 2,2
        { "SP","SP","SP","SP","SP","SP","H","H","H","H" },
        // 3,3
        { "SP","SP","SP","SP","SP","SP","H","H","H","H" },
        // 4,4
        { "H","H","H","SP","SP","H","H","H","H","H" },
        // 5,5
        { "D","D","D","D","D","D","D","D","H","H" },
        // 6,6
        { "SP","SP","SP","SP","SP","H","H","H","H","H" },
        // 7,7
        { "SP","SP","SP","SP","SP","SP","H","H","H","H" },
        // 8,8
        { "SP","SP","SP","SP","SP","SP","SP","SP","SP","SP" },
        // 9,9
        { "SP","SP","SP","SP","SP","ST","SP","SP","ST","ST" },
        // 10,10
        { "ST","ST","ST","ST","ST","ST","ST","ST","ST","ST" },
        // A,A
        { "SP","SP","SP","SP","SP","SP","SP","SP","SP","SP" },
        };

    ui->setupUi(this);

    // Create all signal/slot connections with c (controller) here
    // Do not use controller in rest of class, breaks mvc
}

MainWindow::~MainWindow()
{
    delete ui;
}
