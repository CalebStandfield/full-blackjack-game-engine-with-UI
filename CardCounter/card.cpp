#include "card.h"
#include "suits.h"
#include "rank.h"

Card::Card(SUIT suit, RANK rank) : suit(suit), rank(rank) {}

SUIT Card::getSuit() const
{
    return suit;
}

Rank::RANK Card::getRank() const
{
    return rank;
}

std::string Card::toString()
{
    return Rank::toString(rank) + " of " + Suit::toString(suit);
}

std::ostream& operator<<(std::ostream& os, const Card& card)
{
    os << toString(card.rank) << " of " << toString(card.suit);
    return os;
}
