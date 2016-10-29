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
    
    optionButton = MenuItemImage::create("_bookgame_UI_options.png", "_bookgame_UI_options.png",
                                         CC_CALLBACK_0(MenuLayer::callOptionLayer, this));
    optionButton->setScale(0.8f);
    optionButton->setPosition(visibleSize.width*0.85, visibleSize.height*0.25);
    
    homeButton = MenuItemImage::create("_bookgame_UI_mainmenu.png","_bookgame_UI_mainmenu.png",
                                      CC_CALLBACK_0(MenuLayer::callBackScene, this));
    homeButton->setPosition(visibleSize.width/2, visibleSize.height*0.20);
    homeButton->setVisible(false);
    
    
    auto menu = Menu::create(playButton,optionButton,homeButton,nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu,1);
    
}

void MenuLayer::callPlayScene()
{
    auto scene = GamePlayScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void MenuLayer::callOptionLayer()
{
    playButton->setVisible(false);
    optionButton->setVisible(false);
    homeButton->setVisible(true);  
}

void MenuLayer::callBackScene()
{
    playButton->setVisible(true);
    optionButton->setVisible(true);
    homeButton->setVisible(false);
}
