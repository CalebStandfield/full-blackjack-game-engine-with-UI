#include "tableview.h"
#include <QtWidgets/qgraphicseffect.h>

TableView::TableView(QWidget *parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this)) {

    setScene(scene);
    setRenderHint(QPainter::Antialiasing);

    QPixmap tablePixmap(":/table/BlackJackTableMat.png"); // GET A DIFFERENT IMAGE

    tablePixmap = tablePixmap.scaled(1200, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    tableBackground = scene->addPixmap(tablePixmap);
    tableBackground->setZValue(0);
    scene->setSceneRect(tablePixmap.rect());
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

void TableView::addCardAnimated(const QString& imagePath, QPointF startPos, QPointF endPos, qreal rotationAngle)
{
    QPixmap cardPixmap(imagePath);

    // Scale the card
    QPixmap scaledPixmap = cardPixmap.scaled(75, 125, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    auto* cardItem = new AnimatableCardItem(scaledPixmap);
    applyShadowToWidget(cardItem);
    cardItem->setPos(startPos);
    cardItem->setRotation(rotationAngle);
    // cardItem->setTransformOriginPoint(75 / 2, 125 / 2);
    cardItem->setZValue(1);
    scene->addItem(cardItem);

    // Animate position
    QPropertyAnimation* anim = new QPropertyAnimation(cardItem, "pos");
    anim->setDuration(2000);
    anim->setStartValue(startPos);
    anim->setEndValue(endPos);
    anim->setEasingCurve(QEasingCurve::OutQuad);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
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

void TableView::clearTable() {
    for (auto* item : scene->items()) {
        if (item != tableBackground) {
            scene->removeItem(item);
            delete item;
        }
    }
}
