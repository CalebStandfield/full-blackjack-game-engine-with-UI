#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>

#include "controller.h"
#include "screens.h"
#include "box2dphysicsscene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Controller* controller, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Controller *controller;
    Screens *screens;
    box2dPhysicsScene* m_scene;

    void setUpMainWindowConnects();
};
#endif // MAINWINDOW_H
