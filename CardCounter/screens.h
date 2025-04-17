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
#include "timermanager.h"

using PlayerStatus::PLAYERSTATUS;

class Screens : public QStackedWidget
{
    Q_OBJECT
public:
    explicit Screens(Ui::MainWindow *ui, QWidget *parent = nullptr);

    ~Screens();

private:
    Ui::MainWindow *ui;
    TableView *tableView;
    TimerManager* timer;

    enum GAMEPLAYMODE {
        BLACKJACK,
        BLACKJACKTUTORIAL,
        BLACKJACKPRACTICE,
        UNSELECTED
    };

    /**
     * @brief mode The mode the user has selected
     */
    GAMEPLAYMODE mode;

    /**
     * @brief players A vector of all the players in the game
     */
    std::vector<Player> players;

    /**
     * @brief dealerHand The dealers cards
     */
    Hand dealerHand;

    /**
     * @brief userIndex An int to signify who the user is
     */
    unsigned int userIndex;

    /**
     * @brief initialMoney The amount of money put up by the player
     */
    unsigned int initialMoney;

    /**
     * @brief currentBet The currecnt bet of the player
     */
    int currentBet;

    /**
     * @brief playerCount The desiered number of players by the user
     * @default 1 There must be at least 1 player
     */
    unsigned int playerCount = 1;

    /**
     * @brief deckCount The disred number of decks by the user
     * @default 1 There must be at least 1 deck
     */
    unsigned int deckCount = 1;

    /**
     * @brief showDealerCard A bool for when to display the dealer card
     */
    bool showDealerCard;

    /**
     * @brief setUpConnect Sets up all the connect functions for this class
     */
    void setUpScreenConnects();

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
     * @brief setUpBankruptcyMenu Sets up the area where you can either go to menu or play again
     */
    void setUpBankruptcyMenu();

    /**
     * @brief setUpGamePlayButtons Sets up the game play buttons
     */
    void setUpGamePlayButtons();

    /**
     * @brief setUpSettingsPopup Sets up the settings pop up
     */
    void setUpSettingsPopup();

    /**
     * @brief setUpPlayerInfoBox Sets up the playerInfoBox
     */
    void setUpPlayerInfoBox();

    /**
     * @brief setUpQStyleSheets Initalizes the QStrings for the different StyleSheets
     */
    void setUpQStyleSheets();

    /**
     * @brief QStackedWidgetStyle QString of the general widget StyleSheet
     */
    QString QStackedWidgetStyle;

    /**
     * @brief QPushButtonStyle QString of the general QPushButton StyleSheet
     */
    QString QPushButtonStyle;

    /**
     * @brief QPushButtonStyleSmallFont QString of the general QPushButton StyleSheet with smaller font
     */
    QString QPushButtonStyleSmallFont;

    /**
     * @brief QPushButtonDisabledStyle QString of the disabled version of a QPushButton StyleSheet
     */
    QString QPushButtonDisabledStyle;

    /**
     * @brief QPushButtonDisabledStyleSmallFont QString of the disabled version of a QPushButton StyleSheet with smaller font
     */
    QString QPushButtonDisabledStyleSmallFont;

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
     * @brief getQWidgetStyle QString of the general QTextBrowser StyleSheet
     */
    QString QGraphicsViewStyle;

    /**
     * @brief QLineEditStyle QString of the general QLine StyleSheet
     */
    QString QLineEditStyle;

    /**
     * @brief moveToPlayScreen Move from current screen to the play screen
     */
    void moveToPlayScreen();

    /**
     * @brief moveBackToStartScreen Move from the current to the start screen
     */
    void moveToStartScreen();

    /**
     * @brief toggleVisibleSettingsPopup Sets the visibility of the settings popup
     * @param show The state to set the setting popup
     */
    void toggleVisibleSettingsPopup(bool show);

    /**
     * @brief toggleVisibleBettingView Sets the visibility of the betting view
     * @param show The state to set the betting view
     */
    void toggleVisibleBettingView(bool show);

