//
//  WaterScene.cpp
//  t15
//
//  Created by 野口一也 on 2014/07/25.
//
//

#include "WaterScene.h"
USING_NS_CC;

Scene* Water::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Water::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Water::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
	auto center = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    
	Texture2D::TexParams p;
	p.minFilter = GL_LINEAR;
	p.magFilter = GL_LINEAR;
	p.wrapS = GL_REPEAT;
	p.wrapT = GL_REPEAT;
    
	auto RocksSprite = Sprite::create("Rocks.png");
	RocksSprite->setPosition(center);
	RocksSprite->setTag(10);
//	float RocksScaleX = visibleSize.width / RocksSprite->getContentSize().width;
//	float RocksScaleY = visibleSize.height / RocksSprite->getContentSize().height;
//	RocksSprite->setScaleX(RocksScaleX);
//	RocksSprite->setScaleY(RocksScaleY);
	addChild(RocksSprite, 10);
    
    auto textureCache = Director::getInstance()->getTextureCache();
    // グレイスケールはだめみたい。。。
	auto tex1 = textureCache->addImage("CausticRGB.png");
    
	auto tex2 = textureCache->addImage("BisectionNoise.png");
	tex2->setTexParameters(p);
    
	// Create the clouds shader
	GLProgram* prog = new GLProgram();
	prog->initWithFilenames("water.vsh", "water.fsh");
    prog->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    prog->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
    
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
	
	ShaderCache::getInstance()->addGLProgram(prog, "water");
    
	RocksSprite->setGLProgram(prog);
	GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(prog);
	state->setUniformVec2("u_NoiseTextureSize", tex1->getContentSize());
    state->setUniformVec2("resolution", visibleSize);
//    state->setUniformTexture("u_CausticTexture", tex1);
//    state->setUniformTexture("u_NoiseTexture", tex2);
    
	prog->release();
    
    return true;
}