#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

// Forward declaration
class AnimatableCardItem;

class TableView : public QGraphicsView {
    Q_OBJECT
public:
    explicit TableView(QWidget *parent = nullptr);
    ~TableView();

    void createPlayerCardContainers(unsigned int playerCount);
    void addPlayerCardContainerAt(unsigned int indexAt);
    void splitPlayerHand(unsigned int playerIndex, unsigned int seatIndex, unsigned int handIndex, unsigned int totalHandCount);

    int playerCount;
    QPointF getCardEndPosition(int seatIndex, int handIndex, int totalHandCount);
    qreal getCardEndRotation(int seatIndex, int handIndex, int totalHandCount);

    void addCardAnimated(int playerIndex, const QString& imagePath, QPointF startPos, QPointF endPos, qreal rotationAngle);
    void addPlayerCardAt(int playerIndex, const QString& imagePath, QPointF pos, qreal rotationAngle);
    void addDealerCardAt(const QString& imagePath, QPointF pos, qreal rotationAngle);
    void createDealerPile();

    void revealDealerCard(const QString &imagePath);

    AnimatableCardItem* createCardItem(const QString& imagePath, QPointF startPos, qreal rotationAngle, bool setShadow);
    QParallelAnimationGroup* createAnimationCardItem(AnimatableCardItem* cardItem, QPointF startPos, QPointF endPos, qreal startRotation, qreal endRotation);

    // void clearHands();
    void clearTable();

private:
    std::vector<std::vector<AnimatableCardItem*>> playerCards;
    std::vector<AnimatableCardItem*> dealerCards;

    unsigned int sizeX = 63;
    unsigned int sizeY = 91;

    void setUpTableViewConnects();

    QGraphicsScene* scene;
    QGraphicsPixmapItem* tableBackground;

    void setPlayerTextPositionsOnTable();

    void applyShadowToWidget(AnimatableCardItem *card);

};

// ---- Internal AnimatableCardItem Class ----
class AnimatableCardItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)

public:
    QString imagePath;

    explicit AnimatableCardItem(const QPixmap& pixmap, const QString& imagePath, QGraphicsItem* parent = nullptr)
        : QObject(), QGraphicsPixmapItem(pixmap, parent), imagePath(imagePath){}
};

#endif // TABLEVIEW_H
