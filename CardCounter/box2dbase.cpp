#include "box2dbase.h"

box2Dbase::box2Dbase(QObject *parent) : QGraphicsScene{parent},
    coinPixmap(new QPixmap(":/cash/otherimg/coin.png")),  // initialize the world
    m_world(new b2World(b2Vec2(0.0f, 9.8f))),
    m_timeStep(1.0f/60.0f),
    m_velocityIterations(6),
    m_positionIterations(2)
{
    m_coinTimer = new QTimer(this);
    connect(m_coinTimer, &QTimer::timeout, this, &box2Dbase::spawnNextCoin);

    setBackgroundBrush(Qt::transparent);

    // // Create ground body (position it at the bottom)
    // b2BodyDef groundBodyDef;
    // groundBodyDef.position.Set(WORLD_WIDTH/2.0f, WORLD_HEIGHT - 1.0f); // Centered X, 1m from bottom
    // b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

    // // Create the groundBody fixture
    // b2PolygonShape groundBox;
    // groundBox.SetAsBox(WORLD_WIDTH/2.0f, 1.0f); // Full width, 2m tall (1m up and down from center)
    // groundBody->CreateFixture(&groundBox, 0.0f);

    // // Create graphics item for ground
    // float groundWidth = WORLD_WIDTH * pixels_PerMeter;
    // float groundHeight = 2.0f * pixels_PerMeter;
    // float groundX = 0;
    // float groundY = (WORLD_HEIGHT - 2.0f) * pixels_PerMeter;

    // QGraphicsRectItem *groundShape = new QGraphicsRectItem(groundX, groundY, groundWidth, groundHeight);
    // groundShape->setBrush(Qt::gray);
    // groundShape->setPen(Qt::NoPen);
    // addItem(groundShape);

    // // Link physics and graphics
    // groundBody->SetUserData(groundShape);

    // Set graphics scene size to match physics world
    setSceneRect(0, 0, WORLD_WIDTH * pixels_PerMeter, WORLD_HEIGHT * pixels_PerMeter);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &box2Dbase::advance);
    timer->start(1000 / 60); // ~60 FPS
}

box2Dbase::~box2Dbase(){
    // Clean up all QGraphicsItems
    clear();

    // Delete Box2D world
    delete m_world;
}

float box2Dbase::randomFloat(float min, float max){
    return static_cast<float>(QRandomGenerator::global()->generateDouble() * (min - max) + min);
}

void box2Dbase::advance(){
    if (!m_world) return; // if the world doesnt exist

    // step physics simulation forward
    m_world->Step(m_timeStep, m_velocityIterations, m_positionIterations);

    // vector of all bodies that have left world bounds
    QVector<b2Body*> bodiesToDelete;

    // iterate through all current bodies spawned
    for (b2Body* body = m_world->GetBodyList(); body; body = body->GetNext()) {
        if (body->GetType() != b2_dynamicBody) continue;
        b2Vec2 position = body->GetPosition();

        // out of world bounds check
        if (position.x < 0 || position.x > WORLD_WIDTH ||
            position.y < 0 || position.y > WORLD_HEIGHT) {
            bodiesToDelete.append(body);
        }
    }

    for (b2Body* body : bodiesToDelete) {
        if (body->GetUserData()) {
            QGraphicsItem* item = static_cast<QGraphicsItem*>(body->GetUserData());
            removeItem(item);  // Remove from scene
            delete item;       // Free memory

            //qDebug() << "body deleted";
        }
        m_world->DestroyBody(body);  // Remove from physics world
    }

    // update graphics items
    for (b2Body* body = m_world->GetBodyList(); body; body = body->GetNext()){
        if (body->GetUserData()){
            QGraphicsItem* item = static_cast<QGraphicsItem*>(body->GetUserData());
            b2Vec2 position = body->GetPosition();
            item->setPos(position.x * pixels_PerMeter,
                         position.y * pixels_PerMeter);
            item->setRotation(body->GetAngle() * 180.0f / b2_pi);
        }
    }

    QGraphicsScene::advance();
}

void box2Dbase::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() != Qt::LeftButton) {
        QGraphicsScene::mousePressEvent(event);
        return;
    }

    // Queue coins with horizontal spread (like a real slot)
    const float slotWidth = 30.0f;

    for (int i = 0; i < 40; i++) {
        float offset = randomFloat(-slotWidth/2, slotWidth/2);
        m_coinQueue.enqueue(event->scenePos() + QPointF(offset, 0));
    }

    for (int i = 0; i < 40; i++) {
        // 1. Create physics body (circle shape)
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(event->scenePos().x() / pixels_PerMeter, event->scenePos().y() / pixels_PerMeter);
        b2Body* body = m_world->CreateBody(&bodyDef);

        // 2. Create CIRCULAR physics shape (matches image dimensions)
        b2CircleShape circleShape;
        circleShape.m_radius = coinPixmap->width() / (2 * pixels_PerMeter); // Convert pixels to meters

        // 3. Create fixture
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circleShape;  // Use the circle shape, not the pixmap
        fixtureDef.density = 3.5f;
        fixtureDef.friction = 0.5f;
        fixtureDef.restitution = 0.5f;
        body->CreateFixture(&fixtureDef);

        // 4. Create graphics (PNG)
        QGraphicsPixmapItem *coinItem = new QGraphicsPixmapItem(*coinPixmap);
        coinItem->setOffset(-coinPixmap->width()/2, -coinPixmap->height()/2);
        coinItem->setPos(event->scenePos());
        addItem(coinItem);

        // 5. Link physics and graphics
        body->SetUserData(coinItem);

        float randx = static_cast<float>(QRandomGenerator::global()->generateDouble() * 16.0 - 8.0);
        float randy = static_cast<float>(QRandomGenerator::global()->generateDouble() * 5.0 - 16.0);
        body->ApplyLinearImpulse(b2Vec2(randx, randy), body->GetWorldCenter(), true);
    }

    // Start with rapid initial burst
    if (!m_coinTimer->isActive()) {
        m_coinTimer->start(50); // First coins fast
        QTimer::singleShot(300, [this]() {
            m_coinTimer->setInterval(1000 / m_coinsPerSecond); // Then slower
        });
    }

    QGraphicsScene::mousePressEvent(event);
}

