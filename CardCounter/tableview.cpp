#include "tableview.h"
#include <QtCore/qtimer.h>
#include <QtWidgets/qgraphicseffect.h>

TableView::TableView(QWidget *parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this)) {

    setScene(scene);
    setRenderHint(QPainter::Antialiasing);

    QPixmap tablePixmap(":/table/blackjack_table.png");

    tablePixmap = tablePixmap.scaled(1200, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
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
    playerCards.resize(playerCount);

    for (unsigned int i = 0; i < playerCount; i++)
    {
        playerCards[i] = std::vector<AnimatableCardItem*>();
    }
}

void TableView::addCardAnimated(int playerIndex, const QString& imagePath, QPointF startPos, QPointF endPos, qreal rotationAngle)
{
    qDebug() << endPos.x() << endPos.y();

    if (playerIndex == -1)
    {
        endPos = QPointF(
            endPos.x() + dealerCards.size() * 20,
            endPos.y()
            );
    }
    else
    {
        endPos = QPointF(
            endPos.x() + playerCards[playerIndex].size() * 7,
            endPos.y() - playerCards[playerIndex].size() * 7
            );

    }

    qDebug() << endPos.x() << endPos.y();

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
    QPointF startPos = QPointF(100, 50);

    for (int i = 0; i < 26; i++)
    {
        int delay = i * 50; // 100ms delay between each card

        QTimer::singleShot(delay, this, [=]() {
            QPointF endPos = QPointF(500, 75 - i); // Slight vertical offset per card

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

AnimatableCardItem* TableView::createCardItem(const QString& imagePath, QPointF startPos, qreal rotationAngle, bool setShadow)
{
    QPixmap cardPixmap(imagePath);

    // Scale the card
    QPixmap scaledPixmap = cardPixmap.scaled(sizeX, sizeY, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    auto* cardItem = new AnimatableCardItem(scaledPixmap);
    if (setShadow)
    {
        applyShadowToWidget(cardItem);
    }
    cardItem->setPos(startPos);
    cardItem->setRotation(rotationAngle);
    cardItem->setZValue(1);
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

// void TableView::clearHands()
// {
//     for (std::vector<AnimatableCardItem*>& hand : playerCards)
//     {
//         for (auto* item : hand)
//         {
//             if (scene->items().contains(item))
//             {
//                 scene->removeItem(item);
//             }
//             item->deleteLater(); // safer than delete
//         }
//         hand.clear();
//     }

//     for (auto* item : dealerCards)
//     {
//         if (scene->items().contains(item))
//         {
//             scene->removeItem(item);
//         }
//         item->deleteLater();
//     }
//     dealerCards.clear();
// }

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
