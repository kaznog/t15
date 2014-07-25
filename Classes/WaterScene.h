//
//  WaterScene.h
//  t15
//
//  Created by 野口一也 on 2014/07/25.
//
//

#ifndef __t15__WaterScene__
#define __t15__WaterScene__

#include "cocos2d.h"

class Water : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
	// implement the "static create()" method manually
    CREATE_FUNC(Water);
    
};

#endif /* defined(__t15__WaterScene__) */