void box2Dbase::onWinSpawnCoins(QPointF position, int coinsToSpawn) {
    // Clear any existing coins first
    m_coinQueue.clear();

    // Queue coins with vertical spread (like a slot machine payout)
    const float payoutWidth = 60.0f; // Wider spread for celebration

    for (int i = 0; i < coinsToSpawn; i++) {
        float offset = randomFloat(-payoutWidth/2, payoutWidth/2);
        m_coinQueue.enqueue(position + QPointF(offset, 0));
    }

    // Start spawning with celebratory timing
    initialBurst();

    if (!m_coinTimer->isActive()) {
        m_coinTimer->start(100); // Slightly slower for visibility
    }

}

void box2Dbase::spawnNextCoin() {
    if (m_coinQueue.isEmpty()) { // if queue is empty stop the timer
        m_coinTimer->stop();
        return;
    }

    QPointF pos = m_coinQueue.dequeue();

    // Physics setup
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x() / pixels_PerMeter, pos.y() / pixels_PerMeter);
    bodyDef.angularDamping = 0.2f;  // resist spinning
    bodyDef.linearDamping = 0.4f;   // air resistance
    b2Body* body = m_world->CreateBody(&bodyDef);

    // shape setup
    b2CircleShape circle;
    circle.m_radius = coinPixmap->width() / (2.5f * pixels_PerMeter); // Slightly smaller than visual

    // fixture setup
    b2FixtureDef fixture;
    fixture.shape = &circle;
    fixture.density = 2.0f;      // Very heavy coins
    fixture.friction = 0.4f;     // High friction
    fixture.restitution = 0.4f;  // Minimal bounce
    body->CreateFixture(&fixture);

    QGraphicsPixmapItem* coin = new QGraphicsPixmapItem(*coinPixmap);
    coin->setOffset(-coinPixmap->width()/2, -coinPixmap->height()/2);
    coin->setPos(pos);
    addItem(coin);
    body->SetUserData(coin);

    float angle = QRandomGenerator::global()->bounded(-20, 20) * (M_PI/180);
    float force = 4.0f + QRandomGenerator::global()->bounded(2.0f);

    body->ApplyLinearImpulse(b2Vec2(force * sin(angle), -force * cos(angle)), body->GetWorldCenter(), true);
}

void box2Dbase::initialBurst(){
    // Queue coins with horizontal spread (like a real slot)
    const float slotWidth = 30.0f;
    QPointF position;

    for (int i = 0; i < 40; i++) {
        float offset = randomFloat(-slotWidth/2, slotWidth/2);
        position = QPointF(540, 740) + QPointF(offset, 0);
        m_coinQueue.enqueue(position);
    }

    for (int i = 0; i < 40; i++) {
        // 1. Create physics body (circle shape)
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(position.x() / pixels_PerMeter, position.y() / pixels_PerMeter);
        b2Body* body = m_world->CreateBody(&bodyDef);

        // 2. Create CIRCULAR physics shape (matches image dimensions)
        b2CircleShape circleShape;
        circleShape.m_radius = coinPixmap->width() / (2 * pixels_PerMeter); // Convert pixels to meters

        // 3. Create fixture
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circleShape;  // Use the circle shape, not the pixmap
        fixtureDef.density = 3.5f;
        fixtureDef.friction = 0.5f;
        fixtureDef.restitution = 0.5f;
        body->CreateFixture(&fixtureDef);

        // 4. Create graphics (PNG)
        QGraphicsPixmapItem *coinItem = new QGraphicsPixmapItem(*coinPixmap);
        coinItem->setOffset(-coinPixmap->width()/2, -coinPixmap->height()/2);
        coinItem->setPos(position);
        addItem(coinItem);

        // 5. Link physics and graphics
        body->SetUserData(coinItem);

        float randx = static_cast<float>(QRandomGenerator::global()->generateDouble() * 16.0 - 8.0);
        float randy = static_cast<float>(QRandomGenerator::global()->generateDouble() * 5.0 - 16.0);
        body->ApplyLinearImpulse(b2Vec2(randx, randy), body->GetWorldCenter(), true);
    }

    // Start with rapid initial burst
    if (!m_coinTimer->isActive()) {
        m_coinTimer->start(50); // First coins fast
        QTimer::singleShot(300, [this]() {
            m_coinTimer->setInterval(1000 / m_coinsPerSecond); // Then slower
        });
    }
}
