#ifndef CARD_H
#define CARD_H

#include "suit.h"

class Card
{
public:
    /**
     * @brief Card Constructor which sets the value and suit of the card
     * @param value The number of the card
     * @param suit The suit of the card
     */
    Card(int value, SUIT suit);

    /**
     * @brief getValue Gets the value of the card
     * @return Returns the value of the card as an int
     */
    int getValue();

    /**
     * @brief getSuit Gets the suit of the card
     * @return Returns the suit of the card as a SUIT
     */
    SUIT getSuit();

private:
    /**
     * @brief value The value of the card
     */
    int value;

    /**
     * @brief suit The suit of the card
     */
    SUIT suit;
};

#endif // CARD_H
