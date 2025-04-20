#ifndef TUTORIALPOPUP_H
#define TUTORIALPOPUP_H

#include "ui_mainwindow.h"

class TutorialPopup : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief TutorialPopup Creates the popup message class for the tutorial
     * @param ui The ui holding all elements on the screen
     */
    explicit TutorialPopup(Ui::MainWindow* ui, QObject *parent = nullptr);

    /**
     * @brief showNextPopup Shows the next popup message on screen
     */
    void showNextPopup();

signals:
    /**
     * @brief sendNextRound Signal to move to the next round of blackjack
     */
    void sendNextRound();

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
     * @brief messageIndex The current index in the messages list
     */
    int messageIndex;

    /**
     * @brief createMessages Helper method to create all of the popup messages and add them to the list
     */
    void createMessages();
};

#endif // TUTORIALPOPUP_H
