#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    CCLOG("-----------NEW SCENE---------");
    auto scene = Scene::createWithPhysics();
    
    // Comentar o buscar manera de solo ejecutar cuando este en debug...   <---
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld( )->setGravity( Vect( 0, -98 ) );
    
    auto layer = GameScene::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());
    
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    // Background
    //backgrounds = Node::create();
    
    background1 = Sprite::create("background.png");
    background1->setPosition(Point( visibleSize.width/2 , visibleSize.height/2) );
    background1->setFlippedX(true);
    //background1->setPosition(Point( visibleSize.width/2 , visibleSize.height/2) );
    //background1->setFlippedX(true);
    background2 = Sprite::create("background.png");
    background2->setPosition(Point( visibleSize.width/2 + BACKGROUND_WIDTH, visibleSize.height/2) );
    //background2->setFlippedX(true);
    
    //backgrounds->addChild(background1);
    //backgrounds->addChild(background2);

    auto edgeBody = PhysicsBody::createEdgeBox(Size(visibleSize.width*2, visibleSize.height*2), PHYSICSBODY_MATERIAL_DEFAULT, 10);
    edgeBody->setCollisionBitmask( EDGE_COLLISION_BITMASK );
    edgeBody->setContactTestBitmask( true );
    
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point( visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y ));
    edgeNode->setPhysicsBody(edgeBody);
    
    // Temporal
    backButton = MenuItemFont::create("Back", CC_CALLBACK_0(GameScene::goToMainMenu, this));
    backButton->setFontSizeObj(100);
    
    Menu *menu = Menu::create(backButton, NULL);
    menu->setPosition(Point(0 + backButton->getContentSize().width, visibleSize.height - backButton->getContentSize().height/2));
    //
    
    scoreLabel = Label::createWithTTF("Score: 0","Marker Felt.ttf",100);
    scoreLabel->setPosition(Point(visibleSize.width/2,visibleSize.height - scoreLabel->getContentSize().height/2));

    rabbit = new Rabbit(this);
    platform = new Platform();
    platforms = Node::create();
    
    for(int i=0; i<TOTAL_PLATFORMS; i++)
    {
        platform->SpawnPlatform(platforms, i);
    }
    
    cloudFactory = new Cloud();
    for(auto i =0; i<INITIAL_RANDOM_CLOUDS_COUNT; i++){
        cloudFactory->spawnCloud(this, false);
    }
    schedule(schedule_selector(GameScene::addClouds), ADDING_CLOUDS_TIME);
    
    // Adding movement buttons
    oneMovementButton = Sprite::create("button.png");
    twoMovementButton = Sprite::create("button.png");
    
    oneMovementButton->setAnchorPoint(Point(0,0));
    oneMovementButton->setPosition(40, 40);
    
    twoMovementButton->setAnchorPoint(Point(1,0));
    twoMovementButton->setPosition(visibleSize.width - 40, 40);
    
    auto contactListener = EventListenerPhysicsContact::create( );
    contactListener->onContactBegin = CC_CALLBACK_1( GameScene::onContactBegin, this );
    Director::getInstance( )->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( contactListener, this );
    
    auto touchListener = EventListenerTouchOneByOne::create( );
    touchListener->setSwallowTouches( true );
    touchListener->onTouchBegan = CC_CALLBACK_2( GameScene::onTouchBegan, this );
    Director::getInstance( )->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( touchListener, this );
    
    this->addChild(scoreLabel,100);
    this->addChild(oneMovementButton,200);
    this->addChild(twoMovementButton,200);
    
    this->addChild(platforms, 100);
    this->addChild(menu, 100);
    this->addChild(edgeNode, 1);
    this->addChild(background1);
    this->addChild(background2);
    
    lastPosition = TOTAL_PLATFORMS;
    whichBackground = false;
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("jumping.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("falling.mp3");
    return true;
}

void GameScene::goToMainMenu()
{
    Director::getInstance()->replaceScene(MainMenuScene::createScene());
}

void GameScene::SetPhysicsWorld(cocos2d::PhysicsWorld *world)
{
    this->world = world;
}

