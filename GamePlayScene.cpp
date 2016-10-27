//
//  GamePlayScene.cpp
//  AirHockey
//
//  Created by VietCT on 10/13/16.
//
//

#include "GamePlayScene.hpp"
#define FRICTION 0.96

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
    
    player1Score = 0;
    player2Score = 0;
    player1 = MainSprite::createWithPos("mallet.png",Who::topPlayer);
    player2 = MainSprite::createWithPos("mallet.png",Who::bottomPlayer);
    players.pushBack(player1);
    players.pushBack(player2);
    this->addChild(player1,1);
    this->addChild(player2,1);
    
    ball = MainSprite::createWithPos("puck.png", Who::ball);
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
    ballAndPlayerCollison();
    ball->update();
    resetAfterGoaled();
    hub->update(player1Score, player2Score);
   
}

void GamePlayScene::ballAndPlayerCollison()
{
    Vec2 ballNextPosition = ball->getNextPosition();
    Vec2 ballVector = ball->getVector();
    ballVector *= FRICTION;
    ballNextPosition += ballVector;
    
    
    for(const auto& player : players)
    {
        if(player != nullptr)
        {
            auto playerNextPosition = player->getNextPosition();
            auto playerVector = player->getVector();
            if(isCollied(player))
            {
                float mag_ball = pow(ballVector.x, 2) + pow(ballVector.y, 2);
                float mag_player = pow(playerVector.x, 2) + pow (playerVector.y,2);
                float force = sqrt(mag_ball + mag_player);
                float angle = atan2(diff.y, diff.x);
                ballVector.x = force * cos(angle);
                ballVector.y = force * sin(angle);
                ballNextPosition.x = playerNextPosition.x + (player->radius() + ball->radius() + force) * cos(angle);
                ballNextPosition.y = playerNextPosition.y + (player->radius() + ball->radius() + force) * sin(angle);
            }
        }
    }
    ball->setVector(ballVector);
    ball->setNextPosition(ballNextPosition);
    
}

void GamePlayScene::setScore()
{
    
    if(ball->whoScored == Who::topPlayer)
    {
        player1Score += 1;
    }else{
        player2Score += 1;
    }

}


bool GamePlayScene::isCollied(MainSprite* player)
{
    float colliedDistance = powf(ball->radius()+player->radius(),2);
    if(ball->getNextPosition().x == 0 && ball->getNextPosition().y == 0)
    {
        diff = Vec2(ball->getPositionX() - player->getNextPosition().x,
                      ball->getPositionY() - player->getNextPosition().y);
    }else{
        diff = Vec2(ball->getNextPosition().x - player->getPosition().x,
                 ball->getNextPosition().y - player->getPosition().y);
    }
    
    float distance = powf(diff.x,2) + powf(diff.y,2);
    
    if(distance <= colliedDistance)
    {
        return true;
    }
    return false;
}

void GamePlayScene::resetAfterGoaled()
{
    if(ball->isGoaled())
    {
        setScore();
        ball->setVector(Vec2::ZERO);
        ball->setNextPosition(Vec2::ZERO);
        
        if(ball->whoScored == Who::topPlayer)
        {
            ball->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2 - ball->radius()*1.25));
        }else{
            ball->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2 + ball->radius()*1.25));
        }
        
        player1->setNextPosition(Vec2::ZERO);
        player1->setPosition(player1->initalPosition);
        player1->setTouch(nullptr);
        
        player2->setNextPosition(Vec2::ZERO);
        player2->setPosition(player2->initalPosition);
        player2->setTouch(nullptr);
    }
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
                    player->setNextPosition(tap);
                    player->setVector(Vec2(tap.x - player->getPositionX(),tap.y - player->getPositionY()));
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
                    player->setTouch(nullptr);
            }
        }
    }
}