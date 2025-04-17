#ifndef BOX2DPHYSICSSCENE_H
#define BOX2DPHYSICSSCENE_H

#include <QGraphicsScene>
#include <Box2D/Box2D.h>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QRandomGenerator>
#include <QDebug>
#include <QTimer>

class box2dPhysicsScene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit box2dPhysicsScene(QObject *parent = nullptr);
    ~box2dPhysicsScene();

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

    void removeBodies();

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
};

#endif // BOX2DPHYSICSSCENE_H
