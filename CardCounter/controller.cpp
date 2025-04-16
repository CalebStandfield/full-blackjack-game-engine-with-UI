#include "controller.h"
#include "qdebug.h"
#include "statistics.h"
#include <QTimer>

Controller::Controller(QObject *parent) : QObject{parent}
{
    botStrategy = new BotStrategy();
    timer = new TimerManager();
}

Controller::~Controller()
{
    delete model;
    delete botStrategy;
    delete timer;
}

void Controller::checkTurnEnd(const Player& player){
    emit playerUpdated(currentPlayerIndex, player.hand, player.hand.getTotal(), player.money, player.status);
    if(player.status == PLAYERSTATUS::BUST || player.status == PLAYERSTATUS::STAND){
        emit playerUpdated(currentPlayerIndex, player.hand, player.hand.getTotal(), player.money, player.status);
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
    if(currentPlayerIndex >= model->getPlayerCount() || model->getDealerHand().getTotal() == 21) {
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

    if(!player.isUser)
         botMove();
}

void Controller::startBetting()
{
    currentPlayerIndex = -1;
    emit showDealerCard(false);
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

    emit updateAllPlayers(model->getAllPlayers());
    emit showDealerCard(false);
    emit dealerUpdated(model->getDealerHand(), model->getDealerHand().getTotal());
}

void Controller::onDealingAnimationComplete()
{
    advanceToNextPlayer();
}

void Controller::botMove()
{
    const Player& player = model->getPlayer(currentPlayerIndex);
    MOVE move = botStrategy->getNextMove(player.hand, model->getDealerHand().getCards()[1]);

    unsigned int waitTime = 1000;

    if(move == MOVE::HIT)
        QTimer::singleShot(waitTime, this, [=]() {
            onHit();});
    else if(move == MOVE::DOUBLE)
    {
        // If not enough money to double down, hit instead
        if(player.money < player.hand.getBet()){
            timer->scheduleSingleShot(waitTime, [=]() {
                onHit();});
        }
        else
            timer->scheduleSingleShot(waitTime, [=]() {
                onDoubleDown();});
    }
    else if(move == MOVE::SPLIT)
    {
        // Call onSplit once implemented
        timer->scheduleSingleShot(waitTime, [=]() {
            onHit();});
    }
    else
        timer->scheduleSingleShot(waitTime, [=]() {
            onStand();});
}

void Controller::botBet()
{
    const Player& player = model->getPlayer(currentPlayerIndex);
    int bet = std::max(player.money / 10, 1);
    timer->scheduleSingleShot(100, [=]() {
        onBet(bet);});
}

void Controller::createNewGame(std::vector<Player> players, int decks, int deterministic)
{
    if(model != nullptr)
        delete model;
    timer->cancelAllTimers();
    model = new GameState(players, decks, deterministic);
}

void Controller::onStopEverything()
{
    timer->cancelAllTimers();
}
