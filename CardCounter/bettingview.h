#ifndef BETTINGVIEW_H
#define BETTINGVIEW_H

#include <QObject>

class BettingView : public QObject
{
    Q_OBJECT
public:
    explicit BettingView(QObject *parent = nullptr);

signals:
};

#endif // BETTINGVIEW_H
