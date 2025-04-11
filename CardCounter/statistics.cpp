#include "statistics.h"


const QString Statistics::HardTable[17][10] = {
    { "H","H","H","H","H","H","H","H","H","H" },            // Hard 5
    { "H","H","H","H","H","H","H","H","H","H" },            // Hard 6
    { "H","H","H","H","H","H","H","H","H","H" },            // Hard 7
    { "H","H","H","H","H","H","H","H","H","H" },            // Hard 8
    { "H","D","D","D","D","H","H","H","H","H" },            // Hard 9
    { "D","D","D","D","D","D","D","D","H","H" },            // Hard 10
    { "D","D","D","D","D","D","D","D","D","D" },            // Hard 11
    { "H","H","ST","ST","ST","H","H","H","H","H"},          // Hard 12
    { "ST","ST","ST","ST","ST","H","H","H","H","H" },       // Hard 13
    { "ST","ST","ST","ST","ST","H","H","H","H","H" },       // Hard 14
    { "ST","ST","ST","ST","ST","H","H","H","H","H" },       // Hard 15
    { "ST","ST","ST","ST","ST","H","H","H","H","H" },       // Hard 16
    { "ST","ST","ST","ST","ST","ST","ST","ST","ST","ST" },  // Hard 17
    { "ST","ST","ST","ST","ST","ST","ST","ST","ST","ST" },  // Hard 18
    { "ST","ST","ST","ST","ST","ST","ST","ST","ST","ST" },  // Hard 19
    { "ST","ST","ST","ST","ST","ST","ST","ST","ST","ST" },  // Hard 20
    { "ST","ST","ST","ST","ST","ST","ST","ST","ST","ST" },  // Hard 21
    };

const QString Statistics::SoftHands[9][10] = {
    { "H","H","H","D","D","H","H","H","H","H" },            // A,2
    { "H","H","H","D","D","H","H","H","H","H" },            // A,3
    { "H","H","D","D","D","H","H","H","H","H" },            // A,4
    { "H","H","D","D","D","H","H","H","H","H" },            // A,5
    { "H","D","D","D","D","H","H","H","H","H" },            // A,6
    { "D","D","D","D","D","ST","ST","H","H","H" },          // A,7
    { "ST","ST","ST","ST","D","ST","ST","ST","ST","ST" },   // A,8
    { "ST","ST","ST","ST","ST","ST","ST","ST","ST","ST" },  // A,9
    { "ST","ST","ST","ST","ST","ST","ST","ST","ST","ST" },  // A,10
    };

const QString Statistics::PairHands[10][10] = {
    { "SP","SP","SP","SP","SP","SP","H","H","H","H" },          // 2,2
    { "SP","SP","SP","SP","SP","SP","H","H","H","H" },          // 3,3
    { "H","H","H","SP","SP","H","H","H","H","H" },              // 4,4
    { "D","D","D","D","D","D","D","D","H","H" },                // 5,5
    { "SP","SP","SP","SP","SP","H","H","H","H","H" },           // 6,6
    { "SP","SP","SP","SP","SP","SP","H","H","H","H" },          // 7,7
    { "SP","SP","SP","SP","SP","SP","SP","SP","SP","SP" },      // 8,8
    { "SP","SP","SP","SP","SP","ST","SP","SP","ST","ST" },      // 9,9
    { "ST","ST","ST","ST","ST","ST","ST","ST","ST","ST" },      // 10,10
    { "SP","SP","SP","SP","SP","SP","SP","SP","SP","SP" },      // A,A
    };

Statistics::Statistics(QObject *parent)
    : QObject{parent}
{}
