#include "gamestate.h"
#include "playerStatus.h"

using PlayerStatus::PLAYERSTATUS;

GameState::GameState(std::vector<Player> players, int deckCount, int deterministic) : players(players), deck(deckCount, deterministic), dealerHand(0) {}

void GameState::dealInitialCards()
{
    deck.shuffle();

    // Deal 2 cards to each player and set their status to waiting
    for(int i = 0; i < 2; i++)
    {
        for(Player& player : players)
        {
            if(player.status == PLAYERSTATUS::BANKRUPT)
                continue;

            player.hand.addCard(deck.getNextCard());
            player.status = PLAYERSTATUS::WAITING;
        }

        dealerHand.addCard(deck.getNextCard());
    }
}

void GameState::clearHands()
{
    dealerHand = Hand(0);
    dealerFinished = false;

    // Reset player's hand
    for(Player& player : players)
        player.hand = Hand(player.hand.getBet());
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

    // Move the doubled money from the player's money to their current bet
    int currentBet = currPlayer.hand.getBet();
    currPlayer.money -= currentBet;
    currPlayer.hand.setBet(currentBet * 2);

    // Do one hit and then stand/check bust
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
        if(player.status == PLAYERSTATUS::BUST)
        {
            if(player.money <= 0)
                player.status = PLAYERSTATUS::BANKRUPT;
            continue;
        }

        int playerTotal = player.hand.getTotal();
        if(dealerBust || playerTotal > dealerTotal)
        {
            // If player gets blackjack, player gets 1.5 times their bet
            if(playerTotal == 21 && player.hand.getCards().size() == 2)
                player.money += player.hand.getBet() * 2.5;
            // Else, player doubles their bet
            else
                player.money += player.hand.getBet() * 2;
        }
        else if(playerTotal == dealerTotal)
            player.money += player.hand.getBet();

        if(player.money <= 0)
            player.status = PLAYERSTATUS::BANKRUPT;
    }
}

void GameState::setPlayerActive(int index)
{
    players[index].status = PLAYERSTATUS::ACTIVE;
}

void GameState::setPlayerBet(int index, int amount)
{
    players[index].money -= amount;
    players[index].hand.setBet(amount);
}

const Player& GameState::getPlayer(int index) const
{
    return players.at(index);
}

const Hand& GameState::getDealerHand() const
{
    return dealerHand;
}

int GameState::getPlayerCount() const
{
    return static_cast<int>(players.size());
}