    /**
     * @brief toggleVisibleSettingsPopup Sets the visibility of the settings popup
     * @param show The state to set the setting popup
     */
    void toggleVisibleGamePlayButtons(bool show);

    /**
     * @brief toggleVisableBankruptcyMenu Sets the visibility of the game over screen
     * @param show The state to set the setting popup
     */
    void toggleVisableBankruptcyMenu(bool show);

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

    /**
     * @brief onPressMainMenuButton Logic for when the user presses Main Menu
     */
    void onPressMainMenuButton();

    /**
     * @brief onPressPlacedBetButton Logic for when the user places their bet
     */
    void onPressPlacedBetButton();

    /**
     * @brief onPressBettingAmountButtons Logic for when the user clicks "all In", "half" "minimum bet"
     */
    void onPressBettingAmountButtons();

    /**
     * @brief onEditChipCountLineEdit Logic for when the user edits the line edit signifying how much money to play with
     */
    void onEditChipCountLineEdit();

    /**
     * @brief toggleEnabledGamePlayButtons Toggles the GamePlay buttons and their style
     * @param enabled A bool for if they should look/be enabled or disabled
     */
    void toggleEnabledGamePlayButtons(bool enabled);

    /**
     * @brief toggleEnabledQPushButton Toggles the button passed in to disabled or enabled
     * @param button The button to toggle
     * @param enabled A bool for if the button should look/be enabled or disabled
     */
    void toggleEnabledQPushButton(QPushButton *button, bool enabled);

    /**
     * @brief onPressNextRound Handles pressing the next round button
     */
    void onPressNextRound();

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

    /**
     * @brief sendOnBet Signal to send for when the user presses sendBet
     * @param playerBet The amount to bet
     */
    void sendOnBet(int playerBet);

    // During game play
    /**
     * @brief dealAnimationComplete Signal to send for when the deal animation is complete
     */
    void dealAnimationComplete();

    // End game
    /**
     * @brief sendNewRound Signal to send for when the user presses new round
     */
    void sendNewRound();

    /**
     * @brief sendStopEverything Signal to send for when the user leaves the game
     */
    void sendStopEverything();

private slots:
    /**
     * @brief dealCard
     * @param seatIndex
     * @param imagePath
     */
    void dealCard(int seatIndex, QString imagePath);

    /**
     * @brief updateBetLabelText Updates the betting lable for the betting view
     * @param value The value to set the label to display
     */
    void updateBetLabelText(unsigned int  value);

    /**
     * @brief updateSettingsSlider Updates the slider that calls this method to the value
     * @param value The value to set the slider value to
     */
    void updateSettingsSlider(unsigned int value);
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
     * @brief allPlayersUpdated Slot for receiving all of the updated players to display
     * @param players The vector containing all of the players
     */
    void allPlayersUpdated(const std::vector<Player>& players);

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
     * @param money The money of the current player
     * @param bet The bet of the current player
     */
    void currentPlayerTurn(int nextPlayerIndex, int money, int bet);

    /**
     * @brief endBetting Slot for changing from betting phase to playing phase
     */
    void endBetting();

    /**
     * @brief endRound SLot for the round ending
     * @param message The message to display of the round
     */
    void endRound(QString message);

    /**
     * @brief updateShowDealerCardBool Updates the bool for when to flip the dealers secret card
     * @param flipped A bool for if to flip or not
     */
    void updateShowDealerCardBool(bool flipped);

    /**
     * @brief splitPlayers Slot to split the player at the given index with the updated players
     * @param originalIndex The index of the player to split
     * @param originalPlayer The original player
     * @param newPlayer The new player
     */
    void onsplitPlayers(int originalIndex, const Player& originalPlayer, const Player& newPlayer);

    /**
     * @brief onGameOver Logic for when the controller sends the game over signal
     */
    void onGameOver();
};

#endif // SCREENS_H
