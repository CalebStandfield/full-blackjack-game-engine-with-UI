#ifndef SCREENS_H
#define SCREENS_H

#include "player.h"
#include "tableview.h"
#include "ui_mainwindow.h"
#include "hand.h"
#include "playerStatus.h"
#include <QWidget>
#include <QGraphicsView>
#include <QtWidgets/qstackedwidget.h>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

using PlayerStatus::PLAYERSTATUS;

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

    std::vector<Player> players;

    Hand dealerHand;

    unsigned int playerIndex;

    unsigned int initialMoney;

    int currentBet;

    unsigned int playerCount;

    unsigned int deckCount;

    bool showDealerCard;

    /**
     * @brief setUpConnect Sets up all the connect functions for this class
     */
    void setUpScreenConnect();

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
     * @brief setUpBettingMenu Sets up the area where you select your bet amount
     */
    void setUpBettingMenu();

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
     * @brief QPushButtonDisabledStyle QString of the disabled version of a QPushButton StyleSheet
     */
    QString QPushButtonDisabledStyle;

    /**
     * @brief getQLableStyle QString of the general QLabel StyleSheet
     */
    QString QLabelStyle;

    /**
     * @brief getQBetLableStyle QString of the betLabel QLabel StyleSheet
     */
    QString QBetLabelStyle;

    /**
     * @brief getQWidgetStylenQString of the general QWidget StyleSheet
     */
    QString QWidgetStyle;

    /**
     * @brief getQSliderStylenQString of the general QWidget StyleSheet
     */
    QString QSliderStyle;
    
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
     * @brief acceptSettingsButtonPressed Logic for sending the setting values to the controller
     */
    void acceptSettingsButtonPressed();

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

    /**
     * @brief onPressHitButton Logic for when the user presses hit
     */
    void onPressHitButton();

    /**
     * @brief onPressStandButton Logic for when the user presses stnad
     */
    void onPressStandButton();

    /**
     * @brief onPressDoubleButton Logic for when the user presses double
     */
    void onPressDoubleButton();

    /**
     * @brief onPressSplitButton Logic for when the user presses split
     */
    void onPressSplitButton();

    void onPressPlacedBetButton();

    void onPressBettingAmountButtons();

    void toggleEnabledGamePlayButtons(bool enabled);

    void toggleEnabledQPushButton(QPushButton *button, bool enabled);

signals:

    // Settings accept

    /**
     * @brief sendSettingsAccepted Singal to send for when the suer has accepted the settings
     * @param players The number of players in the game
     * @param decks The number of decks to play with
     * @param deterministic 0 = random shuffle, 1 = shuffle for single player, 2 = shuffle for 3 players
     */
    void sendSettingsAccepted(std::vector<Player>& players, int decks, int deterministic);

    // Betting

    /**
     * @brief sendGameSetupCompleteStartBetting
     */
    void sendGameSetupCompleteStartBetting();

    // Game play buttons

    /**
     * @brief sendHitButtonPressed Signal to send for when the user presses hit
     */
    void sendHitButtonPressed();

    /**
     * @brief sendStandButtonPressed Signal to send for when the user presses stand
     */
    void sendStandButtonPressed();

    /**
     * @brief sendDoubleButtonPressed Signal to send for when the user presses double
     */
    void sendDoubleButtonPressed();

    /**
     * @brief sendSplitButtonPressed Signal to send for when the user presses split
     */
    void sendSplitButtonPressed();

    void sendOnBet(int playerBet);


private slots:
    void updateBetLabelText(unsigned int  value);

    void dealCard(int seatIndex, QString imagePath);
public slots:
    /**
     * @brief playerUpdated Slot for receiving information about an updated player with their updated info
     * @param playerIndex The player that has updated
     * @param hand The new hand for the player
     * @param total The total value of their cards
     * @param money The money they have left
     * @param status The status of the player
     */
    void playerUpdated(int playerIndex, const Hand& hand, int total, int money, PLAYERSTATUS status);

    /**
     * @brief dealerUpdated Slot for receiving updated dealer info
     * @param hand The new hand of the dealer
     * @param total The total value of their cards
     */
    void dealerUpdated(const Hand& hand, int total);

    // used for changing POV
    /**
     * @brief currentPlayerTurn Slot for changing to the player at given index
     * @param nextPlayerIndex The index of the next player that is up now
     */
    void currentPlayerTurn(int nextPlayerIndex);

    /**
     * @brief endBetting Slot for changing from betting phase to playing phase
     */
    void endBetting();

    void updateShowDealerCardBool(bool flipped);

};

#endif // SCREENS_H
