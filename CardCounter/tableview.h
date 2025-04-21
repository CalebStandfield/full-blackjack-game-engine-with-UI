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
    void addPlayerHandContainerAt(unsigned int playerIndex, unsigned int handIndex);

    void splitPlayerHand(unsigned int playerIndex, unsigned int handIndex);

    QPointF getCardEndPosition(int playerIndex, int handIndex, int cardIndex);
    qreal getCardEndRotation(int playerIndex, int handIndex);

    void addCardAnimated(int playerIndex, int handIndex, const QString& imagePath, QPointF startPos, QPointF endPos, qreal rotationAngle);
    void addPlayerCardAt(int playerIndex, int handIndex, const QString& imagePath, QPointF pos, qreal rotationAngle);
    void addDealerCardAt(const QString& imagePath, QPointF pos, qreal rotationAngle);
    void createDealerPile();

    void revealDealerCard(const QString &imagePath);

    AnimatableCardItem* createCardItem(const QString& imagePath, QPointF startPos, qreal rotationAngle, bool setShadow);
    QParallelAnimationGroup* createAnimationCardItem(AnimatableCardItem* cardItem, QPointF startPos, QPointF endPos, qreal startRotation, qreal endRotation);

    // void clearHands();
    void clearTable();

private:
    // Vector of players, hands of the players, and cards in said hands
    std::vector<std::vector<std::vector<AnimatableCardItem*>>> playerCards;
    std::vector<AnimatableCardItem*> dealerCards;

    unsigned int sizeX = 63;
    unsigned int sizeY = 91;

    void setUpTableViewConnects();

    QGraphicsScene* scene;
    QGraphicsPixmapItem* tableBackground;

    void setPlayerTextPositionsOnTable();

    void applyShadowToWidget(AnimatableCardItem *card);

    void updateCardPosition(unsigned int playerIndex, unsigned int oldHandIndex, unsigned int oldCardIndex,
                                                      unsigned int newHandIndex, unsigned int newCardIndex);
};

// ---- Internal AnimatableCardItem Class ----
class AnimatableCardItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)

public:
    AnimatableCardItem(const QPixmap& pixmap, QGraphicsItem* parent = nullptr)
        : QObject(), QGraphicsPixmapItem(pixmap, parent){}
};

#endif // TABLEVIEW_H
