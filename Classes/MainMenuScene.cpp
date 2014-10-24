#include "MainMenuScene.h"

USING_NS_CC;

MainMenuScene::~MainMenuScene() {
    unscheduleAllSelectors();
}

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

    background = Sprite::create("background.png");
    background->setPosition(Point( visibleSize.width/2 , visibleSize.height/2) );
    
    logo = Sprite::create("logo.png");
    logo->setPosition(Point(visibleSize.width/2, (visibleSize.height/4)*3 ));


    playButton = MenuItemFont::create("Tap To Start", CC_CALLBACK_0(MainMenuScene::startGame, this));
    playButton->setFontSizeObj(100);
    
    Menu *menu = Menu::create(playButton, NULL);
    menu->setPosition(Point(visibleSize.width/2, visibleSize.height/4));
    
    cloudFactory = new Cloud();
    for(auto i =0; i<INITIAL_RANDOM_CLOUDS_COUNT; i++){
        cloudFactory->spawnCloud(this, false);
    }
    schedule(schedule_selector(MainMenuScene::addClouds), ADDING_CLOUDS_TIME);
    
    this->addChild(logo,10);
    this->addChild(background);
    this->addChild(menu, 1);
    return true;
}

void MainMenuScene::startGame()
{
    unscheduleAllSelectors();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, GameScene::createScene()));
}

void MainMenuScene::addClouds(float dt) {
    int rnd = arc4random() % 2;
    if (rnd == 1) {
        for(auto i =0; i<LATER_RANDOM_CLOUDS_COUNT; i++){
            cloudFactory->spawnCloud(this, true);
        }
    }
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
