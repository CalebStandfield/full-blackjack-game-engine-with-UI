#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPalette>
#include <QPixmap>
#include "controller.h"
#include "tableview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Controller* c, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TableView *tableView;
};
#endif // MAINWINDOW_H
