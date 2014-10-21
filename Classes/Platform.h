//
//  Platform.h
//  jumpii
//
//  Created by Richard Siwady on 10/18/14.
//
//

#ifndef __jumpii__Platform__
#define __jumpii__Platform__

#include "cocos2d.h"
#include "Definitions.h"

using namespace cocos2d;

class Platform
{
public:
    Platform();
    
    void SpawnPlatform( Node* layer, int pos );
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    bool isOKToAdd;
};

#endif /* defined(__jumpii__Platform__) */
