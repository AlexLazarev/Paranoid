#include "Brick.h"
#include "time.h"
#include "Definition.h"

USING_NS_CC;

Brick::Brick()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

}

void Brick::SpawnBrick(cocos2d::Layer *layer)
{
	srand(time(0));
	int i = rand() % 5;
	auto brick = Sprite::create("br.png", Rect(48 * i, 0, 48, 23));
	auto brickBody = PhysicsBody::createBox(brick->getContentSize());
	brickBody->setDynamic(false);
	brickBody->setCollisionBitmask(BRICK_COLLISON_BITMASK);
	brickBody->setContactTestBitmask(true);

	brick->setPhysicsBody(brickBody);
	brick->setAnchorPoint(Vec2(0, 0));

	brick->setPosition(Vec2(
		visibleSize.width / 2 + origin.x +
		CCRANDOM_MINUS1_1() * visibleSize.width /2.3,
		visibleSize.height / 2 + origin.y +
		CCRANDOM_MINUS1_1() *visibleSize.height / 4));

	layer->addChild(brick);
}