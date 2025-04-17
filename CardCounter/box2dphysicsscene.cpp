#include "box2dphysicsscene.h"

box2dPhysicsScene::box2dPhysicsScene(QObject *parent) : QGraphicsScene{parent},
    m_world(new b2World(b2Vec2(0.0f, 9.8f))),  // initialize the world
    m_timeStep(1.0f/60.0f),
    m_velocityIterations(6),
    m_positionIterations(2)
{
    // Physics world dimensions (in meters)
    const float WORLD_WIDTH = 20.0f;
    const float WORLD_HEIGHT = 15.0f;

    // // Create ground body (position it at the bottom)
    // b2BodyDef groundBodyDef;
    // // groundBodyDef.position.Set(0.0f, WORLD_HEIGHT - 1.0f); // 1m thick ground
    // // b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

    // groundBodyDef.position.Set(WORLD_WIDTH/2.0f, WORLD_HEIGHT - 1.0f); // Centered at middle of ground
    // b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

    // // Create the groundBody fixture
    // b2PolygonShape groundBox;
    // groundBox.SetAsBox(WORLD_WIDTH/2.0f, 1.0f); // Full width
    // groundBody->CreateFixture(&groundBox, 0.0f);

    // // // Create a grund body shape - DEBUG
    // // QGraphicsRectItem *groundShape = new QGraphicsRectItem(-0.5f * pixels_PerMeter, -0.5f * pixels_PerMeter, pixels_PerMeter, pixels_PerMeter);
    // // groundShape->setBrush(Qt::gray);
    // // addItem(groundShape);

    // // // Link physics and graphics
    // // groundBody->SetUserData(groundShape);

    // float groundWidth = WORLD_WIDTH * pixels_PerMeter;
    // float groundHeight = 2.0f * pixels_PerMeter; // 2m tall (1m up and down from center)
    // float groundX = 0; // Scene coordinates start at 0
    // float groundY = (WORLD_HEIGHT - 2.0f) * pixels_PerMeter; // Position at bottom

    // QGraphicsRectItem *groundShape = new QGraphicsRectItem(groundX, groundY, groundWidth, groundHeight);
    // groundShape->setBrush(Qt::blue);
    // addItem(groundShape);

    // // Link physics and graphics
    // groundBody->SetUserData(groundShape);

    // // Set graphics scene size to match physics world
    // setSceneRect(0, 0, WORLD_WIDTH * pixels_PerMeter, WORLD_HEIGHT * pixels_PerMeter);
    // Create ground body (position it at the bottom)

    // b2BodyDef groundBodyDef;
    // groundBodyDef.position.Set(WORLD_WIDTH/2.0f, WORLD_HEIGHT - 1.0f); // Centered X, 1m from bottom
    // b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

    // // Create the groundBody fixture
    // b2PolygonShape groundBox;
    // groundBox.SetAsBox(WORLD_WIDTH/2.0f, 1.0f); // Full width, 2m tall (1m up and down from center)
    // groundBody->CreateFixture(&groundBox, 0.0f);

    // // Create graphics item for ground
    // float groundWidth = WORLD_WIDTH * pixels_PerMeter;
    // float groundHeight = 2.0f * pixels_PerMeter; // 2m tall (1m up and down from center)
    // float groundX = 0; // Scene coordinates start at 0
    // float groundY = (WORLD_HEIGHT - 2.0f) * pixels_PerMeter; // Position at bottom

    // QGraphicsRectItem *groundShape = new QGraphicsRectItem(groundX, groundY, groundWidth, groundHeight);
    // groundShape->setBrush(Qt::gray);
    // groundShape->setPen(Qt::NoPen); // Remove border
    // addItem(groundShape);

    // // Link physics and graphics
    // groundBody->SetUserData(groundShape);

    // Set graphics scene size to match physics world
    setSceneRect(0, 0, WORLD_WIDTH * pixels_PerMeter, WORLD_HEIGHT * pixels_PerMeter);

    // qDebug() << "Ground position:" << groundX << groundY;
    // qDebug() << "Ground size:" << groundWidth << groundHeight;
    // qDebug() << "Scene rect:" << sceneRect();

}

