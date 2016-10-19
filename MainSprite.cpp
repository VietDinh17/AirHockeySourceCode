//
//  MainSprite.cpp
//  AirHockey
//
//  Created by VietCT on 10/14/16.
//
//

#include "MainSprite.hpp"

USING_NS_CC;

MainSprite* MainSprite::createWithPos(const char* name, Pos p)
{
    auto sprite = new MainSprite(p);
    if(sprite && sprite->init(name))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return sprite = nullptr;
}

bool MainSprite::init(const char* name)
{
    visibleSize = Director::getInstance()->getVisibleSize();
    this->initWithFile(name);
    if(_p == Pos::top)
    this->setPosition(Vec2(visibleSize.width/2,visibleSize.height - this->getContentSize().height));
    if(_p == Pos::bottom)
    this->setPosition(Vec2(visibleSize.width/2, this->getContentSize().height));
    return true;
}


void MainSprite::update()
{
    if(_p == Pos::top)
    {
        if(this->getPosition().y <=  visibleSize.height/2)
            this->setPosition(Vec2(this->getPosition().x,visibleSize.height / 2 + this->getContentSize().height));
    }else{
        if(this->getPosition().y >=  visibleSize.height/2)
            this->setPosition(Vec2(this->getPosition().x,visibleSize.height / 2 - this->getContentSize().height));
    }
}