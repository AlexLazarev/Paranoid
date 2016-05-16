#include "mainMenuScene.h"

USING_NS_CC;

Scene* mainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = mainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool mainMenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("mainMenuBackGround.png");
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);


	auto playItem = MenuItemImage::create("PlayButton.png","PlayButtonClick.png",
		CC_CALLBACK_1(mainMenuScene::GoToGameScene,this));
	playItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	
	auto menu = Menu::create(playItem, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);

    return true;
}

void mainMenuScene::GoToGameScene(Ref * sender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}
