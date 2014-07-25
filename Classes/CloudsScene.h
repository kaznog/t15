//
//  CloudsScene.h
//  t15
//
//  Created by 野口一也 on 2014/07/25.
//
//

#ifndef __t15__CloudsScene__
#define __t15__CloudsScene__

#include "cocos2d.h"

class Clouds : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
	// implement the "static create()" method manually
    CREATE_FUNC(Clouds);
    
	float m_cloudAmount;
	float m_cloudSpeed;
    
	cocos2d::EventListenerTouchAllAtOnce* m_eventListenerTouch;
    
	Clouds() : m_eventListenerTouch(nullptr), m_cloudAmount(0.7f), m_cloudSpeed(1.0f) {}
};


#endif /* defined(__t15__CloudsScene__) */