bool GameScene::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event )
{
    Vec2 p = touch->getLocation();
    Rect rectOne = oneMovementButton->getBoundingBox();
    Rect rectTwo = twoMovementButton->getBoundingBox();
    
    if(rectOne.containsPoint(p))
    {
        if (!rabbit->isJumping && !rabbit->isFalling) {
            
            CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( "jumping.mp3" );
            CCLOG("click on onemovement");
            rabbit->jumpByOne();
        
            DelayTime::create(0.3f);

                if (background2->getPositionX() <= -(BACKGROUND_WIDTH-(BACKGROUND_MOVEMENT*4))) {
                    CCLOG("%f<=%i",background2->getPositionX(),-(BACKGROUND_WIDTH-(BACKGROUND_MOVEMENT*4)));
                    /*background1->setPosition(Point( this->visibleSize.width/2, this->visibleSize.height/2) );*/
                    background2->setPosition(Point( visibleSize.width/2 + BACKGROUND_WIDTH, visibleSize.height/2) );
                    //background2->setPositionX(visibleSize.width/2);
                }
                if (background1->getPositionX() <= -(BACKGROUND_WIDTH-(BACKGROUND_MOVEMENT*4))) {
                    CCLOG("%f<=%i",background1->getPositionX(),-(BACKGROUND_WIDTH-(BACKGROUND_MOVEMENT*4)));
                    /*background2->setPosition(Point( this->visibleSize.width/2, this->visibleSize.height/2) );*/
                    background1->setPosition(Point( visibleSize.width/2 + BACKGROUND_WIDTH, visibleSize.height/2) );
                    //background1->setPositionX(visibleSize.width/2);
                }
            
            auto movePlatform = MoveBy::create( 0.0001f * (PLATFORM_WIDTH*8), Point( -PLATFORM_WIDTH, 0 ));
            auto platformsAction = Sequence::create(DelayTime::create(0.05f), movePlatform, NULL);
        
            platforms->runAction( platformsAction );
            auto movePlatform2 = MoveBy::create( 0.0001f * (PLATFORM_WIDTH*8), Point( -(PLATFORM_WIDTH*2), 0 ));
            auto platformsAction2 = Sequence::create(DelayTime::create(0.05f), movePlatform2, NULL);
            
            background1->runAction( platformsAction2 );
            
            auto movePlatform3 = MoveBy::create( 0.0001f * (PLATFORM_WIDTH*8), Point( -(PLATFORM_WIDTH*2), 0 ));
            auto platformsAction3 = Sequence::create(DelayTime::create(0.05f), movePlatform3, NULL);
            
            background2->runAction( platformsAction3 );
            platform->SpawnPlatform(platforms, lastPosition);
            
            lastPosition+=1;
            
            
            
            addToScore(1);

            return true;
        }
        return false; // to indicate that we have consumed it.
    }
    if(rectTwo.containsPoint(p))
    {
        if (!rabbit->isJumping && !rabbit->isFalling) {
            
            CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( "jumping.mp3" );
            CCLOG("click on twomovement");
            rabbit->jumpByTwo();
        
            auto movePlatform = MoveBy::create( 0.0001f * (PLATFORM_WIDTH*8), Point( -(PLATFORM_WIDTH*2), 0 ));
            auto platformsAction = Sequence::create(DelayTime::create(0.05f), movePlatform, NULL);
            
            platforms->runAction( platformsAction );
            
            auto movePlatform2 = MoveBy::create( 0.0001f * (PLATFORM_WIDTH*8), Point( -(PLATFORM_WIDTH*2), 0 ));
            auto platformsAction2 = Sequence::create(DelayTime::create(0.05f), movePlatform2, NULL);
            
            background1->runAction( platformsAction2 );
            
            auto movePlatform3 = MoveBy::create( 0.0001f * (PLATFORM_WIDTH*8), Point( -(PLATFORM_WIDTH*2), 0 ));
            auto platformsAction3 = Sequence::create(DelayTime::create(0.05f), movePlatform3, NULL);
            
            background2->runAction( platformsAction3 );
            
            platform->SpawnPlatform(platforms, lastPosition);
            platform->SpawnPlatform(platforms, lastPosition+1);
            
            
            lastPosition+=2;
            
            if (background2->getPositionX() <= -(BACKGROUND_WIDTH-(BACKGROUND_MOVEMENT*4))) {
                CCLOG("%f<=%i",background2->getPositionX(),-(BACKGROUND_WIDTH-(BACKGROUND_MOVEMENT*4)));
                /*background1->setPosition(Point( this->visibleSize.width/2, this->visibleSize.height/2) );*/
                background2->setPosition(Point( visibleSize.width/2 + BACKGROUND_WIDTH, visibleSize.height/2) );
                //background2->setPositionX(visibleSize.width/2);
            }
            if (background1->getPositionX() <= -(BACKGROUND_WIDTH-(BACKGROUND_MOVEMENT*4))) {
                CCLOG("%f<=%i",background1->getPositionX(),-(BACKGROUND_WIDTH-(BACKGROUND_MOVEMENT*4)));
                /*background2->setPosition(Point( this->visibleSize.width/2, this->visibleSize.height/2) );*/
                background1->setPosition(Point( visibleSize.width/2 + BACKGROUND_WIDTH, visibleSize.height/2) );
                //background1->setPositionX(visibleSize.width/2);
            }
            
            
            addToScore(2);

            return true;
        }
        return false; // to indicate that we have consumed it.
    }
    
    return false;
}

