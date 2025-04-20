#include "tutorialpopup.h"

TutorialPopup::TutorialPopup(Ui::MainWindow* ui, QObject *parent) : QObject(parent), ui(ui)
{
    popupMessages->reserve(26);
    createMessages();
}

void TutorialPopup::createMessages()
{
    const std::initializer_list<QString> tutorialMessages = {
        "firstMessage", // Add messages in order here
        "secondMessage",
    };

    for(const QString& message : tutorialMessages)
    {
        popupMessages->push_back(message);
    }
    messageIndex = 0;
}

void TutorialPopup::toggleVisableTutorialPopup(bool show)
{
    if (show)
    {
        ui->tutorialWidget->show();
    }
    else
    {
        ui->tutorialWidget->hide();
    }
}

void TutorialPopup::onContinuePressed()
{
    // Hide message popup

    if (messageIndex % 2 == 1)
    {
        emit sendNextRound();
    }
}

void TutorialPopup::setUpTutorialButtons()
{
    ui->tutorialWidget->
}
