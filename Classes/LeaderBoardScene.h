#ifndef __LEADER_BOARD_SCENE_H__
#define __LEADER_BOARD_SCENE_H__

#include "cocos2d.h"

class LeaderBoardScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    
    CREATE_FUNC(LeaderBoardScene);
};

#endif // __LeaderBoardScene_SCENE_H__
