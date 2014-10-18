//
//  GameData.h
//  jumpii
//
//  Created by Jose Castellanos on 10/18/14.
//
//

#ifndef __jumpii__GameData__
#define __jumpii__GameData__

#include "cocos2d.h"
#include "Definitions.h"
#include <list>

using namespace cocos2d;
using namespace std;

class GameData
{
public:
    static GameData* getInstance();
    ~GameData();
    
    vector<int> getScores();
    void addScore(int score);
    int getLastScore();
    int getHighestScore();
    void clearScores();
    
private:
    GameData();
    static GameData* instance;
    
    vector<int> scores;
    
    UserDefault* usr;
    Data data;
    int lastScore = -1;
    int highestScore = -1;
};

#endif /* defined(__jumpii__GameData__) */
