#include "controller.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{
    model = new GameState(1);
}
