#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>

#include "controller.h"
#include "screens.h"
#include "playerinfoview.h"
#include "box2dbase.h"
#include "gamestate.h"

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

    void setupCoinAnimViews();

private:
    Ui::MainWindow *ui;
    Controller *controller;
    Screens *screens;
    PlayerInfoView *infoBar;
    box2Dbase* m_scene;
    GameState *state;

    void setUpMainWindowConnects();
};
#endif // MAINWINDOW_H
