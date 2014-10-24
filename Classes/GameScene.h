#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"
#include "GameData.h"
#include "MainMenuScene.h"
#include "Rabbit.h"
#include "Platform.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "GameData.h"
#include "Cloud.h"

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
    Sprite *background1, *background2, *oneMovementButton, *twoMovementButton;
    MenuItemFont *backButton;
    Rabbit *rabbit;
    Node *platforms, *backgrounds;
    Platform *platform;
    Cloud *cloudFactory;
    Label *scoreLabel;
    bool whichBackground;
    int lastPosition;
    int score;
    Size visibleSize;
    Vec2 origin;
    
    // Functions
    void SetPhysicsWorld ( PhysicsWorld *world );
    void goToMainMenu();
    void addToScore(int amountOfJumps );
    void addClouds(float dt);
    void moveBackground(float dt);
    
    //Events
    bool onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event );
    bool onContactBegin( cocos2d::PhysicsContact &contact );
};

#endif // __GameScene_SCENE_H__
