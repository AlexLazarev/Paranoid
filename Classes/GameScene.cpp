#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(0);

    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
	layer->SetPhysicalWorld(scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	
    if ( !Layer::init() )
    {
        return false;
    }
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	

	auto backgroundSprite = Sprite::create("mainGameBackGround.png"); // background re
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);

	//auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, EDGE_SIZE_BORDER);
	//edgeBody->setCollisionBitmask(EDGE_COLLISON_BITMASK);
	//edgeBody->setContactTestBitmask(true);
	

	auto edgeLeftBody = PhysicsBody::createEdgeSegment(
		Vec2(0,0),Vec2(0,visibleSize.height)
		, PhysicsMaterial(0.0f, 0.0f, 1.0f), EDGE_SIZE_BORDER);
	edgeLeftBody->setCollisionBitmask(EDGE_LEFT_COLLISON_BITMASK);
	edgeLeftBody->setContactTestBitmask(true);
	
	auto edgeRightBody = PhysicsBody::createEdgeSegment(
		Vec2(visibleSize.width, 0), Vec2(visibleSize.width, visibleSize.height)
		,PHYSICSBODY_MATERIAL_DEFAULT, EDGE_SIZE_BORDER);
	edgeRightBody->setCollisionBitmask(EDGE_RIGHT_COLLISON_BITMASK);
	edgeRightBody->setContactTestBitmask(true);

	auto edgeTopBody = PhysicsBody::createEdgeSegment(
		Vec2(0, visibleSize.height), Vec2(visibleSize.width, visibleSize.height)
		,PHYSICSBODY_MATERIAL_DEFAULT, EDGE_SIZE_BORDER);
	edgeTopBody->setCollisionBitmask(EDGE_TOP_COLLISON_BITMASK);
	edgeTopBody->setContactTestBitmask(true);

	auto edgeDownBody = PhysicsBody::createEdgeSegment(
		Vec2(0, 0), Vec2(visibleSize.width, 0)
		,PHYSICSBODY_MATERIAL_DEFAULT, EDGE_SIZE_BORDER);
	edgeDownBody->setCollisionBitmask(EDGE_DOWN_COLLISON_BITMASK);
	edgeDownBody->setContactTestBitmask(true);

	PhysicsBody *pb[] = { edgeLeftBody,edgeRightBody,edgeTopBody,edgeDownBody };
	Node *edgeNode[4];
	for (int i = 0; i < 4; i++)
	{
		edgeNode[i] = Node::create();
		edgeNode[i]->setPosition(Vec2(origin.x, origin.y));
		edgeNode[i]->setPhysicsBody(pb[i]);
		this->addChild(edgeNode[i]);
	}
	

	
	
	this->schedule(schedule_selector(GameScene::SpawnBrick), BRICK_SPAWN_FREQUENCY);

	platform = new Platform(this);
	ball = new Ball(this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
   
	
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	SpawnBrick(0);


	


	health = HEALTH_POINT;
	for (int i = 0; i < HEALTH_POINT; i++)
	{
		healthSprite[i] = Sprite::create("heart.png");
		healthSprite[i]->setPosition(Vec2(visibleSize.width*0.95 - healthSprite[i]->getContentSize().width*i,
			visibleSize.height - healthSprite[i]->getContentSize().height));
		this->addChild(healthSprite[i]);
	}

	score = 0;
	scoreLabel = Label::createWithTTF("Score: 0", "fonts/Marker Felt.ttf", visibleSize.height*SCORE_FONT_SIZE);
	scoreLabel->setPosition(visibleSize.width / 10 + origin.x,
		visibleSize.height - healthSprite[0]->getContentSize().height);

	this->addChild(scoreLabel);

	return true;
}

void GameScene::SpawnBrick(float dt)
{
	brick.SpawnBrick(this);
}


bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();	
	a->getOwner()->stopActionByTag(1);

	if (BALL_COLLISON_BITMASK == a->getCollisionBitmask() && PLATFORM_COLLISON_BITMASK == b->getCollisionBitmask())
	{
		ball->changeVelocityY();
	}
	else if (BALL_COLLISON_BITMASK == a->getCollisionBitmask() && BRICK_COLLISON_BITMASK == b->getCollisionBitmask())
	{
		if (ball->getX() < b->getOwner()->getPositionX() ||
			ball->getX() > b->getOwner()->getPositionX() + b->getOwner()->getContentSize().width)
				ball->changeVelocityX();

		else if (ball->getY() < b->getOwner()->getPosition().y ||
			ball->getY() > b->getOwner()->getPosition().y + b->getOwner()->getContentSize().height)
				ball->changeVelocityY();


		b->getOwner()->setOpacity(0);
		b->onRemove();
		updateScore();
	}
	else if (BALL_COLLISON_BITMASK == a->getCollisionBitmask()
		&& (EDGE_LEFT_COLLISON_BITMASK == b->getCollisionBitmask()
			|| EDGE_RIGHT_COLLISON_BITMASK == b->getCollisionBitmask()))
		ball->changeVelocityX();
	else if (BALL_COLLISON_BITMASK == a->getCollisionBitmask()
		&& EDGE_TOP_COLLISON_BITMASK == b->getCollisionBitmask())
			ball->changeVelocityY();
	else if (BALL_COLLISON_BITMASK == a->getCollisionBitmask()
		&& EDGE_DOWN_COLLISON_BITMASK == b->getCollisionBitmask())
	{
		ball->changeVelocityY();
		ball->setPosition(Director::getInstance()->getVisibleSize().width / 2,
			Director::getInstance()->getVisibleSize().height / 2);
		health--;
		if(health > 0)
			healthSprite[HEALTH_POINT-1 - health]->setOpacity(0);
		else 
			GoToGameOverScene(0);
			
	}
	
	ball->MoveBall();
	return true;
}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	platform->setPosition(touch->getLocation().x);

	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event)
{ 
	platform->setPosition(touch->getLocation().x);
}

void GameScene::updateScore()
{
	score++;
	__String *tempScore = __String::createWithFormat("Score: %i", score);
	scoreLabel->setString(tempScore->getCString());
}


GameScene::~GameScene()
{
	delete platform;
	delete ball;
}

void GameScene::GoToGameOverScene(float dt)
{
	auto scene = GameOverScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}