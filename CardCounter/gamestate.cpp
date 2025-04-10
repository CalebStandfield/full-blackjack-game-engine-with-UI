#include "gamestate.h"
#include "playerStatus.h"

using PlayerStatus::PLAYERSTATUS;

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
    deck.shuffle();
    dealerHand = Hand(0);
    dealerFinished = false;

    // Reset player's hand
    for(Player& player : players)
        player.hand = Hand(player.hand.getBet());

    // Deal 2 cards to each player and set their status to waiting
    for(int i = 0; i < 2; i++)
    {
        for(Player& player : players)
        {
            player.hand.addCard(deck.getNextCard());
        }

        dealerHand.addCard(deck.getNextCard());
    }
}

void GameState::hit(int playerIndex)
{
    Player &currPlayer = players[playerIndex];
    currPlayer.status = PLAYERSTATUS::ACTIVE;
    currPlayer.hand.addCard(deck.getNextCard());
    if(isBust(currPlayer.hand)){
        currPlayer.status = PLAYERSTATUS::BUST;
    }
}

void GameState::doubleDown(int playerIndex)
{
    Player &currPlayer = players[playerIndex];
    int currentBet = currPlayer.hand.getBet();
    currPlayer.money -= currentBet;
    currPlayer.hand.setBet(currentBet * 2);
    currPlayer.hand.addCard(deck.getNextCard());
    currPlayer.status = PLAYERSTATUS::STAND;
    if(isBust(currPlayer.hand)){
        currPlayer.status = PLAYERSTATUS::BUST;
    }
}

void GameState::stand(int playerIndex)
{
    Player &currPlayer = players[playerIndex];
    currPlayer.status = PLAYERSTATUS::STAND;
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
            continue;

        int playerTotal = player.hand.getTotal();
        if(dealerBust || playerTotal > dealerTotal)
        {
            // If player gets blackjack, player gets 1.5 times their bet
            if(playerTotal == 21)
                player.money += player.hand.getBet() * 2.5;
            // Else, player doubles their bet
            else
                player.money += player.hand.getBet() * 2;
        }
        else if(playerTotal == dealerTotal)
            player.money += player.hand.getBet();
    }
}

void GameState::setPlayerActive(int index)
{
    players[index].status = PLAYERSTATUS::ACTIVE;
}

const Player& GameState::getPlayer(int index) const
{
    return players.at(index);
}

// int GameState::getPlayerMoney(int index) const
// {
//     return players.at(index).money;
// }

const Hand& GameState::getDealerHand() const
{
    return dealerHand;
}

int GameState::getPlayerCount() const
{
    return static_cast<int>(players.size());
}


