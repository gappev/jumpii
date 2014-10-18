#include "MainMenuScene.h"

USING_NS_CC;

CCScene* MainMenuScene::scene()
{
    CCScene *scene = CCScene::create();
    MainMenuScene *layer = MainMenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenuScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
 
    
    playButton = CCMenuItemFont::create("Tap to Start", this, menu_selector(MainMenuScene::startGame));
    playButton->setFontSize(14);
    
    
    CCMenu *mainMenu = CCMenu::create(playButton, NULL);
    mainMenu->alignItemsVertically();
    
    this->addChild(mainMenu);
    return true;
}

void MainMenuScene::startGame()
{
    CCDirector::sharedDirector()->replaceScene(GameScene::scene());
}


void MainMenuScene::menuCloseCallback(CCObject* pSender)
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
