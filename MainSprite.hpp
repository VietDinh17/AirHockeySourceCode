//
//  MainSprite.hpp
//  AirHockey
//
//  Created by VietCT on 10/14/16.
//
//

#ifndef MainSprite_hpp
#define MainSprite_hpp

#include <cocos2d.h>

enum class Who{topPlayer, bottomPlayer, ball};

class MainSprite : public cocos2d::Sprite
{
public:
    Who whoScored;
    cocos2d::Vec2 initalPosition;
    
public:
    static MainSprite* createWithPos(const char* name, Who position);
    
    CC_SYNTHESIZE(cocos2d::Touch*, _touch, Touch);
    CC_SYNTHESIZE(cocos2d::Vec2, _vector, Vector);
    CC_SYNTHESIZE(cocos2d::Vec2, _nextPosition, NextPosition);
    
    void setPosition(const cocos2d::Vec2& pos) override;
    
    void update();
    
    inline Who getP() const { return _p; }
    
    inline float radius() { return this->getContentSize().width/2; }
    
    bool isGoaled();
    
private:
    MainSprite(Who p) : _p{p}, _vector{cocos2d::Vec2(0,0)} {}
    Who _p;
    cocos2d::Size visibleSize;
    
private:
    bool init(const char* name);
    
    void keepPlayerInside();
    
    bool isGoalRange();
    
    void bouchBack();
    
};

#endif /* MainSprite_hpp */
