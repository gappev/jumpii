#include "MainMenu.h"

USING_NS_CC;

CCScene* MainMenu::scene()
{
    CCScene *scene = CCScene::create();
    MainMenu *layer = MainMenu::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenu::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
 
    
    playButton = CCMenuItemFont::create("Tap to Start", this, menu_selector(MainMenu::startGame));
    playButton->setFontSize(14);
    
    
    CCMenu *mainMenu = CCMenu::create(playButton, NULL);
    mainMenu->alignItemsVertically();
    
    this->addChild(mainMenu);
    return true;
}

void MainMenu::startGame()
{
    CCDirector::sharedDirector()->replaceScene(GameScene::scene());
}


void MainMenu::menuCloseCallback(CCObject* pSender)
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
