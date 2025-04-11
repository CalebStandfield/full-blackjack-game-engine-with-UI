#ifndef STATISTICS_H
#define STATISTICS_H

#include <QObject>

class Statistics : public QObject
{
    Q_OBJECT
public:
    explicit Statistics(QObject *parent = nullptr);

    static const QString HardTable[17][10];

    static const QString SoftHands[9][10];

    static const QString PairHands[10][10];

signals:
};

#endif // STATISTICS_H
