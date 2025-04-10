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
     */
    void hit(int playerIndex);

    /**
     * @brief doubleDown Double bet for the specified player, deal one card, check bust
     */
    void doubleDown(int playerIndex);

    /**
     * @brief stand The player stands
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
     */
    bool isBust(const Hand& hand) const;

    /**
     * @brief getPlayerCount Gets how many players are active in the game
     */
    int getPlayerCount() const;

    /**
     * @brief getPlayerHand Gets a player's current hand
     */
    const Hand& getPlayerHand(int index) const;

    /**
     * @brief getPlayerMoney Get how much money a player has.
     */
    int getPlayerMoney(int index) const;

    /**
     * @brief getDealerHand Gets the dealer's current hand
     */
    const Hand& getDealerHand() const;

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
