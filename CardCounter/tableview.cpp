#include "tableview.h"

TableView::TableView(QWidget *parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this)) {

    setScene(scene);
    setRenderHint(QPainter::Antialiasing);

    QPixmap tablePixmap(":/cardImages/table.png");  // Your table image path
    tableBackground = scene->addPixmap(tablePixmap);
    tableBackground->setZValue(0);
    scene->setSceneRect(tablePixmap.rect());
}

void TableView::addCardAnimated(const QString& imagePath, QPointF startPos, QPointF endPos, qreal rotationAngle)
{
    QPixmap cardPixmap(imagePath);

    // Scale the card
    QPixmap scaledPixmap = cardPixmap.scaled(75, 125, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    auto* cardItem = new AnimatableCardItem(scaledPixmap);
    cardItem->setPos(startPos);
    cardItem->setRotation(rotationAngle); // Set rotation here
    // cardItem->setTransformOriginPoint(cardSize.width() / 2, cardSize.height() / 2);
    cardItem->setTransformOriginPoint(75 / 2, 125 / 2);
    cardItem->setZValue(1);
    scene->addItem(cardItem);

    // Animate position
    QPropertyAnimation* anim = new QPropertyAnimation(cardItem, "pos");
    anim->setDuration(600);
    anim->setStartValue(startPos);
    anim->setEndValue(endPos);
    anim->setEasingCurve(QEasingCurve::OutQuad);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void TableView::clearTable() {
    for (auto* item : scene->items()) {
        if (item != tableBackground) {
            scene->removeItem(item);
            delete item;
        }
    }
}
