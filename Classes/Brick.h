#pragma once

#include "cocos2d.h"

class Brick
{
public:
	Brick();

	void SpawnBrick(cocos2d::Layer *layer);

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
};
