#ifndef STATSVIEW_H
#define STATSVIEW_H

#include <QObject>

class StatsView : public QObject
{
    Q_OBJECT
public:
    explicit StatsView(QObject *parent = nullptr);

signals:
};

#endif // STATSVIEW_H
