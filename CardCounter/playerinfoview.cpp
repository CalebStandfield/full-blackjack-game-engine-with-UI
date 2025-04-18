#include "playerinfoview.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QString>

PlayerInfoView::PlayerInfoView(Ui::MainWindow *ui, QObject *parent) : QObject(parent), ui(ui) {}

void PlayerInfoView::buildLayout(int seats)
{
    seatCount = qMin(seats,5);
    seatLabels.resize(seatCount);

    QString QWidgetStyle =
        "QWidget {"
        "    background-color: rgba(50, 25, 20, 200);"
        "    border-radius: 20px;"
        "    border: 1px solid rgba(255, 255, 255, 15);"
        "    padding: 16px;"
        "    color: white;"
        "    font-size: 16px;"
        "}";

    ui->playInfoContainer->setStyleSheet(QWidgetStyle);

    QHBoxLayout *layout = ui->horizontalPlayerInfoLayout;
    layout->setDirection(QBoxLayout::RightToLeft);

    // Clears layout from previous games
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Creates labels and adds them to the layout for each player
    for (int i = 0; i < seatCount; i++) {
        QLabel *label = new QLabel(ui->playInfoContainer);
        label->setFixedSize(200, 140);
        label->setAlignment(Qt::AlignCenter);
        paintBorder(label, PLAYERSTATUS::WAITING);
        seatLabels[i] = label;
        layout->addWidget(label, 0, Qt::AlignVCenter);
    }

    ui->playInfoContainer->show();
}
QString PlayerInfoView::getStatusColor(PLAYERSTATUS status)
{
    QString color;
    switch (status) {
    case PLAYERSTATUS::LOST:
    case PLAYERSTATUS::BUST:
        color = "#cc3333";
        break; // red
    case PLAYERSTATUS::WAITING:
        color = "#dcdc33";
        break; // yellow
    case PLAYERSTATUS::BANKRUPT:
        color = "#2a2a2a";
        break; // black
    case PLAYERSTATUS::PUSHED:
        color = "#808080";
        break; // grey
    case PLAYERSTATUS::STAND:
        color = "#3399ff";
        break; // blue
    case PLAYERSTATUS::ACTIVE:
        color = "#33cc66";
        break; // green
    case PLAYERSTATUS::BETSUBMITTED:
        color = "#ff9933";
        break; // orange
    case PLAYERSTATUS::BLACKJACK:
        color = "#9C27B0";
        break; // casino green
    case PLAYERSTATUS::WON:
        color = "#D4AF37";
        break; // golden
    default:
        color = "#ffffff";
    }
    return color;
}

void PlayerInfoView::paintBorder(QLabel *label, PLAYERSTATUS status)
{
    QString borderColor = getStatusColor(status);

    // Choose label background color
    const char *darkBase =
        "background-color:qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        " stop:0 #222, stop:1 #333);"
        "color:white;";

    QString labelColor;

    if(fillWholeCard(status))
    {
        labelColor = QString("background-color:%1;color:white;"
                            "border:3px solid #000000;").arg(borderColor);
    }
    else
    {
        labelColor = QString("%1border:3px solid %2;").arg(darkBase, borderColor);
    }

    label->setStyleSheet(QString(
                             "QLabel{%1"
                             "border-radius:12px;"
                             "padding:12px 20px;"
                             "font-size:19px;"
                             "font-weight:600;}").arg(labelColor));
}

bool PlayerInfoView::fillWholeCard(PLAYERSTATUS status)
{
    return status == PLAYERSTATUS::WON || status == PLAYERSTATUS::BLACKJACK || status == PLAYERSTATUS::LOST
           || status == PLAYERSTATUS::PUSHED || status == PLAYERSTATUS::BANKRUPT;
}

void PlayerInfoView::rebuildMapping()
{
    modelToSeat.clear();
    for (int i = 0; i < seatCount; i++)
        modelToSeat.push_back(i);
}

