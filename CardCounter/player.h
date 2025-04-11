#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"
#include "playerStatus.h"

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
     * @brief isUser True if the player is a user, false otherwise
     */
    bool isUser;

    /**
     * @brief status Stores the current status of the player
     */
    PlayerStatus::PLAYERSTATUS status = PlayerStatus::PLAYERSTATUS::WAITING;

    /**
     * @brief Player Constructor that creates a new player with the given bet and money
     * @param initialMoney The amount of money the player starts with
     * @param initialBet The inital bet for the first round
     * @param isUser True is the player is a user, false if they are a bot
     */
    Player(int initialMoney, int initialBet, bool isUser): hand(initialBet), money(initialMoney), isUser(isUser){}
};

#endif // PLAYER_H
