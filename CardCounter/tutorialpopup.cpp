#include "tutorialpopup.h"

TutorialPopup::TutorialPopup(Ui::MainWindow* ui, QString qWidgetStyle, QString qPushButtonStyle, QObject *parent) : QObject(parent), ui(ui)
{
    QString qLabelStyle =
        "QLabel {"
        "    background-color: transparent;"
        "    border: none;"
        "    color: white;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    padding: 6px;"
        "}";

    ui->tutorialWidget->setStyleSheet(qWidgetStyle);
    ui->tutorialContinueButton->setStyleSheet(qPushButtonStyle);
    ui->tutorialLabel->setStyleSheet(qLabelStyle);

    popupMessages = new std::vector<QString>(26);
    createMessages();

    toggleVisableTutorialPopup(false);
}

TutorialPopup::~TutorialPopup()
{
    delete popupMessages;
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
    toggleVisableTutorialPopup(false);

    if (messageIndex % 2 == 1)
    {
        emit sendNextRound();
    }

    if (messageIndex < 25)
    {
        messageIndex++;
    }
}

