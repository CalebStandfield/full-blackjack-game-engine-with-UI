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

    toggleVisableTutorialPopup(false);
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
        "Tip: The dealer has a 6, which is a bust card, but is a strong bust card (3-6). The dealer is likely to bust, so you should stand if you are over 11",
        "Lesson: When the dealer shows 3-6 and you have greater than 11, you don't risk your own hand and hope they hit and bust", // scenario 2 done
        "Tip: With 2 aces, both are likely to give you 2 strong hands if you split. Basic strategy is to always split aces",
        "Lesson: One hand became 19, the other 18. Both became good hands instead of one bad 12 hand", // scenario 3 done
        "Tip: You already have a strong 20 hand, splitting risks turning a strong hand into 2 weaker ones. Dealer has a strong bust card (6) anyways. Strategy says to stand",
        "Lesson: Don't mess with a great hand, especially when a dealer is likely to bust. Never split 10's", // scenario 4 done
        "Tip: 11 is the best hand to double on. Most cards will get you close to or at 21",
        "Lesson: Always double on 11", // scenario 5 done
        "Tip: Soft 18 isn't great vs a dealer 10. Doubling only gets you one card and you might be stuck at a worse position. Strategy is to hit if the dealer's card is greater than yours with a 10 and over 7",
        "Tip: You now have 21, always stand",
        "Lesson: Don't overcommit against strong dealer upcard", // scenario 6 done
        "Lesson: Sometimes there's no escaping a loss. Unfortunetly that part of the game", // scenario 7 done
        "Tip: Soft 17 is a weak hand, treat it more like 8 than 17. Since the dealer has a 9, strategy says to hit",
        "Tip: 19 is a strong hand, strategy says to now stand",
        "Lesson: Keep hitting soft 17 until you reach over the dealer's card with a 10 (19) or until hard 17", // scenario 8 done
        "Tip: Any 8's should be split, hard 16 is the worst possible hand since it is still considered a weak hand but closest to busting. Two chances at 18+ beats one guarenteed 16",
        "Tip: While normally doubling on 11, you cannot double after splitting. Strategy says to hit since no change at busting",
        "Tip: you now have 21, always stand",
        "Tip: Strategy says to hit on a 10.",
        "Tip: You never hit once at or above hard 17, strategy is to stand",
        "Lesson: First hand reaches 21 and wins, while the other reaches 18 pushes the dealer's 18. ALways split 8's, turns a horrible 17 into 2 possibly good hands", // scenario 9
    };

    const std::initializer_list<MOVE> tutorialButtonMoves = {
        MOVE::HIT, // Add moves in order here || scenario 1 done
        MOVE::STAND, // scenario 2 done
        MOVE::SPLIT, // scenario 3 done
        MOVE::STAND, // scenario 4 done
        MOVE::DOUBLE, // scenario 5 done
        MOVE::HIT,
        MOVE::STAND, // scenario 6 done
        // Dealer blackjack so no move here || scenario 7 done
        MOVE::HIT,
        MOVE::STAND, // scenario 8 done
        MOVE::SPLIT,
        MOVE::HIT,
        MOVE::STAND,
        MOVE::HIT,
        MOVE::STAND // scenario 9 done
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
    if (show)
    {
        ui->tutorialLabel->setText(popupMessages->at(messageIndex));
        ui->tutorialWidget->show();
    }
    else
    {
        ui->tutorialWidget->hide();
    }
}

bool TutorialPopup::nextIsTip() const
{
    return popupMessages->at(messageIndex).startsWith("Tip");
}

void TutorialPopup::onContinuePressed()
{
    toggleVisableTutorialPopup(false);

    const QString& currentMessage = popupMessages->at(messageIndex);

    if (currentMessage.startsWith("Tip"))
    {
        // it’s a Tip, disable everything, then enable the one move button
        emit enableButton(ui->hitButton, false);
        emit enableButton(ui->standButton, false);
        emit enableButton(ui->doubleButton, false);
        emit enableButton(ui->splitButton, false);

        // look up which MOVE to enable
        MOVE move = moveOrder->at(moveIndex++);
        QPushButton* button = nullptr;
        switch (move) {
        case MOVE::HIT:
            button = ui->hitButton;
            break;
        case MOVE::STAND:
            button = ui->standButton;
            break;
        case MOVE::DOUBLE:
            button = ui->doubleButton;
            break;
        case MOVE::SPLIT:
            button = ui->splitButton;
            break;
        }
        if (button)
        {
            if (messageIndex == 0)
            {
                emit delayedEnableButton(button, true);
            }
            else
                emit enableButton(button, true);
        }
    }
    else if (currentMessage.startsWith("Lesson"))
    {
        // it’s a Lesson so disable all play buttons
        emit enableButton(ui->hitButton, false);
        emit enableButton(ui->standButton, false);
        emit enableButton(ui->doubleButton, false);
        emit enableButton(ui->splitButton, false);

        // then move on to the next round
        emit sendNextRound();
    }

    if (messageIndex < (int)popupMessages->size() - 1)
    {
        messageIndex++;
    }
}

void TutorialPopup::resetAndHideTutorial()
{
    toggleVisableTutorialPopup(false);
    messageIndex = 0;
    moveIndex = 0;
}

void TutorialPopup::setUpTutorialButtons()
{
    ui->tutorialWidget->
}
