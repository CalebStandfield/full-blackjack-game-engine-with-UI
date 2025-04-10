#include "gamestate.h"

GameState::GameState(int playerCount, int deckCount, int initialBet, int initialMoney)
    : deck(deckCount), dealerHand(0)
{
    // Adds players with default money and bets to the players vector
    for(int i = 0; i < playerCount; i++)
    {
        players.emplace_back(initialMoney, initialBet);
    }
}

void GameState::dealInitialCards()
{
    dealerHand = Hand(0);
    dealerFinished = false;

    // Deal 2 cards to each player and set their status to waiting
    for(Player& player : players)
    {
        player.hand = Hand(player.hand.getBet());
        player.hand.addCard(deck.getNextCard());
        player.hand.addCard(deck.getNextCard());
    }

    dealerHand.addCard(deck.getNextCard());
    dealerHand.addCard(deck.getNextCard());
}

void GameState::hit(int playerIndex)
{
    players[playerIndex].hand.addCard(deck.getNextCard());
}

void GameState::doubleDown(int playerIndex)
{
    int currentBet = players[playerIndex].hand.getBet();
    players[playerIndex].hand.setBet(currentBet * 2);
    players[playerIndex].hand.addCard(deck.getNextCard());
}

void GameState::stand(int playerIndex)
{

}

void GameState::dealerPlay()
{
    while (dealerHand.getTotal() < 17)
        dealerHand.addCard(deck.getNextCard());
    dealerFinished = true;
}

bool GameState::isBust(const Hand& hand) const
{
    return hand.getTotal() > 21;
}

void GameState::endRound()
{
    int dealerTotal = dealerHand.getTotal();
    bool dealerBust = isBust(dealerHand);

    for(Player& player : players)
    {
        if(isBust(player.hand))
            player.money -= player.hand.getBet();

        else
        {
            int playerTotal = player.hand.getTotal();
            if(dealerBust)
            {
                // If player gets blackjack, player gets 1.5 times there bet
                if(playerTotal == 21)
                    player.money += player.hand.getBet() * 2.5;
                // Else, player doubles their bet
                else
                    player.money += player.hand.getBet() * 2;
            }
            else if(playerTotal > dealerTotal)
            {
                // If player gets blackjack, player gets 1.5 times there bet
                if(playerTotal == 21)
                    player.money += player.hand.getBet() * 2.5;
                // Else, player doubles their bet
                else
                    player.money += player.hand.getBet() * 2;
            }
            else if(playerTotal < dealerTotal)
                player.money -= player.hand.getBet();
        }
    }
}

const Hand& GameState::getPlayerHand(int index) const
{
    return players.at(index).hand;
}

int GameState::getPlayerMoney(int index) const
{
    return players.at(index).money;
}

const Hand& GameState::getDealerHand() const
{
    return dealerHand;
}

int GameState::getPlayerCount() const
{
    return static_cast<int>(players.size());
}


