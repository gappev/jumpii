#include "LeaderBoardScene.h"

USING_NS_CC;

CCScene* LeaderBoardScene::scene()
{
    CCScene *scene = CCScene::create();
    LeaderBoardScene *layer = LeaderBoardScene::create();
    scene->addChild(layer);
    return scene;
}

bool LeaderBoardScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    return true;
}


void LeaderBoardScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}