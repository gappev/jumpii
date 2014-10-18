//
//  GameData.cpp
//  jumpii
//
//  Created by Jose Castellanos on 10/18/14.
//
//

#include "GameData.h"

GameData* GameData::instance = 0;

GameData::GameData()
{
    usr = UserDefault::getInstance();
    data = usr->getDataForKey(SCORES_DATA_KEY, Data() );
    
    if (!data.isNull()) {
        int* scoresArray = (int*)data.getBytes();
        int size = (int)data.getSize() / sizeof(int);
        for(int i=0; i<size; i++) {
            scores.push_back(scoresArray[i]);
            if (scoresArray[i] > highestScore) {
                highestScore = scoresArray[i];
            }
            CCLOG("scores[%i]: %i", i+1, scoresArray[i]);
        }
        if (size > 0) {
            lastScore = scoresArray[size-1];
        }
    }
}

GameData* GameData::getInstance()
{
    if(!instance)
        instance = new GameData();
    return instance;
}

vector<int> GameData::getScores() {
    return scores;
}

void GameData::addScore(int score) {
    scores.push_back(score);
    
    data.clear();
    data.copy((unsigned char*)scores.data(), scores.size()*sizeof(int));
    
    usr->setDataForKey(SCORES_DATA_KEY, data);
    usr->flush();
    
    lastScore = score;
    if (score > highestScore) {
        highestScore = score;
    }
}

void GameData::clearScores() {
    usr->setDataForKey(SCORES_DATA_KEY, Data());
    scores.clear();
    lastScore = -1;
    highestScore = -1;
}

int GameData::getLastScore() {
    return lastScore;
}

int GameData::getHighestScore() {
    return highestScore;
}