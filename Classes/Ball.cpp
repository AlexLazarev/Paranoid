#include "Ball.h"

#include "Definition.h"

USING_NS_CC;

Ball::Ball(cocos2d::Layer *layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	ball = Sprite::create("ball2.png");
	ball->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height /20 + origin.y));
	radius = ball->getContentSize().width / 2;
	auto ballBody = PhysicsBody::createCircle(radius);
	ballBody->setDynamic(true);
	ballBody->setGravityEnable(false);

	ballBody->setCollisionBitmask(BALL_COLLISON_BITMASK);
	ballBody->setContactTestBitmask(true);

	ball->setPhysicsBody(ballBody);	
	velocity.x = visibleSize.width;
	velocity.y = -visibleSize.height;
	
	layer->addChild(ball);
}

void Ball::setPosition(int x,int y)
{
	ball->setPosition(x, y);
}

void Ball::MoveBall()
{

	auto moveAction = MoveBy::create(BALL_DURATION,velocity);
	moveAction->setTag(1);
	ball->runAction(moveAction);
}

void Ball::MoveBall(int x, int y)
{

	auto moveAction = MoveBy::create(BALL_DURATION, Vec2(x,y));
	moveAction->setTag(2);
	ball->runAction(moveAction);
}

float Ball::getX()
{
	return ball->getPositionX();
}

float Ball::getY()
{
	return ball->getPositionY();
}

void Ball::changeVelocityX()
{
	velocity.x *=-1;
}

void Ball::changeVelocityY()
{
	velocity.y *= -1;
}

int Ball::getRadius()
{
	return radius;
}