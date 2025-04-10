#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include "player.h"
#include "deck.h"

class GameState
{
public:
    /**
     * @brief Constructs the GameState with a given number of players, a certain number of decks, and an initial bet for each player
     * @param playerCount The number of players in the game
     * @param deckCount The number of decks to use
     * @param initialBet The initialBet for all players
     * @param initialMoney The initialMoney for all players
     */
    GameState(int playerCount, int deckCount = 1, int initialBet = 10, int initialMoney = 100);

    /**
     * @brief dealInitialCards Deals two cards to each player and two to the dealer
     */
    void dealInitialCards();

    /**
     * @brief hit Deals a single card to the specified player, checks for bust
     * @param playerIndex The index of the current player
     */
    void hit(int playerIndex);

    /**
     * @brief doubleDown Double bet for the specified player, deal one card, check bust
     * @param playerIndex The index of the current player
     */
    void doubleDown(int playerIndex);

    /**
     * @brief stand The player stands
     * @param playerIndex The index of the current player
     */
    void stand(int playerIndex);

    /**
     * @brief dealerPlay Dealer draws cards until total >= 17 or bust
     */
    void dealerPlay();

    /**
     * @brief endRound Compare each player's total to the dealer's total, pay winners, take bets from losers, then remove bankrupt players
     */
    void endRound();

    /**
     * @brief isBust Checks if a hand is over 21
     * @param hand The hand to check
     */
    bool isBust(const Hand& hand) const;

    /**
     * @brief getPlayerCount Gets how many players are active in the game
     */
    int getPlayerCount() const;

    /**
     * @brief getPlayer Gets a player's current hand
     * @param index The current player's index
     */
    const Player& getPlayer(int index) const;

    /**
     * @brief getDealerHand Gets the dealer's current hand
     */
    const Hand& getDealerHand() const;

    /**
     * @brief setPlayerActive Sets the player at given index to ACTIVE
     * @param index The player to set to ACTIVE
     */
    void setPlayerActive(int index);

private:
    /**
     * @brief players The players in the game
     */
    std::vector<Player> players;

    /**
     * @brief deck The deck for the game
     */
    Deck deck;

    /**
     * @brief dealerHand The dealer's hand
     */
    Hand dealerHand;

    /**
     * @brief dealerFinished True if the dealer has done their turn, false otherwise
     */
    bool dealerFinished = false;
};

#endif // GAMESTATE_H
