#include "MainMenuScene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenuScene::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    playButton = MenuItemFont::create("Tap To Start", CC_CALLBACK_0(MainMenuScene::startGame, this));
    
    Menu *menu = Menu::create(playButton, NULL);
    menu->alignItemsVertically();
    
    this->addChild(menu);
    return true;
}

void MainMenuScene::startGame()
{
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameScene::createScene()));
}


void MainMenuScene::menuCloseCallback(Ref* pSender)
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
