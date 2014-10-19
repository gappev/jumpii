//
//  Rabit.cpp
//  jumpii
//
//  Created by Richard Siwady on 10/18/14.
//
//

#include "Rabbit.h"

Rabbit::Rabbit(Layer *layer)
{
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );
    
    auto rabbit = Sprite::create("rabbit.png");
    CCLOG("%f",rabbit->getContentSize().width);
    rabbit->setPosition(Point( origin.x + rabbit->getContentSize().width/2, origin.y + rabbit->getContentSize().height/2 + PLATFORM_HEIGHT) );
    
    auto rabbitBody = PhysicsBody::createBox(rabbit->getContentSize(), PhysicsMaterial(1,0,1));
    rabbitBody->setCollisionBitmask( RABBIT_COLLISION_BITMASK );
    rabbitBody->setContactTestBitmask( true );
    rabbit->setPhysicsBody(rabbitBody);
    
    layer->addChild(rabbit, 200);
}