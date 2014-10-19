//
//  Rabit.h
//  jumpii
//
//  Created by Richard Siwady on 10/18/14.
//
//

#ifndef __jumpii__Rabit__
#define __jumpii__Rabit__

#include "cocos2d.h"
#include "Definitions.h"

using namespace cocos2d;

class Rabbit
{
public:
    Rabbit(Layer *layer);
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    Sprite *rabbit;
    
};

#endif /* defined(__jumpii__Rabit__) */
