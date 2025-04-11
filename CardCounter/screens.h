#ifndef SCREENS_H
#define SCREENS_H

#include "tableview.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QGraphicsView>
#include <QtWidgets/qstackedwidget.h>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Screens : public QStackedWidget
{
    Q_OBJECT
public:
    explicit Screens(Ui::MainWindow *ui, QWidget *parent = nullptr);

private:
    Ui::MainWindow *ui;
    TableView *tableView;

    enum GAMEPLAYMODE {
        BLACKJACK,
        BLACKJACKTUTORIAL,
        COUNTCARDS,
        COUNTCARDSTUTORIAL,
        UNSELECTED
    };

    GAMEPLAYMODE mode;

    /**
     * @brief setUpConnect Sets up all the connect functions for this class
     */
    void setUpConnect();

    /**
     * @brief setUpBackGround Sets up the general background for the ui
     */
    void setUpBackGround();

    /**
     * @brief setUpTable Sets up the table for program start
     */
    void setUpTable();

    /**
     * @brief setUpStartMenuButtons Sets up the button area for the startMenu
     */
    void setUpStartMenuButtons();

    /**
     * @brief setUpGamePlayButtons Sets up the game play buttons
     */
    void setUpGamePlayButtons();

    /**
     * @brief setUpSettingsPopup Sets up the settings pop up
     */
    void setUpSettingsPopup();

    /**
     * @brief setUpQStyleSheets Initalizes the QStrings for the different StyleSheets
     */
    void setUpQStyleSheets();

    /**
     * @brief QPushButtonStylef QString of the general QPushButton StyleSheet
     */
    QString QPushButtonStyle;

    /**
     * @brief getQLableStyle QString of the general QLabel StyleSheet
     */
    QString QLabelStyle;

    /**
     * @brief getQWidgetStylenQString of the general QWidget StyleSheet
     */
    QString QWidgetStyle;

    /**
     * @brief getQWidgetStylenQString of the general QTextBrowser StyleSheet
     */
    QString QTextBrowserStyle;

    /**
     * @brief getQWidgetStylenQString of the general QTextBrowser StyleSheet
     */
    QString QGraphicsViewStyle;

    /**
     * @brief moveToPlayScreen Move from current screen to the play screen
     */
    void moveToPlayScreen();

    /**
     * @brief moveBackToStartScreen Move from the current to the start screen
     */
    void moveToStartScreen();

    /**
     * @brief hideSettingsPopup Hides the settings popup
     */
    void hideSettingsPopup();

    /**
     * @brief showSettingsPopup Shows the settings popup
     */
    void showSettingsPopup();

    /**
     * @brief applyShadowToWidget Applies a shadow effect for more depth for the passed in widget
     * @param widget The widget to give shadow to
     */
    void applyShadowToWidget(QWidget *widget);

    /**
     * @brief move to the screen that shows infromation about the blackjack charts and how to play
     */
    void moveToInforScreen();

    /**
     * @brief this methods add an image to the window in the tutorial
     */
    void setUpBasicStrategyCharts();

    void tableViewCardTest();

    void hitButtonOnPress();
    void standButtonOnPress();
    void doubleButtonOnPress();
    void splitButtonOnPress();

signals:
    // Blackjack game start
    void blackjackPlayButton();

    // Game play buttons
    void sendHitButtonPressed();
    void sendStandbuttonPressed();
    void sendDoubleButtonPressed();
    void sendSplitButtonPressed();


private slots:
public slots:

};

#endif // SCREENS_H
