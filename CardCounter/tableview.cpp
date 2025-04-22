#include "tableview.h"
#include <QtWidgets/qgraphicseffect.h>

TableView::TableView(QWidget *parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this)) {

    timer = new TimerManager();
    setScene(scene);

    setRenderHints(
        QPainter::Antialiasing                |
        QPainter::SmoothPixmapTransform
        );

    QPixmap tablePixmap(":/table/background_table_mat.png");

    tablePixmap = tablePixmap.scaled(1170, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    tableBackground = scene->addPixmap(tablePixmap);
    tableBackground->setZValue(0);
    scene->setSceneRect(tablePixmap.rect());
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

TableView::~TableView()
{
    delete timer;
}

void TableView::setUpTableViewConnects()
{

}

void TableView::createPlayerCardContainers(unsigned int playerCount)
{
    playerCards.resize(playerCount);

    for (unsigned int i = 0; i < playerCount; i++)
    {
        playerCards[i] = std::vector<std::vector<AnimatableCardItem*>>();
        playerCards[i].resize(1);
        playerCards[i][0] = std::vector<AnimatableCardItem*>();
    }
}

void TableView::addPlayerHandContainerAt(unsigned int playerIndex, unsigned int handIndex)
{
    // Index check
    if (playerIndex > playerCards.size())
        return;

    // Insert an empty vector at the specified index
    playerCards[playerIndex].insert(playerCards[playerIndex].begin() + handIndex + 1, std::vector<AnimatableCardItem*>());
}

void TableView::splitPlayerHand(unsigned int playerIndex, unsigned int handIndex){
    if (playerIndex > playerCards.size())
        return;
    addPlayerHandContainerAt(playerIndex, handIndex);
    for(int i = (int)playerCards[playerIndex].size() - 1; i >= 0; i--){
        for(int j = 0; j < (int)playerCards[playerIndex][i].size(); j++){
            if(i == (int)handIndex && j == 1){
                updateCardPosition(playerIndex, i, j, i + 1, 0);
                continue;
            }
            updateCardPosition(playerIndex, i, j, i, j);
        }
    }
}

void TableView::updateCardPosition(unsigned int playerIndex, unsigned int oldHandIndex, unsigned int oldCardIndex,
                                                             unsigned int newHandIndex, unsigned int newCardIndex){
    if(playerIndex >= playerCards.size() || oldHandIndex >= playerCards[playerIndex].size()
        || newHandIndex >= playerCards[playerIndex].size() || oldCardIndex >= playerCards[playerIndex][oldHandIndex].size())
        return;

    AnimatableCardItem* card = playerCards[playerIndex][oldHandIndex][oldCardIndex];
    //May need to make card a copy here.
    QPointF newPos = getCardEndPosition(playerIndex, newHandIndex, newCardIndex);
    qreal newRot = getCardEndRotation(playerIndex, newHandIndex);

    QParallelAnimationGroup* cardAnim = createAnimationCardItem(card, card->pos(), newPos,
                                                                 card->rotation(), newRot);
    connect(cardAnim, &QParallelAnimationGroup::finished, this, [=]() {
        playerCards[playerIndex][oldHandIndex].erase(playerCards[playerIndex][oldHandIndex].begin() + oldCardIndex);
        playerCards[playerIndex][newHandIndex].insert(playerCards[playerIndex][newHandIndex].begin() + newCardIndex, card);
    });
}

QPointF TableView::getCardEndPosition(int playerIndex, int handIndex, int cardIndex)
{
    if(playerIndex == -1)
        return QPointF(550 + dealerCards.size() * 40, 70);
    qreal xOffset = 550;
    qreal yOffset = -10;
    qreal cardOffset = 11;
    qreal r = 450; //radius

    qreal tempAngle = ((playerIndex + 1) * M_PI / (playerCards.size() + 2)) + ((handIndex + 1) * M_PI / ((playerCards.size() + 2) * (playerCards[playerIndex].size() + 1)));
    qreal newX = xOffset + r * qCos(tempAngle);
    qreal newY = yOffset + r * qSin(tempAngle);

    tempAngle -= M_PI_2;
    qreal cosA = qCos(tempAngle);
    qreal sinA = qSin(tempAngle);
    qreal rotatedX = cardOffset * sinA + cardOffset * cosA;
    qreal rotatedY = cardOffset * cosA - cardOffset * sinA;

    newX += cardIndex * rotatedX;
    newY -= cardIndex * rotatedY;

    return QPointF(newX, newY);
}

qreal TableView::getCardEndRotation(int playerIndex, int handIndex)
{
    if(playerIndex == -1)
        return 0;
    int playerCount = playerCards.size();
    qreal tempAngle = ((playerIndex + 1) * M_PI / (playerCount + 2)) + ((handIndex + 1) * M_PI / ((playerCount + 2) * (playerCards[playerIndex].size() + 1)));
    return qRadiansToDegrees(tempAngle - M_PI_2);
}

void TableView::addCardAnimated(int playerIndex, int handIndex, const QString& imagePath, QPointF startPos, QPointF endPos, qreal rotationAngle)
{
    AnimatableCardItem* cardItem = createCardItem(imagePath, startPos, rotationAngle, true);
    cardItem->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

    QParallelAnimationGroup* anim = createAnimationCardItem(cardItem, startPos, endPos, 90, rotationAngle);

    if (playerIndex == -1)
    {
        dealerCards.push_back(cardItem);
        connect(anim, &QParallelAnimationGroup::finished, this, [=]() {
            scene->removeItem(cardItem);
            delete cardItem;
            addDealerCardAt(imagePath, endPos, rotationAngle);
        });
        return;
    }
    //playerCards[playerIndex][handIndex].push_back(cardItem);
    connect(anim, &QParallelAnimationGroup::finished, this, [=]() {
        scene->removeItem(cardItem);
        delete cardItem;
        addPlayerCardAt(playerIndex, handIndex, imagePath, endPos, rotationAngle);
    });
}

void TableView::addPlayerCardAt(int playerIndex, int handIndex, const QString& imagePath, QPointF pos, qreal rotationAngle)
{
    AnimatableCardItem* cardItem = createCardItem(imagePath, pos, rotationAngle, false);
    playerCards[playerIndex][handIndex].push_back(cardItem);
}

void TableView::addDealerCardAt(const QString& imagePath, QPointF pos, qreal rotationAngle)
{
    AnimatableCardItem* cardItem = createCardItem(imagePath, pos, rotationAngle, false);
    dealerCards.push_back(cardItem);
}

void TableView::applyShadowToCard(AnimatableCardItem *card)
{
    // Create a shadow effect
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();

    // Set how the shadow looks
    shadow->setBlurRadius(15);
    shadow->setOffset(5, 5);
    shadow->setColor(QColor(0, 0, 0, 160));

    card->setGraphicsEffect(shadow);
}

void TableView::createDealerPile()
{
    QPointF startPos = QPointF(-100, 50);

    for (int i = 0; i < 26; i++)
    {
        int delay = i * 50; // 100ms delay between each card

        timer->scheduleSingleShot(delay, [=]() {
            QPointF endPos = QPointF(450, 75 - i); // Slight vertical offset per card

            AnimatableCardItem* cardItem = createCardItem(":/cardImages/cards_pngsource/back_of_card.png", startPos, 90, true);

            QParallelAnimationGroup* anim = createAnimationCardItem(cardItem, startPos, endPos, 90, 90);

            connect(anim, &QPropertyAnimation::finished, this, [=]() {
                scene->removeItem(cardItem);
                delete cardItem;

                // Optionally add a final static card after animation
                createCardItem(":/cardImages/cards_pngsource/back_of_card.png", endPos, 90, false);
            });
        });
    }
}

void TableView::revealDealerCard(const QString& imagePath)
{
    QPointF endPos = QPointF(550, 70);
    createCardItem(imagePath, endPos, 0, false);
}

AnimatableCardItem* TableView::createCardItem(const QString& imagePath, QPointF startPos, qreal rotationAngle, bool setShadow)
{
    QPixmap cardPixmap(imagePath);

    // Scale the card
    QPixmap scaledPixmap = cardPixmap.scaled(sizeX, sizeY, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    auto* cardItem = new AnimatableCardItem(scaledPixmap);
    if (setShadow)
    {
        applyShadowToCard(cardItem);
    }
    cardItem->setPos(startPos);
    cardItem->setRotation(rotationAngle);
    cardItem->setZValue(1);
    cardItem->setTransformOriginPoint(cardItem->boundingRect().center());
    scene->addItem(cardItem);
    return cardItem;
}

QParallelAnimationGroup* TableView::createAnimationCardItem(AnimatableCardItem* cardItem, QPointF startPos, QPointF endPos, qreal startRotation, qreal endRotation)
{
    // Position animation
    QPropertyAnimation* posAnim = new QPropertyAnimation(cardItem, "pos");
    posAnim->setDuration(600);
    posAnim->setStartValue(startPos);
    posAnim->setEndValue(endPos);
    posAnim->setEasingCurve(QEasingCurve::OutQuad);

    // Rotation animation
    QPropertyAnimation* rotAnim = new QPropertyAnimation(cardItem, "rotation");
    rotAnim->setDuration(600);
    rotAnim->setStartValue(startRotation);
    rotAnim->setEndValue(endRotation);
    rotAnim->setEasingCurve(QEasingCurve::OutQuad);

    // Group animations together
    QParallelAnimationGroup* group = new QParallelAnimationGroup;
    group->addAnimation(posAnim);
    group->addAnimation(rotAnim);
    group->start(QAbstractAnimation::DeleteWhenStopped);

    return group;
}

void TableView::clearTable()
{
    for (auto* item : scene->items())
    {
        if (item != tableBackground)
        {
            scene->removeItem(item);
            delete item;
        }
    }
    dealerCards.clear();

    for (std::vector<std::vector<AnimatableCardItem*>>& player : playerCards)
    {
        for (std::vector<AnimatableCardItem*>& hand : player)
        {
            hand.clear();
        }
        player.clear();
        player.resize(1);
    }
}

void TableView::stopEverything()
{
    timer->cancelAllTimers();
}
