//
//  GamePlayScene.cpp
//  AirHockey
//
//  Created by VietCT on 10/13/16.
//
//

#include "GamePlayScene.hpp"


USING_NS_CC;

Scene* GamePlayScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GamePlayScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool GamePlayScene::init()
{
    if(!Layer::init()) return false;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    players = Vector<MainSprite*>(2);
    auto bg = Sprite::create("court.png");
    bg->setPosition(visibleSize.width/2, visibleSize.height/2);
    this->addChild(bg,0);
    
    player1 = MainSprite::createWithPos("mallet.png",Pos::top);
    player2 = MainSprite::createWithPos("mallet.png",Pos::bottom);
    players.pushBack(player1);
    players.pushBack(player2);
    this->addChild(player1,1);
    this->addChild(player2,1);
    
    ball = MainSprite::createWithPos("puck.png", Pos::middle);
    this->addChild(ball,1);
    
    hub = HUBLayer::create();
    this->addChild(hub,2);
    
    isTouchable(true);
    
    this->scheduleUpdate();
    return true;
}

void GamePlayScene::update(float dt)
{
    player1->update();
    player2->update();
}

void GamePlayScene::isTouchable(bool b)
{
    if(b)
    {
        auto listener = EventListenerTouchAllAtOnce::create();
        listener->onTouchesBegan = CC_CALLBACK_2(GamePlayScene::onTouchesBegan, this);
        listener->onTouchesMoved = CC_CALLBACK_2(GamePlayScene::onTouchesMoved, this);
        listener->onTouchesEnded = CC_CALLBACK_2(GamePlayScene::onTouchesEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }
}

void GamePlayScene::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
    for(auto touch : touches)
    {
        if(touch != nullptr)
        {
            auto tap = touch->getLocation();
            for( auto player : players)
            {
                if(player->getBoundingBox().containsPoint(tap))
                    player->setTouch(touch);
            }
        }
    }
    
}

void GamePlayScene::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
    for(auto touch : touches)
    {
        if(touch != nullptr)
        {
            auto tap = touch->getLocation();
            for(auto player : players)
            {
                if(player->getTouch() != nullptr && player->getTouch() == touch)
                {
                    Vec2 nextPosition = tap;
                    if(nextPosition.x < player->radius()) nextPosition.x = player->radius();
                    if(nextPosition.y < player->radius()) nextPosition.y = player->radius();
                    if(nextPosition.x > visibleSize.width - player->radius())
                        nextPosition.x = visibleSize.width - player->radius();
                    if(nextPosition.y > visibleSize.height - player->radius())
                        nextPosition.y = visibleSize.height - player->radius();
                    
                    player->setPosition(nextPosition);
                }
                
            }
        }
    }
}

void GamePlayScene::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    for(auto touch :touches)
    {
        if(touch != nullptr)
        {
            for(auto player : players)
            {
                if(player->getTouch() != nullptr && player->getTouch() == touch)
                {
                    player->setTouch(nullptr);
                }
            }
        }
    }
}