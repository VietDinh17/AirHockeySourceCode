//
//  MenuLayer.cpp
//  AirHockey
//
//  Created by VietCT on 10/13/16.
//
//

#include "MenuLayer.hpp"
#include "GamePlayScene.hpp"


USING_NS_CC;

Scene* MenuLayer::createScene()
{
    auto scene = Scene::create();
    
    auto layer = MenuLayer::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool MenuLayer::init()
{
    
    if(!Layer::init()) return false;

    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    auto bg = Sprite::create("BackgroundPurple5.png");
    bg->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(bg,0);
    
    createButtons();
    
    return true;
}

void MenuLayer::createButtons()
{
    playButton = MenuItemImage::create("logo.png", "logo.png",
                                       CC_CALLBACK_0(MenuLayer::callPlayScene, this));
    playButton->setPosition(visibleSize.width/2,visibleSize.height/2);
    
    auto menu = Menu::create(playButton,nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu,1);
    
}


void MenuLayer::callPlayScene()
{
    auto scene = GamePlayScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

