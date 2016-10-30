//
//  HUBLayer.cpp
//  AirHockey
//
//  Created by VietCT on 10/17/16.
//
//

#include "HUBLayer.hpp"
#include "SimpleAudioEngine.h"
#include "GamePlayScene.hpp"


USING_NS_CC;

bool HUBLayer::init()
{
    if(!Layer::init()) return false;
    visibleSize = Director::getInstance()->getVisibleSize();
    scoreLabel();
    otherLabel();
    isPaused = false;
    return true;
}

void HUBLayer::scoreLabel()
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

void HUBLayer::otherLabel()
{
    
    soundButton = ui::CheckBox::create("_bookgame_UI_soundON.png", "_bookgame_UI_soundOFF.png");
    soundButton->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    soundButton->addEventListener(CC_CALLBACK_2(HUBLayer::changeSound, this));
    this->addChild(soundButton,1);
    soundButton->setVisible(false);
    
    optionButton = MenuItemImage::create("_bookgame_UI_options.png", "_bookgame_UI_options.png",
                                         CC_CALLBACK_0(HUBLayer::callOptionLayer, this));
    optionButton->setScale(0.8f);
    optionButton->setPosition(optionButton->getContentSize().width, visibleSize.height/2);
    
    resumeButton = MenuItemImage::create("_bookgame_UI_resume.png","_bookgame_UI_resume.png",
                                       CC_CALLBACK_0(HUBLayer::callBackGamePlay, this));
    resumeButton->setPosition(visibleSize.width * 0.25, visibleSize.height/2);
    resumeButton->setVisible(false);
    
    auto menu = Menu::create(optionButton,resumeButton,nullptr);
    menu->setPosition(Vec2(0,0));
    this->addChild(menu,1);
}

void HUBLayer::changeSound(Ref* sender, ui::CheckBox::EventType type)
{
    switch (type) {
        case ui::CheckBox::EventType::SELECTED:
            //UserDefault::getInstance()->setBoolForKey("isSoundPaused", true);
            CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
            break;
        case ui::CheckBox::EventType::UNSELECTED:
            CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
            break;
        default:
            break;
    }
}


void HUBLayer::callOptionLayer()
{
    auto playScene = (GamePlayScene*)this->getParent();
    playScene->unscheduleUpdate();
    optionButton->setVisible(false);
    resumeButton->setVisible(true);
    soundButton->setVisible(true);
    isPaused = true;
}

void HUBLayer::callBackGamePlay()
{
    auto playScene = (GamePlayScene*)this->getParent();
    playScene->scheduleUpdate();
    optionButton->setVisible(true);
    resumeButton->setVisible(false);
    soundButton->setVisible(false);
    isPaused = false;
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