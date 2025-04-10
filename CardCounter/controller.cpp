#include "controller.h"

Controller::Controller(QObject *parent) : QObject{parent}
{
    model = new GameState(1);
    // display characters, then call "start new round"
    // players start from left of dealer (i.e. right to left) (what order to make players?)
}

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

void Controller::advanceToNextPlayer()
{
    currentPlayerIndex++;
    if(currentPlayerIndex == model->getPlayerCount()){
        model->dealerPlay();
        emit dealerUpdated(model->getDealerHand(), model->getDealerHand().getTotal());
        model->endRound();
        emit endRound("The round has ended.");
        return;
    }
    emit nextPlayerTurn(currentPlayerIndex);
    model->setPlayerActive(currentPlayerIndex);
    const Player& player = model->getPlayer(currentPlayerIndex);
    emit playerUpdated(currentPlayerIndex, player.hand, player.hand.getTotal(), player.money, player.status);
}

void Controller::startRound()
{
    currentPlayerIndex = 0;
    // Players each bet at this point, starting from player index 0

    model->dealInitialCards();
    model->setPlayerActive(currentPlayerIndex);
    const Player& player = model->getPlayer(currentPlayerIndex);
    emit playerUpdated(currentPlayerIndex, player.hand, player.hand.getTotal(), player.money, player.status);
    emit dealerUpdated(model->getDealerHand(), model->getDealerHand().getTotal());

    // check whether current player is an AI or a real player
    // if a real player, send signal to view to activate P1's buttons
    // otherwise, the controller will play as the AI
}
