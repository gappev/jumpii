#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    
    // Comentar o buscar manera de solo ejecutar cuando este en debug...   <---
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // Background
    background = Sprite::create("background.png");
    background->setPosition(Point( visibleSize.width/2 , visibleSize.height/2) );

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 10);
    
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point( visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y ));
    edgeNode->setPhysicsBody(edgeBody);
    
    // Temporal
    backButton = MenuItemFont::create("Back", CC_CALLBACK_0(GameScene::goToMainMenu, this));
    backButton->setFontSizeObj(100);
    
    Menu *menu = Menu::create(backButton, NULL);
    menu->setPosition(Point(visibleSize.width/2, visibleSize.height - backButton->getContentSize().height/2));
    //

    rabbit = new Rabbit(this);
    
    this->addChild(menu);
    this->addChild(edgeNode);
    this->addChild(background);
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
