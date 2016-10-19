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
    static cocos2d::Scene* createScene();
    MainSprite* player1;
    MainSprite* player2;
    HUBLayer* hub;
    
private:
    cocos2d::Size visibleSize;
    
private:
    CREATE_FUNC(GamePlayScene);
    
    bool init() override;
    
    void update(float dt) override;

    
};

#endif /* GamePlayScene_hpp */
