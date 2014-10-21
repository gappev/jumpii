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
    
    rabbit = Sprite::create("rabbit.png");
    
    int x =origin.x + rabbit->getContentSize().width/2 + (PLATFORM_WIDTH/5) + PLATFORM_WIDTH*2;
    int y =origin.y + rabbit->getContentSize().height/2 + PLATFORM_HEIGHT - PLATFORM_HEIGHT_GAP;
    rabbit->setPosition(Point( x,y ) );
    
    rabbitBody = PhysicsBody::createBox(rabbit->getContentSize(), PhysicsMaterial(1,0,1));
    //CCLOG("velocity: %fx%f", rabbitBody->getVelocity().x, rabbitBody->getVelocity().y);
    //rabbitBody->setVelocity(Vect(0, -600.0f));
    //rabbitBody->setVelocityLimit(-800.0f);
    rabbitBody->setCollisionBitmask( RABBIT_COLLISION_BITMASK );
    rabbitBody->setContactTestBitmask( true );
    
    rabbit->setPhysicsBody(rabbitBody);
    
    isJumping = false;
    isFalling = false;
    
    layer->addChild(rabbit, 200);
}

void Rabbit::jumpByOne() {
    isJumping = true;
    
    auto action1 = MoveBy::create( 0.00001f * (PLATFORM_WIDTH*8), Point( -PLATFORM_WIDTH, 0 ));
    auto action2 = JumpTo::create( 1, Point( rabbit->getPositionX(), rabbit->getPositionY() ), rabbit->getPositionY()/1.6f, 1);
    
    Sequence* actions = Sequence::create(action1, DelayTime::create(0.1f), action2, CallFunc::create(std::bind(&Rabbit::isNotJumping,this)), NULL);
    
    rabbit->runAction( actions );
}

void Rabbit::jumpByTwo() {
    isJumping = true;
    
    auto action1 = MoveBy::create( 0.0001f * (PLATFORM_WIDTH*8), Point( -(PLATFORM_WIDTH*2), 0 ));
    auto action2 = JumpTo::create( 1, Point( rabbit->getPositionX(), rabbit->getPositionY() ), rabbit->getPositionY()/1.6f, 1);
    
    Sequence* actions = Sequence::create(action1, DelayTime::create(0.1f), action2, CallFunc::create(std::bind(&Rabbit::isNotJumping,this)), NULL);
    
    rabbit->runAction( actions );
}

void Rabbit::isNotJumping() {
    isJumping = false;
}