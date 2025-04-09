#include "card.h"
#include "suits.h"
#include "rank.h"

Card::Card(SUIT suit, RANK rank) : suit(suit), rank(rank) {}

SUIT Card::getSuit() const
{
    return suit;
}

RANK Card::getRank() const
{
    return rank;
}

void Card::setSuit(SUIT suit)
{
    this->suit = suit;
}

void Card::setRank(RANK rank)
{
    this->rank = rank;
}

std::ostream& operator<<(std::ostream& os, const Card& card)
{
    os << toString(card.rank) << " of " << toString(card.suit);
    return os;
}
