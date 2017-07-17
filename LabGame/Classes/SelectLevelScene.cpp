#include "HelloWorldScene.h"
#include "SelectLevelScene.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include <string>
using std::string;
#include <iostream>
#include <sstream>


USING_NS_CC;

Scene* SelectLevel::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SelectLevel::create();

    // add layer as a child to scene
    scene->addChild(layer,0,999);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SelectLevel::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	CCUserDefault *def = CCUserDefault::sharedUserDefault();
	def->setIntegerForKey("LevelUnlockedTest",0);
	levelunlocked= def->getIntegerForKey("LevelUnlockedTest");
	touchableSprites.clear();

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));
	auto nodeItems = Node::create();
	nodeItems->setName("nodeItems");

	auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	float width = sprite->getContentSize().width;

	backgroundSprite = Sprite::create("4.png");
	backgroundSprite->setAnchorPoint(Vec2::ZERO);
	backgroundSprite->setContentSize(playingSize);
	backgroundSprite->setScaleX((visibleSize.width / backgroundSprite->getContentSize().width) * 1);
	backgroundSprite->setScaleY((visibleSize.height / backgroundSprite->getContentSize().height) * 1);

	nodeItems->addChild(backgroundSprite, -1);
	int loop = std::ceil(visibleSize.width / width);

	sprite->setPosition(0, 0);

	auto spriteNode = Node::create();
	spriteNode->setName("spriteNode");

	//Adding touchable sprites to vector, different type of sprites different vectors?
	//Enemy 1 vector
	//Player monsters 1 vector
	//Touchable sprites 1 vector, etc
	a = new Touchables();
	a->init("Button1.png", "mainSprite", visibleSize.width * 0.1, visibleSize.height * 0.65, Touchables::T_LEVEL1,0.45);

	Touchables* b = new Touchables();
	b->init("Button1.png", "mainSprite", visibleSize.width * 0.3, visibleSize.height * 0.65, Touchables::T_LEVEL2,0.45);
	
	touchableSprites.push_back(a);
	touchableSprites.push_back(b);
	float widthX = 0.5;
	float heightY = 0.65;

	// Back button
	Touchables* back = new Touchables();
	back->init("back_button.png", "mainSprite", visibleSize.width * 0.8, visibleSize.height * 0.05, Touchables::T_BACK, 1.2);

	// Shop button
	Touchables* shop = new Touchables();
	shop->init("red_button1.png", "mainSprite", visibleSize.width * 0.35, visibleSize.height * 0.8, Touchables::T_SHOP, 1.2);
	shop->SetDisabled(true);
	shop->SetText("LEVEL SELECTION", 1, "fonts/Soos.ttf", ccc3(255, 255, 255), 0, 0);
	shop->GetLabel("label")->disableEffect();

	// push back sprite vector
	touchableSprites.push_back(back);
	touchableSprites.push_back(shop);

	//Test multi generating locked levels
	for (int i = 0; i < 3; i++)
	{
		Touchables* c = new Touchables();
		c->init("Button1.png", "mainSprite", visibleSize.width * widthX, visibleSize.height * heightY, Touchables::T_LEVEL3, 0.45);

		if (c->getSprite()->getPositionX() >= visibleSize.width - c->getSprite()->getContentSize().width)
		{
			widthX = 0.1;
			heightY -= 0.24;
		}
		else
		widthX += 0.2;

		c->SetText("Level 3", 3, "fonts/Soos.ttf", ccc3(0, 200, 255), 0, 0);
		c->SetToolTip("Unlock previous levels", "wood.png", 150, 0, -c->getSprite()->getContentSize().height*1.25, 1.3);
		c->GetToolTipLabel()->setScale(1.2);
		c->GetToolTipLabel()->enableShadow();
		if (levelunlocked < 3)
			c->SetDisabled(true);
		touchableSprites.push_back(c);
	}

	for (auto* s : touchableSprites)
	{
		spriteNode->addChild(s->getSprite(), 1);
	}

	a->SetText("Level 1",3, "fonts/Soos.ttf", ccc3(0, 200, 255), 0, 0);
	b->SetText("Level 2", 3, "fonts/Soos.ttf", ccc3(0, 200, 255), 0, 0);
	b->SetToolTip("Unlock previous levels", "wood.png", 150, 0, -b->getSprite()->getContentSize().height*1.25, 1.3);
	b->GetToolTipLabel()->setScale(1.2);
	b->GetToolTipLabel()->enableShadow();
	if(levelunlocked < 2)
	b->SetDisabled(true);


	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(SelectLevel::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(SelectLevel::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->addChild(nodeItems, 1);
	this->addChild(spriteNode, 2);

	auto _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseUp = CC_CALLBACK_1(SelectLevel::onMouseUp, this);
	_mouseListener->onMouseMove = CC_CALLBACK_1(SelectLevel::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchEnded = CC_CALLBACK_2(SelectLevel::onTouchEnded, this);

	this->scheduleUpdate();

	// Load sound
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/click.wav");

	return true;
}
void SelectLevel::update(float deltaTime)
{
	if (moveDir != 0)
	{
		auto cam = Camera::getDefaultCamera();
		cam->setPosition(Vec2(cam->getPosition().x + moveDir, cam->getPosition().y));
	}

	for (auto* s : touchableSprites)
	{
		s->Update(deltaTime);
	}
}
void SelectLevel::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	for (auto* s : touchableSprites)
	{
		if (s->onTouchBegan(touch, event))
		{

		}
	}
}
void SelectLevel::onMouseMove(Event *event)
{
	//HOVERING change sprite
	EventMouse* e = (EventMouse*)event;

	for (auto* s : touchableSprites)
	{

		if (s->checkMouseDown(event))
		{
			if (s->GetToolTip() != nullptr && s->GetDisabled())
				s->GetToolTip()->setVisible(true);

			if (!s->GetDisabled())
			{
				if (s->GetType() != Touchables::T_BACK)
					s->getSprite()->setTexture("Button2.png");
				if (s->GetLabel("label") != nullptr)
				{
					s->GetLabel("label")->setColor(ccc3(0, 0, 255));
				}
			}
			switch (s->GetType())
			{
			case Touchables::T_BACK:
				break;

			case Touchables::T_LEVEL1:
				break;

			case Touchables::T_LEVEL2:
				break;
			case Touchables::T_LEVEL3:
				break;
			}

		}
		else
		{
			if (s->GetToolTip() != nullptr)
				s->GetToolTip()->setVisible(false);

			if (!s->GetDisabled())
			{
				if (s->GetType() != Touchables::T_BACK)
					s->getSprite()->setTexture("Button1.png");
				if (s->GetLabel("label") != nullptr)
				{
					s->GetLabel("label")->setColor(s->GetDefaultTextColor());
				}
			}
			switch (s->GetType())
			{
			case Touchables::T_BACK:
				break;

			case Touchables::T_LEVEL1:
				break;

			case Touchables::T_LEVEL2:
				break;

			case Touchables::T_LEVEL3:
				break;
			}
		}
	}
}

void SelectLevel::onMouseUp(Event *event)
{
	EventMouse* e = (EventMouse*)event;
	
	//Detection for touching any touchable sprite

	//Buttons to summon monsters/players
	for (auto* s : touchableSprites)
	{
		std::stringstream oss;

		if (!s->GetDisabled())
		{
			//Checking if point is within sprite's box, and the tag of sprite
			if (s->checkMouseDown(event))
			{
				switch (s->GetType())
				{
				case Touchables::T_LEVEL1:
					CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5, HelloWorld::createScene(), Color3B(0, 0, 0)));
					//CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
					audioMng->playSFX("click", 0);
					//audioMng->stopBGM();
					break;
				case Touchables::T_LEVEL2:
					CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5, HelloWorld::createScene(), Color3B(0, 255, 255)));

					break;
				case Touchables::T_LEVEL3:
					CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5, HelloWorld::createScene(), Color3B(0, 255, 255)));

					break;
				case Touchables::T_BACK:
					CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5, MenuScene::createScene(), Color3B(0, 255, 255)));
					//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/click.wav");
					audioMng->playSFX("click", 0);
					break;
				}
			}
		}
	}
}
void SelectLevel::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5, HelloWorld::createScene(), Color3B(0, 255, 255)));
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{

	}

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
	
	}
	for (auto* s : touchableSprites)
	{
	}
}
void SelectLevel::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	moveDir = 0;
}
void SelectLevel::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
