//
//  CloudsScene.cpp
//  t15
//
//  Created by 野口一也 on 2014/07/25.
//
//

#include "CloudsScene.h"

USING_NS_CC;

Scene* Clouds::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Clouds::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Clouds::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
	m_eventListenerTouch = EventListenerTouchAllAtOnce::create();
	auto center = Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    
	auto bg = Sprite::create("bg.png");
	bg->setPosition(center);
	auto bgsize = bg->getContentSize();
	float scaleX = visibleSize.width / bgsize.width;
	float scaleY = visibleSize.height / bgsize.height;
	bg->setScaleX(scaleX);
	bg->setScaleY(scaleY);
	addChild(bg, 0);
    
	Texture2D::TexParams p;
	p.minFilter = GL_LINEAR;
	p.magFilter = GL_LINEAR;
	p.wrapS = GL_REPEAT;
	p.wrapT = GL_REPEAT;
    
	auto cloudsSprite = Sprite::create("noise_1024.png");
	cloudsSprite->getTexture()->setTexParameters(p);
	cloudsSprite->setPosition(center);
	cloudsSprite->setTag(10);
	float cloudsScaleX = visibleSize.width / cloudsSprite->getContentSize().width;
	float cloudsScaleY = visibleSize.height / cloudsSprite->getContentSize().height;
	cloudsSprite->setScaleX(cloudsScaleX);
	cloudsSprite->setScaleY(cloudsScaleY);
	addChild(cloudsSprite, 10);
    
    auto textureCache = Director::getInstance()->getTextureCache();
	auto tex1 = textureCache->addImage("noise_512.png");
	tex1->setTexParameters(p);
    
	auto tex2 = textureCache->addImage("noise_256.png");
	tex2->setTexParameters(p);
    
	// Create the clouds shader
	GLProgram* prog = new GLProgram();
	prog->initWithFilenames("clouds.vsh", "clouds.fsh");
    
	prog->link();
	prog->use();
	prog->updateUniforms();
	
	glActiveTexture(GL_TEXTURE1);
	CHECK_GL_ERROR_DEBUG();
	glBindTexture(GL_TEXTURE_2D, tex1->getName());
	CHECK_GL_ERROR_DEBUG();
    
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, tex2->getName());
	CHECK_GL_ERROR_DEBUG();
    
	glActiveTexture(GL_TEXTURE0);
	CHECK_GL_ERROR_DEBUG();
	
	ShaderCache::getInstance()->addGLProgram(prog, "clouds");
    
	cloudsSprite->setGLProgram(prog);
	GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(prog);
	state->setUniformFloat("u_cloudSpeed", m_cloudSpeed);
	state->setUniformFloat("u_amount", m_cloudAmount);
    
	prog->release();
    
	m_eventListenerTouch->onTouchesMoved = [=] (const std::vector<Touch*>& touch, Event* e)
	{
		if (touch.size() > 0)
		{
			auto t = touch[0];
			auto delta = t->getDelta() * 0.001f;
            
			m_cloudAmount += delta.y;
			m_cloudAmount = std::max(0.0f, m_cloudAmount);
			m_cloudAmount = std::min(1.0f, m_cloudAmount);
            
			auto state = cloudsSprite->getGLProgramState();
			state->setUniformFloat("u_amount", m_cloudAmount);
		}
	};
    
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(m_eventListenerTouch, 1);
    return true;
}
