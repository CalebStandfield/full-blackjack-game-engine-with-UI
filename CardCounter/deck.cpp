#include "deck.h"
#include "suits.h"
#include "rank.h"
#include <algorithm>
#include <random>

Deck::Deck(int deckNumber)
{
    createDeck();

    for(int i = 0; i < deckNumber; i++) {
        shuffledDeck.insert(shuffledDeck.end(), masterDeck.begin(), masterDeck.end());
    }
    shuffle();
}

void Deck::createDeck()
{
    masterDeck.reserve(52);

    for (RANK rank : Rank::allRanks)
        for (SUIT suit : Suit::allSuits)
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
    if (currentDeckIndex > (shuffledDeck.size() * 0.8))
    {
        shuffle();
        currentDeckIndex = 0;
    }

    return shuffledDeck[currentDeckIndex++];
}

bool Deck::isEmpty() const {
    return currentDeckIndex >= static_cast<int>(shuffledDeck.size());
}
