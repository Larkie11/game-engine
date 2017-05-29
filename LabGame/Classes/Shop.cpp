#include "Shop.h"
#include "MenuScene.h"
#include "HelloWorldScene.h"
#include "SelectLevelScene.h"
#include "SimpleAudioEngine.h"
#include <string>
using std::string;
#include <iostream>
#include <sstream>>


USING_NS_CC;

Scene* Shop::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Shop::create();

	// add layer as a child to scene
	scene->addChild(layer, 0, 999);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Shop::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	touchableSprites.clear();

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));
	
	auto nodeItems = Node::create();
	nodeItems->setName("nodeItems");
	// Background
	backgroundSprite = Sprite::create("2.png");
	backgroundSprite->setAnchorPoint(Vec2::ZERO);
	backgroundSprite->setContentSize(playingSize);
	backgroundSprite->setScaleX((visibleSize.width / backgroundSprite->getContentSize().width) * 1);
	backgroundSprite->setScaleY((visibleSize.height / backgroundSprite->getContentSize().height) * 1);
	nodeItems->addChild(backgroundSprite, -1);

	auto spriteNode = Node::create();
	spriteNode->setName("spriteNode");
	auto scrollNode = Node::create();
	scrollNode->setName("scrollNode");

	// Shop button
	Touchables* shop = new Touchables();
	shop->init("red_button1.png", "mainSprite", visibleSize.width * 0.35, visibleSize.height * 0.8, Touchables::T_SHOP, 1.2);
	shop->SetDisabled(true);
	shop->SetText("SHOP", 1, "fonts/Soos.ttf", ccc3(255, 255, 255), 0, 0);
	shop->GetLabel("label")->disableEffect();
	spriteNode->addChild(shop->getSprite());

	// Back button
	Touchables* back = new Touchables();
	back->init("back_button.png", "mainSprite", visibleSize.width * 0.8, visibleSize.height * 0.05, Touchables::T_BACK,1.2);

	Touchables* monster1 = new Touchables();
	monster1->init("ShopHover.png", "mainSprite", visibleSize.width * 0.05, visibleSize.height * 0.3, Touchables::T_SHOP1,0.3);

	Touchables* monster2 = new Touchables();
	monster2->init("Shop2Hover.png", "mainSprite", visibleSize.width * 0.35, visibleSize.height * 0.3, Touchables::T_SHOP2,0.3);

	Touchables* monster3 = new Touchables();
	monster3->init("ShopHover.png", "mainSprite", visibleSize.width * 0.65, visibleSize.height * 0.3, Touchables::T_SHOP3,0.3);

	// push back sprite vector
	touchableSprites.push_back(back);
	touchableSprites.push_back(monster1);
	touchableSprites.push_back(monster2);
	touchableSprites.push_back(monster3);

	for (auto* s : touchableSprites)
	{
		if (s->GetType() == Touchables::T_BACK)
			spriteNode->addChild(s->getSprite(), 1);
		else
			scrollNode->addChild(s->getSprite(), 1);
	}

	//Tool tips (Pop up UI)
	//Image in the middle of button
	monster1->SetToolTip("Monster unlock: YO", "wood.png",200,0, -monster1->getSprite()->getContentSize().height,2);
	monster1->SetImage("walk_1.png", "but1",3);

	monster2->SetToolTip("Monster unlock: TOOOO", "wood.png", 200, 0, -monster2->getSprite()->getContentSize().height, 2);
	monster2->SetImage("walk_1.png", "but1",3);

	monster3->SetToolTip("Monster unlock: BOOOO", "wood.png", 200, 0, -monster2->getSprite()->getContentSize().height, 2);
	monster3->SetImage("walk_1.png", "but1",3);

	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(Shop::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Shop::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->addChild(nodeItems, 1);
	this->addChild(spriteNode, 2);
	this->addChild(scrollNode, 3);

	auto _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseUp = CC_CALLBACK_1(Shop::onMouseUp, this);
	_mouseListener->onMouseMove = CC_CALLBACK_1(Shop::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchEnded = CC_CALLBACK_2(Shop::onTouchEnded, this);

	this->scheduleUpdate();

	// Load sound
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/click.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/purchase.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/disabled.mp3");

	return true;
}
void Shop::update(float deltaTime)
{
	if (moveDir != 0)
	{
		auto cam = Camera::getDefaultCamera();
		cam->setPosition(Vec2(cam->getPosition().x + moveDir, cam->getPosition().y));
	}

	for (auto* s : touchableSprites)
	{
		s->Update(deltaTime);
		if (s->GetImg("purchased") != nullptr)
			int a;
	}
}
void Shop::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	for (auto* s : touchableSprites)
	{
		if (s->onTouchBegan(touch, event))
		{

		}
	}
}
void Shop::onMouseMove(Event *event)
{
	//HOVERING over
	EventMouse* e = (EventMouse*)event;

	for (auto* s : touchableSprites)
	{
		//change
		if (s->checkMouseDown(event))
		{
			if (s->GetDisabled() != true)
			{
				if (s->GetToolTip() != nullptr && s->GetDisabled() != true)
					s->GetToolTip()->setVisible(true);
			}
			else
			{
				if(s->GetImg("but1")->getActionManager()!=nullptr)
				s->GetImg("but1")->stopAllActions();
			}
			switch (s->GetType())
			{
				
			case Touchables::T_SHOP1:
					if (s->GetDisabled() != true)
					{
						{
							s->getSprite()->setTexture("ShopNoHover.png");
							s->AnimateImage("Sprites/cat/walk/walk_", 1, 7, 177, 177,0.1);
						}
					}
				break;
			case Touchables::T_SHOP3:
				if (s->GetDisabled() != true)
				{
					{
						s->getSprite()->setTexture("ShopNoHover.png");
						s->AnimateImage("Sprites/cat/walk/walk_", 1, 7, 177, 177,0.1);
					}
				}
				
			break;
			case Touchables::T_SHOP2:
				if (s->GetDisabled() != true)
				{
					{
						s->getSprite()->setTexture("Shop2NoHover.png");
						s->AnimateImage("Sprites/cat/walk/walk_", 1, 7, 177, 177,0.1);
					}
				}
			break;
			}

		}
		else
		{
			if (s->GetToolTip() != nullptr)
				s->GetToolTip()->setVisible(false);
			s->StopAnimation();
			switch (s->GetType())
			{
			case Touchables::T_SHOP1:
			case Touchables::T_SHOP3:
			{
				
					s->getSprite()->setTexture("ShopHover.png");
				
			}
			break; 
			case Touchables::T_SHOP2:
			{
				
				s->getSprite()->setTexture("Shop2Hover.png");
			}
			break;
			}

		}

	}
}
void Shop::onMouseUp(Event *event)
{
	//Detection for touching any touchable sprite
	EventMouse* e = (EventMouse*)event;

	for (auto* s : touchableSprites)
	{
		std::stringstream oss;
		if (s->checkMouseDown(event))
		{
			switch (s->GetType())
			{
				case Touchables::T_BACK:
				{
					CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5, MenuScene::createScene(), Color3B(0, 0, 0)));
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/click.wav");
					break;
				}
				case Touchables::T_SHOP1:
				case Touchables::T_SHOP2:
				case Touchables::T_SHOP3:
				{
					if (!s->GetDisabled())
					{
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/purchase.wav");
						s->SetDisabled(true);
						s->SetImage("ducttape.png", "purchased", 1);
					}
					else
					{
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/disabled.mp3");
					}
					break;
				}
			}	
		}
	}

}
void Shop::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5, HelloWorld::createScene(), Color3B(0, 255, 255)));
	}
}
void Shop::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
}
void Shop::menuCloseCallback(Ref* pSender)
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
