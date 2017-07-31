//#include "Shop.h"
#include "Settings.h"
#include "MenuScene.h"
#include "HelloWorldScene.h"
#include "SelectLevelScene.h"
#include <string>
using std::string;
#include <iostream>
#include <sstream>>


USING_NS_CC;

Scene* Settings::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Settings::create();

	// add layer as a child to scene
	scene->addChild(layer, 0, 999);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Settings::init()
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
	backgroundSprite = Sprite::create("3.png");
	backgroundSprite->setAnchorPoint(Vec2::ZERO);
	backgroundSprite->setContentSize(playingSize);
	backgroundSprite->setScaleX((visibleSize.width / backgroundSprite->getContentSize().width) * 1);
	backgroundSprite->setScaleY((visibleSize.height / backgroundSprite->getContentSize().height) * 1);
	nodeItems->addChild(backgroundSprite, -1);

	auto spriteNode = Node::create();
	spriteNode->setName("spriteNode");

	// Shop sign
	auto spriteNode2 = Node::create();
	spriteNode2->setName("spriteNode2");
	auto sprite = Sprite::create("settings_sign.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(visibleSize.width * 0.35, visibleSize.height * 0.8);
	sprite->setScale(1.5);
	spriteNode2->addChild(sprite, -1);

	//Adding touchable sprites to vector, different type of sprites different vectors?
	//Enemy 1 vector
	//Player monsters 1 vector
	//Touchable sprites 1 vector, etc

	// Back button
	Touchables* back = new Touchables();
	back->init("back_button.png", "mainSprite", visibleSize.width * 0.8, visibleSize.height * 0.05, Touchables::T_BACK,1.2);
	// push back sprite vector
	touchableSprites.push_back(back);

	//Texts for debugging
	//label = Label::createWithTTF("label test", "fonts/Marker Felt.ttf", 32);
	//label->setPosition(500, 500);
	//nodeItems->addChild(label, 1);
	//label2 = Label::createWithTTF("label test", "fonts/Marker Felt.ttf", 32);
	//label2->setPosition(500, 200);
	//nodeItems->addChild(label2, 1);
	//health1 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 32);
	//health1->setPosition(400, 330);
	//nodeItems->addChild(health1, 1);
	//health2 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 32);
	//health2->setPosition(400, 300);
	//nodeItems->addChild(health2, 1);

	for (auto* s : touchableSprites)
	{
		spriteNode->addChild(s->getSprite(), 1);
	}

	auto moveEvent = MoveBy::create(1, Vec2(200, 0));  // Move to 200 pixels in 1 second
													   //Move to is absolute movement
													   //Move by is relative vector
													   //mainSprite->runAction(moveEvent->reverse());
													   //Cannot use action on more than 1, need to clone
													   //if wan to use moveEvent for another sprite, it will double to pixel and time

	auto delay = DelayTime::create(5.0f);
	auto delaySequence = Sequence::create(delay, delay->clone(), nullptr);
	auto sequence = Sequence::create(moveEvent, moveEvent->reverse(), delaySequence, nullptr); //Store all the events, end with nullptr for all sequence
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = CC_CALLBACK_2(Settings::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(Settings::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Settings::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->addChild(nodeItems, 1);
	this->addChild(spriteNode, 2);
	this->addChild(spriteNode2, 3);

	auto _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseUp = CC_CALLBACK_1(Settings::onMouseUp, this);
	_mouseListener->onMouseMove = CC_CALLBACK_1(Settings::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	this->scheduleUpdate();
	/*
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
	"CloseNormal.png",
	"CloseSelected.png",
	CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
	origin.y + closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("HAIIIIIIIII", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
	origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");
	auto sprite2 = Sprite::create("Blue_Front1.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	sprite2->setPosition(Vec2(visibleSize.width / 3 + origin.x, visibleSize.height / 5 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	this->addChild(sprite2, 0);
	*/
	//Shadow
	mLoc.set(.5f, .5f);
	mLocInc.set(.005f, .01f);
	shaderCharEffect = new GLProgram();
	shaderCharEffect->initWithFilenames("Basic.vsh", "CharEffect.fsh");
	shaderCharEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	shaderCharEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	shaderCharEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
	shaderCharEffect->link();
	shaderCharEffect->updateUniforms();
	state = GLProgramState::getOrCreateWithGLProgram(shaderCharEffect);
	state->setUniformVec2("loc", mLoc);

	//VERTEX_ATTRIB_COLOR
	//Not working
	//Gray scale
	proPostProcess = new GLProgram();
	proPostProcess->initWithFilenames("Basic.vsh", "GreyScale.fsh");
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD1, GLProgram::VERTEX_ATTRIB_TEX_COORD1);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD2, GLProgram::VERTEX_ATTRIB_TEX_COORD2);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD3, GLProgram::VERTEX_ATTRIB_TEX_COORD3);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_NORMAL, GLProgram::VERTEX_ATTRIB_NORMAL);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT, GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_INDEX, GLProgram::VERTEX_ATTRIB_BLEND_INDEX);
	proPostProcess->link();
	proPostProcess->updateUniforms();
	rendtex = RenderTexture::create(visibleSize.width, visibleSize.height);
	rendtex->retain();
	rendtexSprite = Sprite::createWithTexture(rendtex->getSprite()->getTexture());
	rendtexSprite->setTextureRect(Rect(0, 0, rendtexSprite->getTexture()->getContentSize().width, rendtexSprite->getTexture()->getContentSize().height));
	rendtexSprite->setAnchorPoint(Point::ZERO);
	rendtexSprite->setPosition(Vec2(-1.0, -1.0));
	rendtexSprite->setFlippedY(true);
	rendtexSprite->setGLProgram(proPostProcess);
	//this->addChild(rendtexSprite, 2);

	// Load sound

	////Shadow for touchable sprites
	//for (auto* s : touchableSprites)
	//{
	//	s->getSprite()->setGLProgram(shaderCharEffect);
	//	s->getSprite()->setGLProgramState(state);
	//}

	return true;
}
void Settings::update(float deltaTime)
{
	//auto cam = Camera::getDefaultCamera();
	/*rendtex->beginWithClear(1.0f, .0f, .0f, .0f);
	this->visit();
	rendtex->end();
	rendtexSprite->setTexture(rendtex->getSprite()->getTexture());
	rendtexSprite->setGLProgram(proPostProcess);*/
	//cam->setPosition(a->getSprite()->getPosition());

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
bool Settings::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{

	for (auto* s : touchableSprites)
	{
		std::stringstream oss;
		if (s->onTouchBegan(touch,event))
		{
			switch (s->GetType())
			{
			case Touchables::T_BACK:
			{
				CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5, MenuScene::createScene(), Color3B(0, 255, 255)));
				break;
			}
			}
		}
	}
	return false;
}
void Settings::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	for (auto* s : touchableSprites)
	{
		if (s->onTouchBegan(touch, event))
		{

		}
	}
}
void Settings::onMouseMove(Event *event)
{
	//HOVERING change sprite
	EventMouse* e = (EventMouse*)event;

	//for (auto* s : touchableSprites)
	//{
	//	if (s->checkMouseDown(event))
	//	{
	//		s->getSprite()->setTexture("shop.png");
	//		if (s->GetLabel() != nullptr)
	//		{
	//			s->GetLabel()->setColor(ccc3(0, 0, 255));
	//		}
	//	}
	//	else
	//	{
	//		s->getSprite()->setTexture("settings.png");
	//		if (s->GetLabel() != nullptr)
	//		{
	//			s->GetLabel()->setColor(ccc3(0, 200, 255));
	//		}
	//	}
	//}


	//for (auto* s : touchableSprites)
	//{
	//	// change
	//	if (s->checkMouseDown(event))
	//	{
	//		switch (s->GetType())
	//		{
	//		case Touchables::T_STARTGAME:
	//		{
	//			s->getSprite()->setTexture("startgame_button2.png");
	//			if (s->GetLabel() != nullptr)
	//			{
	//				s->GetLabel()->setColor(ccc3(0, 0, 255));
	//			}
	//			break;
	//		}
	//		case Touchables::T_SHOP:
	//		{
	//			s->getSprite()->setTexture("shop_button2.png");
	//			if (s->GetLabel() != nullptr)
	//			{
	//				s->GetLabel()->setColor(ccc3(0, 0, 255));
	//			}
	//			break;
	//		}
	//		case Touchables::T_SETTINGS:
	//		{
	//			s->getSprite()->setTexture("settings_button2.png");
	//			if (s->GetLabel() != nullptr)
	//			{
	//				s->GetLabel()->setColor(ccc3(0, 0, 255));
	//			}
	//			break;
	//		}
	//		case Touchables::T_EXIT:
	//		{
	//			s->getSprite()->setTexture("exit_button2.png");
	//			if (s->GetLabel() != nullptr)
	//			{
	//				s->GetLabel()->setColor(ccc3(0, 0, 255));
	//			}
	//			break;
	//		}
	//		}
	//	}
	//	else
	//	{
	//		switch (s->GetType())
	//		{
	//		case Touchables::T_STARTGAME:
	//		{
	//			s->getSprite()->setTexture("startgame_button.png");
	//			if (s->GetLabel() != nullptr)
	//			{
	//				s->GetLabel()->setColor(ccc3(0, 0, 255));
	//			}
	//			break;
	//		}
	//		case Touchables::T_SHOP:
	//		{
	//			s->getSprite()->setTexture("shop.png");
	//			if (s->GetLabel() != nullptr)
	//			{
	//				s->GetLabel()->setColor(ccc3(0, 0, 255));
	//			}
	//			break;
	//		}
	//		case Touchables::T_SETTINGS:
	//		{
	//			s->getSprite()->setTexture("settings.png");
	//			if (s->GetLabel() != nullptr)
	//			{
	//				s->GetLabel()->setColor(ccc3(0, 0, 255));
	//			}
	//			break;
	//		}
	//		case Touchables::T_EXIT:
	//		{
	//			s->getSprite()->setTexture("exit.png");
	//			if (s->GetLabel() != nullptr)
	//			{
	//				s->GetLabel()->setColor(ccc3(0, 0, 255));
	//			}
	//			break;
	//		}
	//		}
	//	}

	//}
}
void Settings::onMouseUp(Event *event)
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
				//CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5, MenuScene::createScene(), Color3B(0, 255, 255)));
				break;
			}
			}
		}
	}

}
void Settings::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5, HelloWorld::createScene(), Color3B(0, 255, 255)));
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		//moveDir = 10;
		//a->MoveChar(100);

	}

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		//moveDir = -10;
		//a->MoveChar(-100);
	}
	for (auto* s : touchableSprites)
	{
		//this->getChildByName("spriteNode")->getChildByName("mainSprite")->setPosition(Vec2(this->getChildByName("spriteNode")->getPosition().x + moveDir, this->getChildByName("spriteNode")->getPosition().y));
		//s->getSprite()->getBoundingBox().setRect(s->getSprite()->getPosition().x + moveDir, s->getSprite()->getPosition().y, s->getSprite()->getContentSize().width, s->getSprite()->getContentSize().height);
	}
}
void Settings::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	moveDir = 0;
	//a->MoveChar(0);
}
void Settings::menuCloseCallback(Ref* pSender)
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