void PlayerInfoView::insertSplitMapping(int playerIndex)
{
    // Inserts a new player behind playerIndex but points them to the same original label
    if (playerIndex < modelToSeat.size())
        modelToSeat.insert(playerIndex + 1, modelToSeat[playerIndex]);
}

void PlayerInfoView::onSettingsAccepted(const std::vector<Player> &players, int, int)
{
    userIndex = -1;

    // Builds all labels and then updates them
    buildLayout(static_cast<int>(players.size()));
    rebuildMapping();
    for (int i = 0; i < static_cast<int>(players.size()); i++)
    {
        if(players[i].isUser)
            userIndex = i;
        refreshSeat(modelToSeat[i], players[i]);
    }
}

void PlayerInfoView::refreshSeat(int seat, const Player& player)
{
    if (seat >= seatCount)
        return;

    paintBorder(seatLabels[seat], player.status);
    setSeatText(seat, player.money, player.hand.getBet(), player.status);
}

void PlayerInfoView::onPlayerUpdated(int playerIndex, const Player& player, int total)
{
    if (playerIndex >= modelToSeat.size())
        return;

    // Updates text and border for the playerIndex label
    int seat = modelToSeat[playerIndex];
    paintBorder(seatLabels[seat], player.status);
    setSeatText(playerIndex, player.money, player.hand.getBet(), player.status);
}

void PlayerInfoView::onUpdateAllPlayers(const std::vector<Player> &players)
{
    rebuildMapping();
    for (int i = 0; i < static_cast<int>(players.size()) && i < modelToSeat.size(); i++)
        refreshSeat(modelToSeat[i], players[i]);
}

void PlayerInfoView::onSplitPlayers(int originalIndex, const Player& originalPlayer, const Player&)
{
    // Adds a new person after originalIndex and updates the label
    insertSplitMapping(originalIndex);
    if (originalIndex < modelToSeat.size())
        refreshSeat(modelToSeat[originalIndex], originalPlayer);
}

void PlayerInfoView::onCurrentPlayerTurn(int newPlayerIndex, int money, int bet)
{
    if (newPlayerIndex >= modelToSeat.size())
        return;

    int seat = modelToSeat[newPlayerIndex];
    paintBorder(seatLabels[seat], PLAYERSTATUS::ACTIVE);
    setSeatText(newPlayerIndex, money, bet, PLAYERSTATUS::ACTIVE);
}

void PlayerInfoView::setSeatText(int seat, int money, int bet, PLAYERSTATUS status)
{
    if (seat < 0 || seat >= seatCount)
        return;

    QString borderColor = getStatusColor(status);
    std::string statusString = PlayerStatus::toString(status);

    QString textColor = "#ffffff";

    // Make the status text white if the background is filled in
    bool isFilled = fillWholeCard(status);
    QString statusTextColor = isFilled ? textColor : borderColor;

    QString name;
    // If seat is is the user, set name as User
    if(seat == userIndex)
        name = "User";
    // If seat is not user, use Player
    else
    {
        // If seat is after userIndex, subtract by 1 for player number
        int playerNumber = seat + 1 - (seat > userIndex ? 1 : 0);
        name = QString("Player %1").arg(playerNumber);
    }

    seatLabels[seat]->setTextFormat(Qt::RichText);
    seatLabels[seat]->setText(
        QString("<span style='color:%6;'>%1</span><br>"
                "<span style='color:white;'>Money: $%2</span><br>"
                "<span style='color:white;'>Bet: $%3</span><br>"
                "<span style='color: %4;'>%5</span>")
            .arg(name)
            .arg(money)
            .arg(bet)
            .arg(statusTextColor)
            .arg(QString::fromStdString(statusString))
            .arg(textColor)
        );

    seatLabels[seat]->show();
}

void PlayerInfoView::onStopEverything()
{
    ui->playInfoContainer->hide();
}

void PlayerInfoView::onEndRound(const std::vector<Player>& players)
{
    for(int i = 0; i < static_cast<int>(players.size()); i++)
    {
        refreshSeat(i, players[i]);
    }
}
