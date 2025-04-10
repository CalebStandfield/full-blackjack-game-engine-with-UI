#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"

class Player
{
public:
    /**
     * @brief hand The hand of cards and bet for a players round
     */
    Hand hand;

    /**
     * @brief money The total amount of money a player has
     */
    int money;

    /**
     * @brief isBusted True if the player busted, false otherwise
     */
    bool isBusted = false;

    /**
     * @brief Player Constructor that creates a new player with the given bet and money
     * @param initialMoney The amount of money the player starts with
     * @param initialBet The inital bet for the first round
     */
    Player(int initialMoney, int initialBet): hand(initialBet), money(initialMoney){}
};

#endif // PLAYER_H
