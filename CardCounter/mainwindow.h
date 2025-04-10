#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPalette>
#include <QPixmap>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>

#include "controller.h"
#include "screens.h"
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

    void onTrainingModeClicked();
    void onPlayModeClicked();
    void onTutorialModeClicked();


private:
    Ui::MainWindow *ui;
    TableView *tableView;
    Screens *screens;

    // Table Functions

    /**
     * @brief setUpTable Sets up the table for program start.
     */
    void setUpTable();

    // Table Functions End

    // StartMenu Functions

    /**
     * @brief setUpStartMenuButtons Sets up the button area for the startMenu.
     */
    void setUpStartMenuButtons();

    // StartMenu Functions End

    // StyleSheet

    /**
     * @brief setUpQStyleSheets Initalizes the QStrings for the different StyleSheets.
     */
    void setUpQStyleSheets();

    /**
     * @brief QPushButtonStylef QString of the general QPushButton StyleSheet.
     */
    QString QPushButtonStyle;

    /**
     * @brief getQLableStyle QString of the general QLabel StyleSheet.
     */
    QString QLabelStyle;

    /**
     * @brief getQWidgetStylenQString of the general QWidget StyleSheet.
     */
    QString QWidgetStyle;

    // StyleSheet End
};
#endif // MAINWINDOW_H
