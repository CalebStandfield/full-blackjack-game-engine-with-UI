#include "tableview.h"
#include <QtCore/qtimer.h>
#include <QtWidgets/qgraphicseffect.h>

TableView::TableView(QWidget *parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this)) {

    setScene(scene);
    setRenderHint(QPainter::Antialiasing);

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

}

void TableView::setUpTableViewConnects()
{

}

void TableView::createPlayerCardContainers(unsigned int playerCount)
{
    this->playerCount = playerCount;
    playerCards.resize(playerCount);

    for (unsigned int i = 0; i < playerCount; i++)
    {
        playerCards[i] = std::vector<AnimatableCardItem*>();
    }
}

void TableView::addPlayerCardContainerAt(unsigned int indexAt)
{
    // Index check
    if (indexAt > playerCards.size())
        return;

    // Insert an empty vector at the specified index
    playerCards.insert(playerCards.begin() + indexAt, std::vector<AnimatableCardItem*>());
}

void TableView::splitPlayerHand(unsigned int playerIndex, unsigned int seatIndex, unsigned int handIndex, unsigned int totalHandCount){
    if (playerIndex > playerCards.size())
        return;
    addPlayerCardContainerAt(playerIndex + 1);

    totalHandCount++;

    AnimatableCardItem* firstCard = playerCards[playerIndex][1];
    AnimatableCardItem* secondCard = playerCards[playerIndex][2];
    QPointF firstPos = getCardEndPosition(seatIndex, handIndex, totalHandCount);
    qreal firstRot = getCardEndRotation(seatIndex, handIndex, totalHandCount);
    const QString& firstImagePath = firstCard->imagePath;
    const QString& secondImagePath = secondCard->imagePath;
    QPointF secondPos = getCardEndPosition(seatIndex, handIndex + 1, totalHandCount);
    qreal secondRot = getCardEndRotation(seatIndex, handIndex + 1, totalHandCount);

    playerCards[playerIndex].clear();
    playerCards[playerIndex + 1].clear();

    QParallelAnimationGroup* animFirst = createAnimationCardItem(firstCard, firstCard->pos(), firstPos,
                                                                 firstCard->rotation(), firstRot);
    QParallelAnimationGroup* animSecond = createAnimationCardItem(secondCard, secondCard->pos(), secondPos,
                                                                 secondCard->rotation(), secondRot);

    connect(animFirst, &QParallelAnimationGroup::finished, this, [=]() {
        scene->removeItem(firstCard);
        delete firstCard;
        addPlayerCardAt(playerIndex, firstImagePath, firstPos, firstRot);
    });
    connect(animSecond, &QParallelAnimationGroup::finished, this, [=]() {
        scene->removeItem(secondCard);
        delete secondCard;
        addPlayerCardAt(playerIndex + 1, secondImagePath, secondPos, secondRot);
    });
}

QPointF TableView::getCardEndPosition(int seatIndex, int handIndex, int totalHandCount)
{
    if(seatIndex == -1)
        return QPointF(550, 70);
    qreal xOffset = 550;
    qreal yOffset = -10;
    qreal r = 450; //radius

    qreal tempAngle = ((seatIndex + 1) * M_PI / (playerCount + 2)) + ((handIndex + 1) * M_PI / ((playerCount + 2) * (totalHandCount + 1)));
    qreal newX = xOffset + r * qCos(tempAngle);
    qreal newY = yOffset + r * qSin(tempAngle);

    return QPointF(newX, newY);
}

qreal TableView::getCardEndRotation(int seatIndex, int handIndex, int totalHandCount)
{
    if(seatIndex == -1)
        return 0;
    qreal tempAngle = ((seatIndex + 1) * M_PI / (playerCount + 2)) + ((handIndex + 1) * M_PI / ((playerCount + 2) * (totalHandCount + 1)));
    return qRadiansToDegrees(tempAngle - M_PI_2);
}

void TableView::addCardAnimated(int playerIndex, const QString& imagePath, QPointF startPos, QPointF endPos, qreal rotationAngle)
{
    if (playerIndex == -1)
    {
        endPos = QPointF(
            endPos.x() + dealerCards.size() * 40,
            endPos.y()
            );
    }
    else
    {
        qreal cardOffset = 6;
        qreal angleRadians = qDegreesToRadians(rotationAngle);

        qreal cosA = qCos(angleRadians);
        qreal sinA = qSin(angleRadians);

        // Rotate vector
        qreal rotatedX = cardOffset * sinA + cardOffset * cosA;
        qreal rotatedY = cardOffset * cosA - cardOffset * sinA;

        endPos = QPointF(
            endPos.x() + playerCards[playerIndex].size() * rotatedX,
            endPos.y() - playerCards[playerIndex].size() * rotatedY
            );
    }
    AnimatableCardItem* cardItem = createCardItem(imagePath, startPos, rotationAngle, true);

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
    playerCards[playerIndex].push_back(cardItem);
    connect(anim, &QParallelAnimationGroup::finished, this, [=]() {
        scene->removeItem(cardItem);
        delete cardItem;
        addPlayerCardAt(playerIndex, imagePath, endPos, rotationAngle);
    });
}

void TableView::addPlayerCardAt(int playerIndex, const QString& imagePath, QPointF pos, qreal rotationAngle)
{
    AnimatableCardItem* cardItem = createCardItem(imagePath, pos, rotationAngle, false);
    playerCards[playerIndex].push_back(cardItem);
}

void TableView::addDealerCardAt(const QString& imagePath, QPointF pos, qreal rotationAngle)
{
    AnimatableCardItem* cardItem = createCardItem(imagePath, pos, rotationAngle, false);
    dealerCards.push_back(cardItem);
}

void TableView::applyShadowToWidget(AnimatableCardItem *card)
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

        QTimer::singleShot(delay, this, [=]() {
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

    auto* cardItem = new AnimatableCardItem(scaledPixmap, imagePath);
    if (setShadow)
    {
        applyShadowToWidget(cardItem);
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

    for (std::vector<AnimatableCardItem*>& hand : playerCards)
    {
        hand.clear();
    }
}
