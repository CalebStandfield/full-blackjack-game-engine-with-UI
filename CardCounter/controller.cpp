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
    checkTurnEnd(player);
}

void Controller::onSplit()
{
    const Player& player = model->getPlayer(currentPlayerIndex);
    if(player.money < player.hand.getBet() || !botStrategy->isPair(player.hand)){
        return;
    }
    model->split(currentPlayerIndex);

    emit splitPlayers(currentPlayerIndex, model->getPlayer(currentPlayerIndex), model->getPlayer(currentPlayerIndex + 1));
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
    while(currentPlayerIndex < model->getPlayerCount() && (model->getPlayer(currentPlayerIndex).status == PLAYERSTATUS::BANKRUPT
                                                            || model->getPlayer(currentPlayerIndex).status == PLAYERSTATUS::STAND))
    {
        currentPlayerIndex++;
    }

    // All players have went, dealer turn
    if(currentPlayerIndex >= model->getPlayerCount() || model->getDealerHand().getTotal() == 21) {
        model->dealerPlay();
        emit showDealerCard(true);
        emit dealerUpdated(model->getDealerHand(), model->getDealerHand().getTotal());
        return;
    }

    // Switch to next player
    const Player& player = model->getPlayer(currentPlayerIndex);
    emit currentPlayerTurn(currentPlayerIndex, player.money, player.hand.getBet());
    model->setPlayerActive(currentPlayerIndex);

    if(!player.isUser)
         botMove();
}

void Controller::onDealerDonePlaying()
{
    model->endRound();
    emit endRound(model->getAllPlayers());

    for(int i = 0; i < model->getPlayerCount(); i++){
        if(model->getPlayer(i).isUser && model->getPlayer(i).status != PLAYERSTATUS::BANKRUPT)
            return;
    }
    emit gameOver();
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
    // Tell the view the player bet and change their status
    if(currentPlayerIndex >= 0)
    {
        const Player& betPlayer = model->getPlayer(currentPlayerIndex);
        emit playerUpdated(currentPlayerIndex, betPlayer.hand, betPlayer.hand.getTotal(), betPlayer.money, betPlayer.status);
    }

    currentPlayerIndex++;

    // Skip all bankrupt players
    while(currentPlayerIndex < model->getPlayerCount() && model->getPlayer(currentPlayerIndex).status == PLAYERSTATUS::BANKRUPT)
    {
        currentPlayerIndex++;
    }

    // Check if everyone has bet
    if(currentPlayerIndex == model->getPlayerCount())
    {
        emit endBetting();
        dealCards();
        return;
    }

    const Player& player = model->getPlayer(currentPlayerIndex);
    emit currentPlayerTurn(currentPlayerIndex, player.money, player.hand.getBet());

    if(!player.isUser)
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
    // Get the correct MOVE
    const Player& player = model->getPlayer(currentPlayerIndex);
    MOVE move = botStrategy->getNextMove(player.hand, model->getDealerHand().getCards()[1]);

    unsigned int waitTime = 1000;

    // Call the correct MOVE
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
    timer->scheduleSingleShot(500, [=]() {
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
