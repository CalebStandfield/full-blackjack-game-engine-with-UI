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

    popupMessages = new std::vector<QString>();
    moveOrder = new std::vector<MOVE>();
    createMessages();

    toggleVisableTutorialPopup(true);
}

TutorialPopup::~TutorialPopup()
{
    delete popupMessages;
    delete moveOrder;
}

void TutorialPopup::createMessages()
{
    const std::initializer_list<QString> tutorialMessages = {
        "Tip: The dealer has a 2, which is a bust card (2-6), but it is too small to justify standing when you also have a bad total. Strategy is to hit because your odds to bust are lower than the dealer's advantage", // Add messages in order here
        "Lesson: Even though you bust, it was still the right play. Long-term odds favor hitting on 12 vs 2", // scenario one done
        "Tip: The dealer has a 6, which is a bust card, but is a strong bust card (3-6). The dealer is likely to bust, so you should stand",
        ""
    };

    const std::initializer_list<MOVE> tutorialButtonMoves = {
        MOVE::HIT, // Add messages in order here
        MOVE::STAND,
    };

    for(const QString& message : tutorialMessages)
    {
        popupMessages->push_back(message);
    }

    for(const MOVE& move : tutorialButtonMoves)
    {
        moveOrder->push_back(move);
    }
    messageIndex = 0;
    moveIndex = 0;
}

void TutorialPopup::toggleVisableTutorialPopup(bool show)
{
    ui->tutorialLabel->setText(popupMessages->at(messageIndex));
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

