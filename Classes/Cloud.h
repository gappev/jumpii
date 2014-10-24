//
//  Cloud.h
//  jumpii
//
//  Created by Richard Siwady on 10/21/14.
//
//

#ifndef __jumpii__Cloud__
#define __jumpii__Cloud__

#include "cocos2d.h"

using namespace cocos2d;

class Cloud
{
public:
    Cloud();
    
    void spawnCloud(Layer* layer, bool fromEdge);
        
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
};

#endif /* defined(__jumpii__Cloud__) */
