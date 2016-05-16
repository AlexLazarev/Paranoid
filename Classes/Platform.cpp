#include "Platform.h"

#include "Definition.h"

USING_NS_CC;

Platform::Platform(cocos2d::Layer *layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	platform = Sprite::create("platform.png");
	platform->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 30 + origin.y));

	auto platformBody = PhysicsBody::createBox(platform->getContentSize());
	platformBody->setDynamic(false);
	platformBody->setCollisionBitmask(PLATFORM_COLLISON_BITMASK);
	platformBody->setContactTestBitmask(true);

	platform->setPhysicsBody(platformBody);

	isMoving = false;

	layer->addChild(platform);
}


void Platform::setPosition(int x)
{
	if(x > origin.x + EDGE_SIZE_BORDER + platform->getContentSize().width/2 
		&& x < visibleSize.width - EDGE_SIZE_BORDER - platform->getContentSize().width / 2)
			platform->setPositionX(x);
}