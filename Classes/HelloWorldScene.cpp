#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    auto _gridNodeTarget = NodeGrid::create();
    _gridNodeTarget->addChild(sprite);
    this->addChild(_gridNodeTarget);
    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    GLProgram* shader = new GLProgram();
    sprite->setGLProgram(shader);
    shader->initWithFilenames("sepia.vsh", "sepia.fsh");
    shader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    shader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
    shader->link();
    shader->updateUniforms();
    
    shader->setUniformLocationWith1i(shader->getUniformLocationForName("u_enableSepia"), true);
    shader->setUniformLocationWith1i(shader->getUniformLocationForName("u_enableGray"), true);

    auto action = Waves3D::create(10, Size(15,10), 5, 40);;
    _gridNodeTarget->runAction(RepeatForever::create(action));
//	CCSprite *sprite = [CCSprite spriteWithImageNamed:@"Rocks.png"];
//	sprite.shader = [CCShader shaderNamed:self.shaderName];
//	
//	sprite.shaderUniforms[@"u_CausticTexture"] = [CCTexture textureWithFile:@"Caustic.png"];
//	
//	CCTexture *noise = [CCTexture textureWithFile:@"BisectionNoise.png"];
//	noise.texParameters = &(ccTexParams){GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
//	sprite.shaderUniforms[@"u_NoiseTexture"] = noise;
    
//    auto texture0 = Director::getInstance()->getTextureCache()->addImage("Images/grossini_dance_atlas.png");
//    texture0->generateMipmap();
//    Texture2D::TexParams texParams = { GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };
//    texture0->setTexParameters(texParams);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
