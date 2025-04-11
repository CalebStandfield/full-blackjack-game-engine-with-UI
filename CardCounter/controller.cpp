#include "controller.h"

Controller::Controller(QObject *parent) : QObject{parent}{}

Controller::~Controller()
{
    delete model;
}

void Controller::checkTurnEnd(const Player& player){
    emit playerUpdated(currentPlayerIndex, player.hand, player.hand.getTotal(), player.money, player.status);
    if(player.status == PLAYERSTATUS::BUST || player.status == PLAYERSTATUS::STAND){
        advanceToNextPlayer();
    }
}

void Controller::onHit()
{
    model->hit(currentPlayerIndex);
    checkTurnEnd(model->getPlayer(currentPlayerIndex));
}

void Controller::onStand()
{
    model->stand(currentPlayerIndex);
    checkTurnEnd(model->getPlayer(currentPlayerIndex));
}

void Controller::onDoubleDown()
{
    const Player& player = model->getPlayer(currentPlayerIndex);
    if(player.money < player.hand.getBet() * 2){
        return;
    }
    model->doubleDown(currentPlayerIndex);
    checkTurnEnd(model->getPlayer(currentPlayerIndex));
}

void Controller::onBet(int bet)
{
    model->setPlayerBet(currentPlayerIndex, bet);
    advanceToNextBet();
}

void Controller::advanceToNextPlayer()
{
    currentPlayerIndex++;
    while(currentPlayerIndex < model->getPlayerCount() && model->getPlayer(currentPlayerIndex).status == PLAYERSTATUS::BANKRUPT)
    {
        currentPlayerIndex++;
    }

    // All players have went, dealer turn
    if(currentPlayerIndex == model->getPlayerCount()){
        model->dealerPlay();
        emit dealerUpdated(model->getDealerHand(), model->getDealerHand().getTotal());
        model->endRound();
        emit endRound("The round has ended.");

        for(int i = 0; i < model->getPlayerCount(); i++){
            if(model->getPlayer(i).isUser && model->getPlayer(i).status != PLAYERSTATUS::BANKRUPT)
                return;
        }
        emit gameOver();
    }

    // Switch to next player
    emit nextPlayerTurn(currentPlayerIndex);
    model->setPlayerActive(currentPlayerIndex);
    const Player& player = model->getPlayer(currentPlayerIndex);
    emit playerUpdated(currentPlayerIndex, player.hand, player.hand.getTotal(), player.money, player.status);

    // if(!player.isUser)
    //     botMove();
}

void Controller::startBetting()
{
    currentPlayerIndex = -1;
    advanceToNextBet();
}

void Controller::advanceToNextBet()
{
    currentPlayerIndex++;
    if(currentPlayerIndex == model->getPlayerCount()){
        emit endBetting();
        dealCards();
        return;
    }

    // if(!model->getPlayer(currentPlayerIndex).isUser)
    //     botBet();
    emit nextPlayerTurn(currentPlayerIndex);
}

void Controller::dealCards()
{
    model->dealInitialCards();
    model->setPlayerActive(currentPlayerIndex);
    const Player& player = model->getPlayer(currentPlayerIndex);
    emit playerUpdated(currentPlayerIndex, player.hand, player.hand.getTotal(), player.money, player.status);
    emit dealerUpdated(model->getDealerHand(), model->getDealerHand().getTotal());
}

void Controller::createNewGame(int players, int decks, int initialMoney, int userIndex)
{
    model = new GameState(players, decks, initialMoney, userIndex);
}
