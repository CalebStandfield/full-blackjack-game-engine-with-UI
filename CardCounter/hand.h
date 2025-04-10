#ifndef HAND_H
#define HAND_H

#include <vector>
#include "card.h"

class Hand
{
public:
    /**
     * @brief Hand Constructor that creates a new empty hand with the initial bet
     * @param bet The initial bet for the hand
     */
    Hand(int bet);

    /**
     * @brief addCard Adds a card to the hand
     * @param card The card to add
     */
    void addCard(const Card& card);

    /**
     * @brief getTotal Gets the total blackjack value of the hand
     * @return Returns an int of the value of the hand
     */
    int getTotal() const;

    /**
     * @brief getBet Gets the current ammount bet
     * @return Returns an int of the bet
     */
    int getBet() const;

    /**
     * @brief setBet Sets the bet to the given amount
     * @param amount The amount to set the bet at
     */
    void setBet(int amount);

private:
    /**
     * @brief cards The cards in the hand
     */
    std::vector<Card> cards;

    /**
     * @brief bet The amount bet on this hand
     */
    int bet;
};

#endif // HAND_H
