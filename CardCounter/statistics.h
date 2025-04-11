#ifndef STATISTICS_H
#define STATISTICS_H

#include <QObject>

enum class MOVE {
    HIT,
    DOUBLE,
    SPLIT,
    STAND
};

class Statistics : public QObject
{
    Q_OBJECT
public:
    explicit Statistics(QObject *parent = nullptr);

    static const MOVE HardTable[17][10];

    static const MOVE SoftHands[9][10];

    static const MOVE PairHands[10][10];

signals:
};

#endif // STATISTICS_H
