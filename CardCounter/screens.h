#ifndef SCREENS_H
#define SCREENS_H

#include "tableview.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QtWidgets/qstackedwidget.h>

class Screens : public QStackedWidget
{
    Q_OBJECT
public:
    explicit Screens(Ui::MainWindow *ui, QWidget *parent = nullptr);

private:
    Ui::MainWindow *ui;
    TableView *tableView;

    // BackGround Functions

    void setUpBackGround();

    // Table Functions

    /**
     * @brief setUpTable Sets up the table for program start.
     */
    void setUpTable();

    // StartMenu Functions

    /**
     * @brief setUpStartMenuButtons Sets up the button area for the startMenu.
     */
    void setUpStartMenuButtons();

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
};

#endif // SCREENS_H
