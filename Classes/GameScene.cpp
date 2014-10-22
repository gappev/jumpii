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
    background = Sprite::create("background.png");
    background->setPosition(Point( visibleSize.width/2 , visibleSize.height/2) );
    
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
    this->addChild(menu, 1);
    
    this->addChild(background);
    
    lastPosition = TOTAL_PLATFORMS;
    
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

            
            auto movePlatform = MoveBy::create( 0.0001f * (PLATFORM_WIDTH*8), Point( -PLATFORM_WIDTH, 0 ));
            auto platformsAction = Sequence::create(DelayTime::create(0.05f), movePlatform, NULL);
        
            platforms->runAction( platformsAction );
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
            platform->SpawnPlatform(platforms, lastPosition);
            platform->SpawnPlatform(platforms, lastPosition+1);
            lastPosition+=2;
            
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
