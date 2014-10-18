#include "LeaderBoardScene.h"

USING_NS_CC;

Scene* LeaderBoardScene::createScene()
{
    auto scene = Scene::create();
    auto layer = LeaderBoardScene::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool LeaderBoardScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    
    
    return true;
}