bool GameScene::onContactBegin( cocos2d::PhysicsContact &contact )
{
    PhysicsBody *a = contact.getShapeA( )->getBody();
    PhysicsBody *b = contact.getShapeB( )->getBody();
    
    if ( ( EDGE_COLLISION_BITMASK == a->getCollisionBitmask( ) && RABBIT_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( EDGE_COLLISION_BITMASK == b->getCollisionBitmask( ) && RABBIT_COLLISION_BITMASK == a->getCollisionBitmask() ) )
    {
        auto scene = MainMenuScene::createScene();
        
        unscheduleAllSelectors();
        GameData::getInstance()->addScore(this->score);
        Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
    }
    if ( ( NO_PLATFORM_COLLISION_BITMASK == a->getCollisionBitmask( ) && RABBIT_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( NO_PLATFORM_COLLISION_BITMASK == b->getCollisionBitmask( ) && RABBIT_COLLISION_BITMASK == a->getCollisionBitmask() ) )
    {
        CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( "falling.mp3" );
        
        CCLOG("CAIIIIII");
        rabbit->isFalling = true;
        this->getScene()->getPhysicsWorld()->setGravity(Vect(0, -1080));
        this->getScene()->getPhysicsWorld()->setSpeed(3.0f);
        if (a->getCollisionBitmask() == NO_PLATFORM_COLLISION_BITMASK) {
            a->removeFromWorld();
        }
        if (b->getCollisionBitmask() == NO_PLATFORM_COLLISION_BITMASK) {
            b->removeFromWorld();
        }
    }
    
    return true;
}

void GameScene::addToScore(int amountOfJumps)
{
    this->score += amountOfJumps;
    
    auto scoreString = __String::createWithFormat( "Score: %i", score );
    scoreLabel->setString(scoreString->getCString());
}

void GameScene::addClouds(float dt) {
    int rnd = arc4random() % 2;
    if (rnd == 1) {
        for(auto i =0; i<LATER_RANDOM_CLOUDS_COUNT; i++){
            cloudFactory->spawnCloud(this, true);
        }
    }
}

void GameScene::moveBackground(float dt) {
    /*if (backgroundDirection) { //Hacia adelante
        auto moveBy = MoveBy::create(MOVE_BACKGROUND_TIME, Point(BACKGROUND_MOVEMENT, 0));
        background->runAction(moveBy);
    } else { //Hacia atras
        auto moveBy = MoveBy::create(MOVE_BACKGROUND_TIME, Point(-BACKGROUND_MOVEMENT, 0));
        background->runAction(moveBy);
    }
    
    backgroundDirection = !backgroundDirection;*/
}