box2dPhysicsScene::~box2dPhysicsScene()
{
    // Clean up all QGraphicsItems
    clear();

    // Delete Box2D world
    delete m_world;
}

float box2dPhysicsScene::randomFloat(float min, float max){
    return static_cast<float>(QRandomGenerator::global()->generateDouble() * (min - max) + min);
}

void box2dPhysicsScene::advance(){
    if (!m_world) return; // if the world doesnt exist

    // Step the physics simulation forward
    m_world->Step(m_timeStep, m_velocityIterations, m_positionIterations);

    // Update graphics items
    for (b2Body* body = m_world->GetBodyList(); body; body = body->GetNext())
    {
        if (body->GetUserData())
        {
            QGraphicsItem* item = static_cast<QGraphicsItem*>(body->GetUserData());
            b2Vec2 position = body->GetPosition();
            item->setPos(position.x * pixels_PerMeter,
                         position.y * pixels_PerMeter);
            item->setRotation(body->GetAngle() * 180.0f / b2_pi);
        }
    }

    QGraphicsScene::advance();
}

void box2dPhysicsScene::removeBodies(){
    if (!m_world) return;

    for (b2Body *body = m_world->GetBodyList(); body; body = body->GetNext()){
        b2Body* next = body->GetNext();

        if (body->GetUserData()) {
            QGraphicsItem* item = static_cast<QGraphicsItem*>(body->GetUserData());
            removeItem(item);
            delete item;
        }

        // Destroy the physics body
        m_world->DestroyBody(body);
        body = next;
    }
}

void box2dPhysicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() != Qt::LeftButton) {
        QGraphicsScene::mousePressEvent(event);
        return;
    }

    QTimer* deleteTimer = new QTimer(this);
    connect(deleteTimer, &QTimer::timeout, this, &box2dPhysicsScene::removeBodies);
    deleteTimer->start(1000/20);

    for (int i = 0; i < 40; i++){
        QPointF clickPos = event->scenePos();
        float32 x = clickPos.x() / pixels_PerMeter;
        float32 y = clickPos.y() / pixels_PerMeter;

        // Create body
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(x, y);
        bodyDef.linearDamping = 0.3f;    // Air resistance
        bodyDef.angularDamping = 0.1f;   // Prevent excessive spinning
        b2Body* body = m_world->CreateBody(&bodyDef);

        // Create the shape
        b2CircleShape coin;
        coin.m_p.Set(0.0f, 0.0f);
        coin.m_radius = 0.5f;

        // Create fixture -> connects shapes to bodies
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &coin;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.4f;
        fixtureDef.restitution = 0.3f;
        body->CreateFixture(&fixtureDef);

        // Create graphics item
        // QGraphicsEllipseItem *coinObj = new QGraphicsEllipseItem(-0.5f * pixels_PerMeter, -0.5f * pixels_PerMeter, pixels_PerMeter, pixels_PerMeter);
        QGraphicsEllipseItem *coinObj = new QGraphicsEllipseItem(
            -coin.m_radius * pixels_PerMeter,
            -coin.m_radius * pixels_PerMeter,
            2 * coin.m_radius * pixels_PerMeter,
            2 * coin.m_radius * pixels_PerMeter
            );
        coinObj->setPos(clickPos);
        coinObj->setBrush(Qt::yellow);
        addItem(coinObj);

        // Link physics and graphics
        body->SetUserData(coinObj);

        // float randx = randomFloat(0.0f, 16.0f);
        // float randy = randomFloat(-4.0f, 8.0f);  // Mostly upward force

        float randx = static_cast<float>(QRandomGenerator::global()->generateDouble() * 16.0 - 8.0);
        float randy = static_cast<float>(QRandomGenerator::global()->generateDouble() * 5.0 - 16.0);
        body->ApplyLinearImpulse(b2Vec2(randx, randy), body->GetWorldCenter(), true);

        // float randx = static_cast<float>(QRandomGenerator::global()->generateDouble() * 16.0 - 8.0);
        // float randy = static_cast<float>(QRandomGenerator::global()->generateDouble() * 5.0 - 8.0);
        // body->ApplyLinearImpulse(b2Vec2(randx, randy), body->GetWorldCenter(), true);
    }

    QGraphicsScene::mousePressEvent(event);
}
