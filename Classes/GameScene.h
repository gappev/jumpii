#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"
#include "GameData.h"
#include "MainMenuScene.h"

using namespace cocos2d;

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(GameScene);
    
private:
    // Properties
    PhysicsWorld *world;
    Sprite *background;
    MenuItemFont *backButton;
    
    // Functions
    void SetPhysicsWorld ( PhysicsWorld *world );
    void goToMainMenu();
};

#endif // __GameScene_SCENE_H__
