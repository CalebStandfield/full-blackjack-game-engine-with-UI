#ifndef CARD_H
#define CARD_H

#include "suits.h"
#include "rank.h"

using Rank::RANK;
using Suit::SUIT;

class Card
{
    /**
     * @brief operator << Prints out the rank and suit of the card as "Rank of Suit"
     * @param os The stream to add the string to
     * @param card The card to print out
     * @return A string represenation of the card
     */
    friend std::ostream& operator<<(std::ostream& os, const Card& card);

    //friend std::string toString(const Card& card);
public:
    /**
     * @brief Card Constructor which sets the rank and suit of the card
     * @param suit The suit of the card
     * @param rank The rank of the card
     */
    Card(SUIT suit, RANK rank);

    /**
     * @brief getSuit Gets the suit of the card
     * @return Returns the suit of the card as a SUIT
     */
    SUIT getSuit() const;

    /**
     * @brief getRank Gets the rank of the card
     * @return Returns the rank of the card as a RANK
     */
    RANK getRank() const;

    /**
     * @brief toString Gives the string output of this card as Rank of Suit
     * @return "Rank of Suit"
     */
    std::string toString();

private:
    /**
     * @brief suit The suit of the card
     */
    SUIT suit;

    /**
     * @brief rank The rank of the card
     */
    RANK rank;
};

#endif // CARD_H
