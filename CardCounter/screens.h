#ifndef SCREENS_H
#define SCREENS_H

#include <QWidget>
#include <QtWidgets/qstackedwidget.h>

class Screens : public QStackedWidget
{
    Q_OBJECT
public:
    explicit Screens(QWidget *parent = nullptr);
};

#endif // SCREENS_H
