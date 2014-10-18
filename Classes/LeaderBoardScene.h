#ifndef __LeaderBoardScene_SCENE_H__
#define __LeaderBoardScene_SCENE_H__

#include "cocos2d.h"

class LeaderBoardScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
        
    CREATE_FUNC(LeaderBoardScene);
};

#endif // __LeaderBoardScene_SCENE_H__
