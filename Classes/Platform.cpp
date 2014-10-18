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
}

void Platform::SpawnPlatform(cocos2d::Layer *layer)
{
    auto platform = Sprite::create("platform-1.png");
    auto platformBody = PhysicsBody::createBox(platform->getContentSize());
    
    platformBody->setDynamic(false);
    platformBody->setContactTestBitmask(true);
    
    platform->setPhysicsBody(platformBody);
    platform->setPosition(Point());
    
    layer->addChild(platform);
}