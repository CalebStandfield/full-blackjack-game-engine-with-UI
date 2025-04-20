#ifndef TUTORIALPOPUP_H
#define TUTORIALPOPUP_H

#include "ui_mainwindow.h"
#include "statistics.h"

using Move::MOVE;

class TutorialPopup : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief TutorialPopup Creates the popup message class for the tutorial
     * @param ui The ui holding all elements on the screen
     */
    explicit TutorialPopup(Ui::MainWindow* ui, QString qWidgetStyle, QString qPushButtonStyle, QObject *parent = nullptr);

    /**
     * @brief Deconstructor
     */
    ~TutorialPopup();

    /**
     * @brief showNextPopup Shows the next popup message on screen
     * @param show A bool for the state of visability for the tutorial popup
     */
    void toggleVisableTutorialPopup(bool show);

signals:
    /**
     * @brief sendNextRound Signal to move to the next round of blackjack
     */
    void sendNextRound();

    /**
     * @brief enableButton
     * @param button
     * @param enabled
     */
    void enableButton(QPushButton* button, bool enabled);

public slots:
    /**
     * @brief onContinuePressed Slot for when the continue button is pressed on the popup page
     */
    void onContinuePressed();

private:
    /**
     * @brief ui The mainwindow ui holding all on screen elements
     */
    Ui::MainWindow *ui;

    /**
     * @brief popupMessages A vector containing all of the popup messages
     */
    std::vector<QString>* popupMessages;

    /**
     * @brief toggleButtonOrder A vector containing the MOVE at each message popup so the correct button is turned on
     */
    std::vector<MOVE>* toggleButtonOrder;

    /**
     * @brief messageIndex The current index in the messages list
     */
    int messageIndex;

    /**
     * @brief createMessages Helper method to create all of the popup messages and add them to the list
     */
    void createMessages();
};

#endif // TUTORIALPOPUP_H
