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

	// Shop sign
	auto sprite = Sprite::create("shop_sign.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(visibleSize.width * 0.35, visibleSize.height * 0.8);
	sprite->setScale(1.5);
	spriteNode->addChild(sprite, -1);

	//Adding touchable sprites to vector, different type of sprites different vectors?
	//Enemy 1 vector
	//Player monsters 1 vector
	//Touchable sprites 1 vector, etc

	// Back button
	Touchables* back = new Touchables();
	back->init("back_button.png", "mainSprite", visibleSize.width * 0.8, visibleSize.height * 0.05, Touchables::T_BACK);
	back->getSprite()->setScale(1.2);

	Touchables* monster1 = new Touchables();
	monster1->init("ShopHover.png", "mainSprite", visibleSize.width * 0.05, visibleSize.height * 0.3, Touchables::T_SHOP1);
	monster1->getSprite()->setScale(0.3);

	Touchables* monster2 = new Touchables();
	monster2->init("Shop2Hover.png", "mainSprite", visibleSize.width * 0.35, visibleSize.height * 0.3, Touchables::T_SHOP2);
	monster2->getSprite()->setScale(0.3);

	Touchables* monster3 = new Touchables();
	monster3->init("ShopHover.png", "mainSprite", visibleSize.width * 0.65, visibleSize.height * 0.3, Touchables::T_SHOP3);
	monster3->getSprite()->setScale(0.3);

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
	monster1->SetToolTip("Monster unlock: YO", "Button1.png",200,0, -monster1->getSprite()->getContentSize().height,2);
	monster1->SetImage("walk_1.png", "but1",3);

	monster2->SetToolTip("Monster unlock: TOOOO", "Button1.png", 200, 0, -monster2->getSprite()->getContentSize().height, 2);
	monster2->SetImage("walk_1.png", "but1",3);

	monster3->SetToolTip("Monster unlock: BOOOO", "Button1.png", 200, 0, -monster2->getSprite()->getContentSize().height, 2);
	monster3->SetImage("walk_1.png", "but1",3);

	auto moveEvent = MoveBy::create(1, Vec2(200, 0));  // Move to 200 pixels in 1 second
													   //Move to is absolute movement
													   //Move by is relative vector
													   //mainSprite->runAction(moveEvent->reverse());
													   //Cannot use action on more than 1, need to clone
													   //if wan to use moveEvent for another sprite, it will double to pixel and time

	auto delay = DelayTime::create(5.0f);
	auto delaySequence = Sequence::create(delay, delay->clone(), nullptr);
	auto sequence = Sequence::create(moveEvent, moveEvent->reverse(), delaySequence, nullptr); //Store all the events, end with nullptr for all sequence

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
			switch (s->GetType())
			{
			case Touchables::T_SHOP1:
			case Touchables::T_SHOP3:
				if (s->GetDisabled() != true)
				{
					{
						s->getSprite()->setTexture("ShopNoHover.png");
					}
				}
			break;
			case Touchables::T_SHOP2:
				if (s->GetDisabled() != true)
				{
					{
						s->getSprite()->setTexture("Shop2NoHover.png");
					}
				}
			break;
			}

		}
		else
		{
			if (s->GetToolTip() != nullptr)
				s->GetToolTip()->setVisible(false);

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
					CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5, MenuScene::createScene(), Color3B(0, 255, 255)));
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
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/disabled.mp3");

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
void Shop::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	moveDir = 0;
	//a->MoveChar(0);
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
