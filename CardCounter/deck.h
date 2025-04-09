#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>

class Deck
{
public:
    /**
     * @brief Deck The constructor for the deck class
     */
    Deck();

    /**
     * Shuffles the shuffleDeck so it is randomized
     */
    void shuffle();

    /**
     * @brief getNextCard Gets the next card in the shuffled deck and moves the index to the next card
     * @return The next card in the shuffled deck
     */
    Card getNextCard();

private:
    /**
     * @brief masterDeck The master deck holding all 52 cards in order
     */
    std::vector<Card> masterDeck;

    /**
     * @brief shuffledDeck The deck that becomes shuffled to use for getting the next card
     */
    std::vector<Card> shuffledDeck;

    /**
     * @brief shuffledDeckIndex The current index in the shuffled deck
     */
    int shuffledDeckIndex = 0;
};

#endif // DECK_H
