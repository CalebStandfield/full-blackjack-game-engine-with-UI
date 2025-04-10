#include "controller.h"

Controller::Controller(QObject *parent) : QObject{parent}
{
    model = new GameState(1);
}

void Controller::onHit()
{

}

void Controller::onStand()
{

}

void Controller::onDoubleDown()
{

}

void Controller::startRound()
{

}
