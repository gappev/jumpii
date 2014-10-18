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


void LeaderBoardScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
