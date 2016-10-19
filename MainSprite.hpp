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

enum class Pos{top, middle, bottom};

class MainSprite : public cocos2d::Sprite
{
public:
    MainSprite(Pos p) : _p{p}{}
    static MainSprite* createWithPos(const char* name, Pos position);
    void update();
    Pos getP() const { return _p; }
    inline float radius() { return this->getContentSize().width/2; }
private:
    Pos _p;
    cocos2d::Size visibleSize;
    
private:
    bool init(const char* name);
    CC_SYNTHESIZE(cocos2d::Touch*, _touch, Touch);
};

#endif /* MainSprite_hpp */
