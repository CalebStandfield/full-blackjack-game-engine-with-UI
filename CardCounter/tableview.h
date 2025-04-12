#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

// Forward declaration
class AnimatableCardItem;

class TableView : public QGraphicsView {
    Q_OBJECT
public:
    explicit TableView(QWidget *parent = nullptr);
    void addCardAnimated(const QString& imagePath, QPointF startPos, QPointF endPos, qreal rotationAngle);
    void clearTable();

private:
    QGraphicsScene* scene;
    QGraphicsPixmapItem* tableBackground;

    void applyShadowToWidget(AnimatableCardItem *card);
};

// ---- Internal AnimatableCardItem Class ----
class AnimatableCardItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    AnimatableCardItem(const QPixmap& pixmap, QGraphicsItem* parent = nullptr)
        : QObject(), QGraphicsPixmapItem(pixmap, parent) {}
};

#endif // TABLEVIEW_H
