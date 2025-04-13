#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "gamestate.h"
#include "hand.h"
#include "playerStatus.h"
#include "botstrategy.h"

using PlayerStatus::PLAYERSTATUS;

class Controller : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Controller Constructor that creates a new controller to the the blackjack game
     * @param parent
     */
    explicit Controller(QObject *parent = nullptr);

    /**
     * @brief Controller Destructor for Controller class
     * @param
     */
    ~Controller();

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
     * @brief startRound The next round of betting starts
     */
    void startBetting();

    /**
     * @brief dealCards Deals out the initial cards and moves to the first player's turn
     */
    void dealCards();

    /**
     * @brief onBet The current player sends in there bet
     * @param bet The bet of the player
     */
    void onBet(int bet);

    /**
     * @brief createNewGame Create a new gamestate and initalizes blackjack with the set players with the given amount of money
     * @param players The number of players in the game
     * @param decks The number of decks to play with
     */
    void createNewGame(std::vector<Player>& players, int decks);
signals:
    /**
     * @brief playerUpdated Signal that a player in the game has updated with their updated info
     * @param playerIndex The player that has updated
     * @param hand The new hand for the player
     * @param total The total value of their cards
     * @param money The money they have left
     * @param status The status of the player
     */
    void playerUpdated(int playerIndex, const Hand& hand, int total, int money, PLAYERSTATUS status);

    /**
     * @brief dealerUpdated Signal that the dealer has updated with their updated info
     * @param hand The new hand of the dealer
     * @param total The total value of their cards
     */
    void dealerUpdated(const Hand& hand, int total);

    /**
     * @brief currentPlayerTurn Signal that it is the next player's turn
     * @param nextPlayerIndex The index of the next player that is up now
     */
    void currentPlayerTurn(int nextPlayerIndex);

    /**
     * @brief endRound Signal that the round has ended
     * @param roundSummary A brief summary of the round to display
     */
    void endRound(QString roundSummary);

    /**
     * @brief gameMessage Signal to send a game message (ex. player 0 has busted)
     * @param message The message to display
     */
    void gameMessage(QString message);

    /**
     * @brief gameOver Signal for the game to be over
     */
    void gameOver();

    /**
     * @brief endBetting Signal for the betting phase to be over
     */
    void endBetting();

private:
    /**
     * @brief model The Gamestate model that handles the players playing blackjack
     */
    GameState *model = nullptr;

    /**
     * @brief botPlayer The BotStrategy that determines the bot's move
     */
    BotStrategy* botStrategy;

    /**
     * @brief currentPlayerIndex The index of the current player in the round
     */
    int currentPlayerIndex;

    /**
     * @brief advanceToNextPlayer Move to the next player's turn
     */
    void advanceToNextPlayer();

    /**
     * @brief advanceToNextBet Move to the next player's turn in betting
     */
    void advanceToNextBet();

    /**
     * @brief checkTurnEnd
     */
    void checkTurnEnd(const Player& player);

    /**
     * @brief botMove Performs a move for a bot player
     */
    void botMove();

    /**
     * @brief botBet Performs a bet for a bot player
     */
    void botBet();
};

#endif // CONTROLLER_H
