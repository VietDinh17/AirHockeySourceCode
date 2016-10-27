//
//  HUBLayer.cpp
//  AirHockey
//
//  Created by VietCT on 10/17/16.
//
//

#include "HUBLayer.hpp"

USING_NS_CC;

bool HUBLayer::init()
{
    if(!Layer::init()) return false;
    visibleSize = Director::getInstance()->getVisibleSize();
    initLabel();
    
    return true;
}

void HUBLayer::initLabel()
{
    label1 = Label::createWithBMFont("PixelFont.fnt", "0");
    label1->setPosition(Vec2(visibleSize.width - label1->getContentSize().width,
                             visibleSize.height/2 + label1->getContentSize().height));
    label1->setRotation(180);
    label1->setScale(0.9);
    
    label2 = Label::createWithBMFont("PixelFont.fnt", "0");
    label2->setPosition(Vec2(visibleSize.width - label2->getContentSize().width,
                             visibleSize.height/2 - label2->getContentSize().height));
    label2->setScale(0.9);
    
    this->addChild(label1);
    this->addChild(label2);
}

void HUBLayer::update(int s1,int s2)
{
    char c1[20]{};
    sprintf(c1, "%d",s1);
    char c2[20]{};
    sprintf(c2, "%d",s2);
    
    label1->setString(c1);
    label2->setString(c2);
}