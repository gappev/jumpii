#ifndef __GAME_SCENE_SCENE_H__
#define __GAME_SCENE_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    
    CREATE_FUNC(GameScene);
};

#endif // __GameScene_SCENE_H__
