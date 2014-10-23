//
//  Cloud.cpp
//  jumpii
//
//  Created by Richard Siwady on 10/21/14.
//
//

#include "Cloud.h"


Cloud::Cloud(Layer* layer, bool fromEdge)
{
    
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );

    cloud = Sprite::create("cloud.png");
    if (fromEdge) {
        cloud->setOpacity(0);
    }
    cloud->setScale(0.5);
    
    auto height = arc4random() % 800 + 700;
    if (!fromEdge) {
        cloud->setPosition(Point(visibleSize.width - 100 * (arc4random()%20), height));
    }
    else {
        cloud->setPosition(Point(visibleSize.width /*+ (cloud->getContentSize().width/2)*/, height));
    }
    
    layer->addChild(cloud,5);
    
    auto speed = arc4random() % 60 + 30;
    auto moveTo = MoveTo::create(speed, Point(-500, height));
    if (fromEdge) {
        auto fadeIn = FadeIn::create(1);
        cloud->runAction(Sequence::create(fadeIn, moveTo, NULL));
    } else {
        cloud->runAction(moveTo);
    }
    
    CCLOG("Height: %d",height);
}