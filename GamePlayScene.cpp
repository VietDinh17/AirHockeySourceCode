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
    
    auto bg = Sprite::create("court.png");
    bg->setPosition(visibleSize.width/2, visibleSize.height/2);
    this->addChild(bg,0);
    
    player1 = MainSprite::createWithPos("puck.png",Pos::top);
    player2 = MainSprite::createWithPos("puck.png",Pos::bottom);
    this->addChild(player1,1);
    this->addChild(player2,1);
 
    
    hub = HUBLayer::create();
    this->addChild(hub,2);
    
    this->scheduleUpdate();
    return true;
}

void GamePlayScene::update(float dt)
{
    player1->update();
    player2->update();
}