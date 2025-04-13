#include "controller.h"
#include "statistics.h"
#include <QTimer>

Controller::Controller(QObject *parent) : QObject{parent}
{
    botStrategy = new BotStrategy();
}

Controller::~Controller()
{
    delete model;
    delete botStrategy;
}

void Controller::checkTurnEnd(const Player& player){
    emit playerUpdated(currentPlayerIndex, player.hand, player.hand.getTotal(), player.money, player.status);
    if(player.status == PLAYERSTATUS::BUST || player.status == PLAYERSTATUS::STAND){
        advanceToNextPlayer();
        return;
    }

    if(!player.isUser)
        botMove();
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
    if(player.money < player.hand.getBet()){
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
    if(currentPlayerIndex >= model->getPlayerCount()){
        model->dealerPlay();
        emit showDealerCard(true);
        emit dealerUpdated(model->getDealerHand(), model->getDealerHand().getTotal());
        model->endRound();
        emit endRound("The round has ended.");

        for(int i = 0; i < model->getPlayerCount(); i++){
            if(model->getPlayer(i).isUser && model->getPlayer(i).status != PLAYERSTATUS::BANKRUPT)
                return;
        }
        emit gameOver();
        return;
    }

    // Switch to next player
    emit currentPlayerTurn(currentPlayerIndex);
    model->setPlayerActive(currentPlayerIndex);

    const Player& player = model->getPlayer(currentPlayerIndex);
    // emit playerUpdated(currentPlayerIndex, player.hand, player.hand.getTotal(), player.money, player.status);

    if(!player.isUser)
         botMove();
}

void Controller::startBetting()
{
    currentPlayerIndex = -1;

    // Clear all hands and update view
    model->clearHands();
    for(int i = 0; i < model->getPlayerCount(); i++){
        const Player& player = model->getPlayer(i);
        emit playerUpdated(i, player.hand, player.hand.getTotal(), player.money, player.status);
    }
    emit dealerUpdated(model->getDealerHand(), model->getDealerHand().getTotal());

    advanceToNextBet();
}

void Controller::advanceToNextBet()
{
    currentPlayerIndex++;
    if(currentPlayerIndex == model->getPlayerCount())
    {
        emit endBetting();
        dealCards();
        return;
    }

    emit currentPlayerTurn(currentPlayerIndex);

    if(!(model->getPlayer(currentPlayerIndex).isUser))
         botBet();

}

void Controller::dealCards()
{
    currentPlayerIndex =  -1;
    model->dealInitialCards();

    for(int i = 0; i < model->getPlayerCount(); i++){
        const Player& player = model->getPlayer(i);
        emit playerUpdated(i, player.hand, player.hand.getTotal(), player.money, player.status);
    }

    emit showDealerCard(false);
    emit dealerUpdated(model->getDealerHand(), model->getDealerHand().getTotal());

    if(model->getDealerHand().getTotal() == 21) {
        currentPlayerIndex = model->getPlayerCount();
    }

    advanceToNextPlayer();
}

void Controller::botMove()
{
    const Player& player = model->getPlayer(currentPlayerIndex);
    MOVE move = botStrategy->getNextMove(player.hand, model->getDealerHand().getCards()[1]);

    unsigned int waitTime = 500;

    if(move == MOVE::HIT)
        QTimer::singleShot(waitTime, this, [=]() {
            onHit();});
    else if(move == MOVE::DOUBLE)
    {
        // If not enough money to double down, hit instead
        if(player.money < player.hand.getBet()){
            QTimer::singleShot(waitTime, this, [=]() {
                onHit();});
        }
        else
            QTimer::singleShot(waitTime, this, [=]() {
                onDoubleDown();});
    }
    else if(move == MOVE::SPLIT)
    {
        // Call onSplit once implemented
        QTimer::singleShot(waitTime, this, [=]() {
            onHit();});
    }
    else
        QTimer::singleShot(waitTime, this, [=]() {
            onStand();});
}

void Controller::botBet()
{
    const Player& player = model->getPlayer(currentPlayerIndex);
    int bet = std::max(player.money / 10, 1);    
    QTimer::singleShot(100, this, [=]() {
        onBet(bet);});
}

void Controller::createNewGame(std::vector<Player> players, int decks, int deterministic)
{
    if(model != nullptr)
        delete model;

    model = new GameState(players, decks, deterministic);
}
