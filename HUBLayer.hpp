//
//  HUBLayer.hpp
//  AirHockey
//
//  Created by VietCT on 10/17/16.
//
//

#ifndef HUBLayer_hpp
#define HUBLayer_hpp

#include <cocos2d.h>

class HUBLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(HUBLayer);
    void update(int score1, int score2);
    
    
private:
    cocos2d::Label* label1;
    cocos2d::Label* label2;
    cocos2d::Size visibleSize;
    
private:
    bool init() override;
    void initLabel();
    
};

#endif /* HUBLayer_hpp */
