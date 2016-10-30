//
//  MenuLayer.hpp
//  AirHockey
//
//  Created by VietCT on 10/13/16.
//
//

#ifndef MenuLayer_hpp
#define MenuLayer_hpp

#include <cocos2d.h>

class MenuLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    
private:
    cocos2d::Size visibleSize;
    cocos2d::MenuItemImage* playButton;
    
    
private:
    CREATE_FUNC(MenuLayer);
    
    bool init() override;
    void createButtons();
    void callPlayScene();

};


#endif /* MenuLayer_hpp */
