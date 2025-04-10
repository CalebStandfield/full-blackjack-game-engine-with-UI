#include "hand.h"
#include "rank.h"

Hand::Hand(int bet): bet(bet) {}

void Hand::addCard(const Card& card)
{
    cards.push_back(card);
}

int Hand::getBet() const
{
    return bet;
}

void Hand::setBet(int amount)
{
    bet = amount;
}

int Hand::getTotal() const
{
    int total = 0;
    int aceCount = 0;

    for (const Card& card : cards)
    {
        int value = Rank::blackjackValue(card.getRank());
        if (value == 11)
            aceCount++;

        total += value;
    }

    // Adjust ace value to 1 if would bust with value 11
    while (total > 21 && aceCount > 0) {
        total -= 10;
        aceCount--;
    }

    return total;
}
