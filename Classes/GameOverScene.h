#ifndef __GameOverScene_SCENE_H__
#define __GameOverScene_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(GameOverScene);
};

#endif // __GameOverScene_SCENE_H__
