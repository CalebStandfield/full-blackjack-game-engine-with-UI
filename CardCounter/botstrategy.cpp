#include "botstrategy.h"
#include "qdebug.h"
#include "statistics.h"
#include "rank.h"

BotStrategy::BotStrategy() {}

MOVE BotStrategy::getNextMove(const Hand &playerHand, const Card &dealerCard)
{
    // Check for a pair, only valid for 2 cards
    if (isPair(playerHand))
        return getPairHandMove(playerHand, dealerCard);

    // Check for soft hand
    if (playerHand.isSoft())
        return getSoftHandMove(playerHand, dealerCard);

    // Treat as a hard hand
    return getHardHandMove(playerHand, dealerCard);
}

MOVE BotStrategy::getHardHandMove(const Hand& playerHand, const Card& dealerCard)
{
    int row = playerHand.getTotal() - 5;

    // qDebug() << "Hard Hand";
    // qDebug() << "Hand Total: " << playerHand.getTotal();
    // qDebug() << "Dealer Card: " << Rank::toString(dealerCard.getRank());
    // MOVE move = Statistics::HardTable[row][cardToIndex(dealerCard)];
    // std::string str;
    // switch (move)
    // {
    // case MOVE::HIT:
    //     str = "Hit";
    //     break;
    // case MOVE::DOUBLE:
    //     str = "Double";
    //     break;
    // case MOVE::SPLIT:
    //     str = "Split";
    //     break;
    // case MOVE::STAND:
    //     str = "Stand";
    //     break;
    // }
    // qDebug() << "MOVE: " << str;

    return Statistics::HardTable[row][cardToIndex(dealerCard)];
}

MOVE BotStrategy::getSoftHandMove(const Hand& playerHand, const Card& dealerCard)
{
    int effective = playerHand.getTotal() - 11;
    int row = effective - 2;

    // qDebug() << "Soft Hand";
    // qDebug() << "Soft Total: " << playerHand.getTotal();
    // qDebug() << "Dealer Card: " << toString(dealerCard.getRank());
    // MOVE move = Statistics::SoftTable[row][cardToIndex(dealerCard)];
    // std::string str;
    // switch (move)
    // {
    // case MOVE::HIT:
    //     str = "Hit";
    //     break;
    // case MOVE::DOUBLE:
    //     str = "Double";
    //     break;
    // case MOVE::SPLIT:
    //     str = "Split";
    //     break;
    // case MOVE::STAND:
    //     str = "Stand";
    //     break;
    // }
    // qDebug() << "MOVE: " << str;
    return Statistics::SoftTable[row][cardToIndex(dealerCard)];
}

MOVE BotStrategy::getPairHandMove(const Hand& playerHand, const Card& dealerCard)
{
    int row = cardToIndex(playerHand.getCards()[0]);
    return Statistics::PairTable[row][cardToIndex(dealerCard)];
}

bool BotStrategy::isPair(const Hand &hand)
{
    const std::vector<Card>& cards = hand.getCards();
    if (cards.size() != 2)
        return false;
    return (cards[0].getRank() == cards[1].getRank());
}

int BotStrategy::cardToIndex(const Card &card)
{
    return Rank::blackjackValue(card.getRank()) - 2;
}
