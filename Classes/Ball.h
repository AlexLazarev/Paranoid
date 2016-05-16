#pragma once

#include "cocos2d.h"

class Ball
{
public:

	Ball(cocos2d::Layer *layer);
	void MoveBall();
	void MoveBall(int,int);
	void setPosition(int, int);

	float getX();
	float getY();
	int getRadius();

	void changeVelocityX();
	void changeVelocityY();
private:
	int radius;
	cocos2d::Vec2 velocity;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite *ball;
	
	

};
