#ifndef BOTSTRATEGY_H
#define BOTSTRATEGY_H

#include "hand.h"
#include "card.h"
#include <QString>

class BotStrategy
{
public:
    BotStrategy();

    /**
     * @brief getNextMove Determines the recommended move (hit, double, split, or stand) given a player's hand and the dealer's visible card.
     * @param playerHand The player's hand.
     * @param dealerCard The dealer's up card.
     * @return A QString corresponding to the recommended move (e.g., "H", "D", "SP", "ST").
     */
    QString getNextMove(const Hand& playerHand, const Card& dealerCard);

private:
    /**
     * @brief cardToIndex Converts the current card to an index for a table by subtracting 2
     * @param card The card to convert
     * @return Returns the int value for the index of the card
     */
    int cardToIndex(const Card& card);

    /**
     * @brief isPair Checks if the hand is a pair (2 of the same card)
     * @param hand The hand to check
     * @return True if the hand is a pair, false if it is not
     */
    bool isPair(const Hand& hand);

    QString getSoftHandMove(const Hand& playerHand, const Card& dealerCard);
    QString getHardHandMove(const Hand& playerHand, const Card& dealerCard);
    QString getPairHandMove(const Hand& playerHand, const Card& dealerCard);

};

#endif // BOTSTRATEGY_H
