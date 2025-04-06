#ifndef STATISTICS_H
#define STATISTICS_H

#include <QObject>

class Statistics : public QObject
{
    Q_OBJECT
public:
    explicit Statistics(QObject *parent = nullptr);

signals:
};

#endif // STATISTICS_H
