#pragma once

#include "cocos2d.h"
#include "Brick.h"
#include "platform.h"
#include "Ball.h"
#include "Definition.h"
#include "GameOverScene.h"
class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	~GameScene();

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
	
private:
	void SetPhysicalWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };

	void updateScore();

	void SpawnBrick(float dt);
	
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchMoved(cocos2d::Touch *touch,cocos2d::Event *event);

	bool onContactBegin(cocos2d::PhysicsContact &contact);


	cocos2d::PhysicsWorld *sceneWorld;
	
	Brick brick;
	Platform *platform;
	Ball *ball;

	unsigned int score;
	unsigned int health;
	cocos2d::Label *scoreLabel;
	cocos2d::Sprite *healthSprite[HEALTH_POINT];

	void GoToGameOverScene(float dt);
};
