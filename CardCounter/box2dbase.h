#ifndef BOX2DBASE_H
#define BOX2DBASE_H

#include <QGraphicsScene>
#include <Box2D/Box2D.h>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QRandomGenerator>
#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QQueue>

class box2Dbase : public QGraphicsScene{
    Q_OBJECT
public:
    /**
     * @brief box2Dbase Constructor
     * @param parent
     */
    explicit box2Dbase(QObject *parent = nullptr);

    /**
     * Destructor
     */
    ~box2Dbase();

    /**
     * @brief advance Responsible for updating the physics simulation forward
     * and the graphics view display to visually show Box2D elements interacting/moving in the world
     */
    void advance();

    /**
     * @brief randomFloat Helper method to generate a random float between a range
     * @param min Minimum value
     * @param max Maximum value
     * @return Random float
     */
    float randomFloat(float min, float max);

    /**
     * @brief removeBodies Remove all bodies once they are no longer needed
     */
    //void removeBodies();

    QPixmap *coinPixmap;

    void spawnNextCoin();

    void onWinSpawnCoins(QPointF position);

protected:
    /**
     * @brief mousePressEvent Responsible for creating a Box2D object on mouse click including the body, shape and fixture such that the
     * element can be simulated in the world scene
     * @param event Mouse button pressed
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    /**
     * @brief m_world The physics world where our Box2D bodies are instantiated
     */
    b2World *m_world;

    /**
     * @brief m_timeStep Determines how much the physics world moves per second
     * The value is equivalent to 60 fps
     */
    float32 m_timeStep = 1.0f/60.0f;

    /**
     * @brief m_velocityIterations
     */
    int32 m_velocityIterations = 6;

    /**
     * @brief m_positionIterations Stabilizes the position shifting
     */
    int32 m_positionIterations = 2;

    /**
     * @brief pixels_PerMeter The conversion factor between pixels and meters
     * Used to convert/translate the coordinates and position values between Qt's and Box2D's coordinate systems
     */
    const float pixels_PerMeter = 50.0f;

    /**
     * @brief WORLD_WIDTH Width bounds of the Box 2D Physics World (in meters)
     */
    const float WORLD_WIDTH = 20.0f;

    /**
     * @brief WORLD_HEIGHT Height bounds of the Box 2D Physics World (in meters)
     */
    const float WORLD_HEIGHT = 15.0f;

    /**
     * @brief m_coinQueue Stores the pending coin positions
     */
    QQueue<QPointF> m_coinQueue;

    /**
     * @brief m_coinTimer Controls the spawn timing of coins
     */
    QTimer* m_coinTimer;

    /**
     * @brief m_coinsPerSecond Adjusts spawn rate
     */
    int m_coinsPerSecond = 10;

signals:

};

#endif // BOX2DBASE_H
