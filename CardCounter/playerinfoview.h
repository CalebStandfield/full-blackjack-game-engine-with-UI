#ifndef PLAYERINFOVIEW_H
#define PLAYERINFOVIEW_H

#include <QObject>
#include <QLabel>
#include <QVector>
#include "player.h"
#include "hand.h"
#include "playerStatus.h"
#include "ui_mainwindow.h"

using PlayerStatus::PLAYERSTATUS;

class PlayerInfoView : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief PlayerInfoView Constructor to create the player bar view
     * @param ui
     * @param parent
     */
    explicit PlayerInfoView(Ui::MainWindow *ui, QObject *parent = nullptr);

public slots:
    /**
     * @brief onSettingsAccepted Slot to create the player info cards once the settings and players have been setup
     * @param players The players in the game
     * @param deckCount The number of decks used in the game
     * @param deterministic 0 for random shuffle, 1 for single player determined shuffle, 2 > for multiple player determined shuffle
     */
    void onSettingsAccepted(const std::vector<Player> &players, int deckCount, int deterministic);

    /**
     * @brief onPlayerUpdated Slot to update the money and status of the player at the passed index
     * @param playerIndex The index of the player
     * @param hand The hand of the player
     * @param total The total of the cards in the hand
     * @param money The money the player has
     * @param status The status of the player
     */
    void onPlayerUpdated(int playerIndex, const Hand &hand, int total, int money, PLAYERSTATUS status);

    /**
     * @brief onUpdateAllPlayers Slot to update all of the players
     * @param players The players to update
     */
    void onUpdateAllPlayers(const std::vector<Player> &players);

    /**
     * @brief onSplitPlayers Slot that a player split
     * @param originalIndex The index of the original player who split
     * @param originalPlayer The original player
     * @param newPlayer The newly split player
     */
    void onSplitPlayers(int originalIndex, const Player& originalPlayer, const Player& newPlayer);

    /**
     * @brief onCurrentPlayerTurn Slot to select a new player
     * @param newPlayerIndex The index of the player to select
     */
    void onCurrentPlayerTurn(int newPlayerIndex);

    /**
     * @brief onStopEverything Hide the player info bar
     */
    void onStopEverything();

private:
    QVector<int> modelToSeat;

    /**
     * @brief seatCount Number of players
     */
    int seatCount = 0;

    /**
     * @brief seatStatus A vector holding all of the player's status'
     */
    QVector<PLAYERSTATUS> seatStatus;

    /**
     * @brief ui The ui of the game
     */
    Ui::MainWindow *ui;

    /**
     * @brief seatLabels A vector holding all of the player labels
     */
    QVector<QLabel*> seatLabels;

    /**
     * @brief buildLayout Builds the layout and adds the labels to it
     * @param seats The number of player labels to create
     */
    void buildLayout(int seats);

    /**
     * @brief rebuildMapping Rebuilds the labels to correctly correspond to a player after splitting
     */
    void rebuildMapping();

    /**
     * @brief insertSplitMapping Inserts a new player into the modelToSeat to get the proper label index after a split
     * @param modelIndex
     */
    void insertSplitMapping(int modelIndex);

    /**
     * @brief refreshSeat Refreshes the label for the player at the given seat
     * @param seat
     * @param player
     */
    void refreshSeat(int seat, const Player& player);

    /**
     * @brief paintBorder Paints the border around a label to the given status
     * @param label The label to paint
     * @param status The status to paint the border
     */
    void paintBorder(QLabel *label, PLAYERSTATUS status);

    /**
     * @brief setSeatText Sets the text for the label at the given seat
     * @param seat The seat to update
     * @param money The money the label should display
     * @param bet The bet the label should display
     */
    void setSeatText(int seat, int money, int bet, PLAYERSTATUS status);

    /**
     * @brief getStatusColor Gets the QString representation of the player status
     * @param status An enum state of the players status
     * @return A QString of a hexidecimal color
     */
    QString getStatusColor(PLAYERSTATUS status);
};

#endif // PLAYERINFOVIEW_H
