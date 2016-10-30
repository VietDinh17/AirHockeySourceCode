//
//  GamePlayScene.hpp
//  AirHockey
//
//  Created by VietCT on 10/13/16.
//
//

#ifndef GamePlayScene_hpp
#define GamePlayScene_hpp

#include <cocos2d.h>
#include "MainSprite.hpp"
#include "HUBLayer.hpp"

class GamePlayScene : public cocos2d::Layer
{
public:
    MainSprite* player1;
    MainSprite* player2;
    MainSprite* ball;
    HUBLayer* hub;
    
    int player1Score;
    int player2Score;
    
public:
    static cocos2d::Scene* createScene();

    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vector<MainSprite*> players;
    cocos2d::Vec2 diff;
    
private:
    CREATE_FUNC(GamePlayScene);
    
    bool init() override;
    
    void update(float dt) override;
    
    void ballAndPlayerCollison();
    
    bool isCollied(MainSprite* player);
    
    void resetAfterGoaled();
    
    void setScore();
    
    void isTouchable(bool b);
    
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) override;
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) override;
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) override;
    
    
};

#endif /* GamePlayScene_hpp */
