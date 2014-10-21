//
//  Platform.cpp
//  jumpii
//
//  Created by Richard Siwady on 10/18/14.
//
//

#include "Platform.h"

Platform::Platform()
{
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );
    
    isOKToAdd = true;
}

void Platform::SpawnPlatform(cocos2d::Node *layer, int pos)
{
    if (pos >= TOTAL_PLATFORMS) {
        int rnd = arc4random() % 2;
        CCLOG("add: %i",rnd);
        if (isOKToAdd) {
            isOKToAdd = rnd == 1;
        } else {
            isOKToAdd = true;
        }
    }
    if (isOKToAdd) {
        auto platform = Sprite::create("platform-1.png");
        auto platformBody = PhysicsBody::createBox(Size(Point(platform->getContentSize().width, platform->getContentSize().height- PLATFORM_HEIGHT_GAP)));
    
        platformBody->setDynamic(false);
        platformBody->setContactTestBitmask(true);
    
        platform->setPhysicsBody(platformBody);
        int x =  origin.x + platform->getContentSize().width / 2 + (pos * platform->getContentSize().width) ;
        int y = origin.y + platform->getContentSize().height / 2;
        platform->setPosition(Point( x,y ));
    
        layer->addChild(platform,100);
    }
}