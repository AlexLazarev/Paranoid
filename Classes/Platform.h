#pragma once

#include "cocos2d.h"

class Platform
{
public:
	Platform(cocos2d::Layer *layer);
	void setPosition(int x);

private:
	bool isMoving;
	int route;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite *platform;
};
