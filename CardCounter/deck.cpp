#include "deck.h"
#include "suits.h"
#include "rank.h"
#include <algorithm>
#include <random>

Deck::Deck(int deckNumber, int deterministic) : deterministic(deterministic)
{
    createDeck();

    for(int i = 0; i < deckNumber; i++)
        shuffledDeck.insert(shuffledDeck.end(), masterDeck.begin(), masterDeck.end());

    shuffle();
}

void Deck::createDeck()
{
    masterDeck.reserve(52);
    unsigned int i = 0;

    for (RANK rank : Rank::allRanks)
        for (SUIT suit : Suit::allSuits)
            masterDeck.emplace_back(suit, rank, Card::getImageFromVector(i++));

}

void Deck::shuffle()
{
    if(deterministic == 0)
    {
        std::default_random_engine rand(std::random_device{}());
        std::shuffle(shuffledDeck.begin(), shuffledDeck.end(), rand);
        currentDeckIndex = 0;
    }
    else if(deterministic == 1)
    {
        // Implement determined shuffle for single player
    }
    else
    {
        // Implement determined shuffle for multiple players
    }
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
