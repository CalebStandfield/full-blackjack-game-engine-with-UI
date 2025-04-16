#ifndef PLAYERINFOVIEW_H
#define PLAYERINFOVIEW_H

#include <QObject>
#include "ui_mainwindow.h"

class PlayerInfoView : public QObject
{
    Q_OBJECT
public:
    explicit PlayerInfoView(Ui::MainWindow *ui, QObject *parent = nullptr);

private:
    Ui::MainWindow *ui;

signals:
};

#endif // PLAYERINFOVIEW_H
