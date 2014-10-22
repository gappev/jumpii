//
//  Cloud.cpp
//  jumpii
//
//  Created by Richard Siwady on 10/21/14.
//
//

#include "Cloud.h"


Cloud::Cloud(Layer* layer)
{
    
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );

    cloud = Sprite::create("cloud.png");
    cloud->setOpacity(128);
    cloud->setScale(0.4);
    
    auto height = arc4random() % 800 + 700;
    cloud->setPosition(Point(visibleSize.width - 100, height));
    
    layer->addChild(cloud,5);
    
    auto speed = arc4random() % 60 + 30;
    cloud->runAction(MoveTo::create(speed, Point(-500, height)));
    
    CCLOG("Height: %d",height);
}