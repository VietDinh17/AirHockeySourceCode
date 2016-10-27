//
//  MainSprite.cpp
//  AirHockey
//
//  Created by VietCT on 10/14/16.
//
//

#include "MainSprite.hpp"
#define GOAL_WIDTH 400

USING_NS_CC;

MainSprite* MainSprite::createWithPos(const char* name, Who p)
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
    int randomN = random(0, 1);
    
    if(!this->initWithFile(name)) return false;
    
    if(_p == Who::topPlayer)
    {
        initalPosition = Vec2(visibleSize.width/2,visibleSize.height - this->getContentSize().height);
        this->setPosition(initalPosition);
    }
    else if(_p == Who::bottomPlayer)
    {
        initalPosition = Vec2(visibleSize.width/2, this->getContentSize().height);
        this->setPosition(initalPosition);
    }
    else // random postion for ball
    {
        if(randomN == 1)
            this->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2 + radius()*1.25));
        else
            this->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2 - radius()*1.25));
    }
    
    return true;
}

void MainSprite::setPosition(const Vec2& pos)
{
    Sprite::setPosition(pos);
    if(!(_nextPosition.equals(pos)))
        _nextPosition = pos;
}


void MainSprite::update()
{
    keepPlayerInside();
    bouchBack();
}


void MainSprite::bouchBack()
{
    if(_p == Who::ball)
    {
        // two sides
        if(_nextPosition.x <= radius())
        {
            _nextPosition.x = radius();
            _vector.x *= -0.8f;
        }
        if(_nextPosition.x >= visibleSize.width - radius())
        {
            _nextPosition.x = visibleSize.width - radius();
            _vector.x *= -0.8f;
        }

        // bot and topPlayer
        if(_nextPosition.y <= radius())
        {
            if(!isGoalRange())
            {
                _nextPosition.y = radius();
                _vector.y *= -0.8f;
            }
        }
        if(_nextPosition.y >= visibleSize.height - radius())
        {
            if(!isGoalRange())
            {
                _nextPosition.y = visibleSize.height - radius();
                _vector.y *= -0.8f;
            }
        }
        this->setPosition(_nextPosition);
    }
    
}

bool MainSprite::isGoaled()
{
    if (_nextPosition.y <= -radius()*0.95) {
        whoScored = Who::topPlayer;
        return true;
    }
    if (_nextPosition.y >= visibleSize.height + radius()*0.95) {
        whoScored = Who::bottomPlayer;
        return true;
    }
    return false;
}

bool MainSprite::isGoalRange()
{
    if((_nextPosition.x - radius()) >= (visibleSize.width/2 - GOAL_WIDTH/2) &&
        (_nextPosition.x + radius()) <= (visibleSize.width/2 + GOAL_WIDTH/2))
    {
        return true;
    }
    return false;
}

void MainSprite::keepPlayerInside()
{
    if(_p != Who::ball)
    {
        if(_nextPosition.x < this->radius()) _nextPosition.x = this->radius();
        if(_nextPosition.y < this->radius()) _nextPosition.y = this->radius();
        if(_nextPosition.x > visibleSize.width - this->radius())
        {
           _nextPosition.x = visibleSize.width - this->radius();
        }
        if(_nextPosition.y > visibleSize.height - this->radius())
        {
            _nextPosition.y = visibleSize.height - this->radius();
        }
        
        if(_p == Who::topPlayer)
        {
            if(_nextPosition.y <=  visibleSize.height/2 + radius())
                _nextPosition = Vec2(_nextPosition.x,visibleSize.height / 2 + radius());
        }
        else
        {
            if(_nextPosition.y >=  visibleSize.height/2 - radius())
                _nextPosition = Vec2(_nextPosition.x,visibleSize.height / 2 - radius());
        }
        this->setPosition(_nextPosition);
        this->setPosition(_nextPosition);
    }

}