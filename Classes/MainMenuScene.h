#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "Definitions.h"

using namespace cocos2d;

class MainMenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(MainMenuScene);
    
private:
    // Properties
    MenuItemFont *playButton;
    
    // Functions
    void startGame();
};

#endif // __HELLOWORLD_SCENE_H__
