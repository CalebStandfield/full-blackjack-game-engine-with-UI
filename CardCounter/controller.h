#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "gamestate.h"
#include "hand.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

public slots:
    /**
     * @brief onHit The current player chooses to hit
     */
    void onHit();

    /**
     * @brief onStand The current player chooses to stand
     */
    void onStand();

    /**
     * @brief onDoubleDown The currnet player chooses to dobule down
     */
    void onDoubleDown();

    /**
     * @brief startRound The next round starts
     */
    void startRound();
signals:
    /**
     * @brief playerUpdated Signal that a player in the game has updated with their updated info
     * @param playerIndex The player that has updated
     * @param hand The new hand for the player
     * @param total The total value of their cards
     * @param money The money they have left
     * @param status The status of the player (busted or stood)
     */
    void playerUpdated(int playerIndex, const Hand& hand, int total, int money, QString status);

    /**
     * @brief dealerUpdated Signal that the dealer has updated with their updated info
     * @param hand The new hand of the dealer
     * @param total The total value of their cards
     */
    void dealerUpdated(const Hand& hand, int total);

    /**
     * @brief nextPlayerTurn Signal that it is the next player's turn
     * @param nextPlayerIndex The index of the next player that is up now
     */
    void nextPlayerTurn(int nextPlayerIndex);

    /**
     * @brief roundEnded Signal that the round has ended
     * @param roundSummary A brief summary of the round to display
     */
    void roundEnded(QString roundSummary);

    /**
     * @brief gameMessage Signal to send a game message (ex. player 0 has busted)
     * @param message The message to display
     */
    void gameMessage(QString message);

    /**
     * @brief gameOver Signal for the game to be over
     */
    void gameOver();

private:
    /**
     * @brief model The Gamestate model that handles the players playing blackjack
     */
    GameState *model;

    /**
     * @brief currentPlayerIndex The index of the current player in the round
     */
    int currentPlayerIndex;

    /**
     * @brief advanceToNextPlayer Move to the next player's turn
     */
    void advanceToNextPlayer();
};

#endif // CONTROLLER_H
