#include "deck.h"
#include "suits.h"
#include "rank.h"
#include <algorithm>
#include <random>

Deck::Deck()
{
    createDeck();
    shuffledDeck = masterDeck;
}

void Deck::createDeck()
{
    masterDeck.reserve(52);

    for (RANK rank : allRanks)
        for (SUIT suit : allSuits)
            masterDeck.emplace_back(suit, rank);
}

void Deck::shuffle()
{
    std::default_random_engine rand(std::random_device{}());
    std::shuffle(shuffledDeck.begin(), shuffledDeck.end(), rand);
    currentDeckIndex = 0;
}

Card Deck::getNextCard()
{
    if (isEmpty())
        throw std::out_of_range("No more cards in the deck");

    return shuffledDeck[currentDeckIndex++];
}

bool Deck::isEmpty() const {
    return currentDeckIndex >= static_cast<int>(shuffledDeck.size());
}
