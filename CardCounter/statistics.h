#ifndef STATISTICS_H
#define STATISTICS_H

#include <QObject>

class Statistics : public QObject
{
    Q_OBJECT
public:
    explicit Statistics(QObject *parent = nullptr);

    static const QString HardTable[16][10];

    static const QString SoftHands[8][10];

    static const QString PairHands[10][10];

signals:
};

#endif // STATISTICS_H
