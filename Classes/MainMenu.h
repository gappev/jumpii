#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"

using namespace cocos2d;

class MainMenu : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    
    CREATE_FUNC(MainMenu);
    
private:
    //Properties
    CCMenuItemFont *playButton;
    
    //Functions
    void startGame();
};

#endif // __MainMenu_SCENE_H__
