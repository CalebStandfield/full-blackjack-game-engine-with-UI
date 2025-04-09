#include "card.h"

Card::Card(int value, SUIT suit) : value(value), suit(suit) {}

int Card::getValue()
{
    return value;
}

SUIT Card::getSuit()
{
    return suit;
}
