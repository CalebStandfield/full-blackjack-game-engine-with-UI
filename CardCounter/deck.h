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

    /**
     * @brief isEmpty Checks if the there are any more cards left in the shuffled deck
     * @return Returns true if there are no more cards and false if the shuffled deck is not empty
     */
    bool isEmpty() const;

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
    int currentDeckIndex = 0;

    /**
     * @brief createDeck Creates a full 52 card deck in number order. Suit goes
     */
    void createDeck();
};

#endif // DECK_H
