#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <string>
using std::string;
#include <iostream>
#include <sstream>>


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer,0,999);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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

	auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	float width = sprite->getContentSize().width;

	backgroundSprite = Sprite::create("1.png");
	backgroundSprite->setAnchorPoint(Vec2::ZERO);
	backgroundSprite->setContentSize(playingSize);
	backgroundSprite->setScaleX((visibleSize.width / backgroundSprite->getContentSize().width) * 1);
	backgroundSprite->setScaleY((visibleSize.height / backgroundSprite->getContentSize().height) * 1);

	nodeItems->addChild(backgroundSprite, -1);
	int loop = std::ceil(visibleSize.width / width);

	sprite->setPosition(0, 0);

	for (int i = 0; i < loop; i++)
	{
		auto sprite2 = Sprite::create("ZigzagGrass_Mud_Round.png");
		sprite2->setAnchorPoint(Vec2::ZERO);
		sprite2->setPosition(i * width, (visibleSize.height / 2) - sprite2->getContentSize().height);
		nodeItems->addChild(sprite2, 1);
	}

	auto spriteNode = Node::create();
	spriteNode->setName("spriteNode");

	//Adding touchable sprites to vector, different type of sprites different vectors?
	//Enemy 1 vector
	//Player monsters 1 vector
	//Touchable sprites 1 vector, etc
	a = new Touchables();
	a->init("Button1.png", "mainSprite", visibleSize.width * 0.1, visibleSize.height * 0.1, Touchables::T_SUMMONBUT1);
	a->getSprite()->setScale(0.5);

	Touchables* b = new Touchables();
	b->init("Button1.png", "mainSprite", visibleSize.width * 0.3, visibleSize.height * 0.1, Touchables::T_SUMMONBUT2);
	b->getSprite()->setScale(0.5);

	Touchables* c = new Touchables();
	c->init("Button1.png", "mainSprite", visibleSize.width * 0.5, visibleSize.height * 0.1, Touchables::T_SUMMONBUT3);
	c->getSprite()->setScale(0.5);

	
	/*auto mainSprite = Sprite::create("Blue_Front1.png");
	mainSprite->setAnchorPoint(Vec2(0, 0));
	mainSprite->setPosition(100, visibleSize.height/2 + width);
	mainSprite->setName("mainSprite");*/

	//Texts for debugging
	label = Label::createWithTTF("label test", "fonts/Marker Felt.ttf", 32);
	label->setPosition(500,500);
	nodeItems->addChild(label,1);
	label2 = Label::createWithTTF("label test", "fonts/Marker Felt.ttf", 32);
	label2->setPosition(500, 200);
	nodeItems->addChild(label2,1);
	health1 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 32);
	health1->setPosition(400, 330);
	nodeItems->addChild(health1,1);
	health2 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 32);
	health2->setPosition(400, 300);
	nodeItems->addChild(health2,1);

	

	touchableSprites.push_back(a);
	touchableSprites.push_back(b);
	touchableSprites.push_back(c);

	for (auto* s : touchableSprites)
	{
		spriteNode->addChild(s->getSprite(), 1);
	}
	a->SetText("BUT 1",3, "fonts/Marker Felt.ttf");
	b->SetText("BUT 2", 3, "fonts/Marker Felt.ttf");
	c->SetText("BUT 3", 3, "fonts/arial.ttf");

	auto moveEvent = MoveBy::create(1, Vec2(200, 0));  // Move to 200 pixels in 1 second
	//Move to is absolute movement
	//Move by is relative vector
	//mainSprite->runAction(moveEvent->reverse());
	//Cannot use action on more than 1, need to clone
	//if wan to use moveEvent for another sprite, it will double to pixel and time

	auto delay = DelayTime::create(5.0f);
	auto delaySequence = Sequence::create(delay, delay->clone(), nullptr);
	auto sequence = Sequence::create(moveEvent, moveEvent->reverse(), delaySequence, nullptr); //Store all the events, end with nullptr for all sequence
	//mainSprite->runAction(sequence);
	//mainSprite->runAction(sequence->reverse());

	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//nodeItems->addChild(sprite, 0);
	this->addChild(nodeItems, 1);
	this->addChild(spriteNode, 2);

	auto _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
	_mouseListener->onMouseMove = CC_CALLBACK_1(HelloWorld::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

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

	mLoc.set(.5f, .5f);
	mLocInc.set(.005f, .01f);

	//Shadow
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
	//Grey scale
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
	rendtexSprite->setPosition(Vec2(-1.0,-1.0));
	rendtexSprite->setFlippedY(true);
	rendtexSprite->setGLProgram(proPostProcess);
	//this->addChild(rendtexSprite, 2);

	////Shadow for touchable sprites
	//for (auto* s : touchableSprites)
	//{
	//	s->getSprite()->setGLProgram(shaderCharEffect);
	//	s->getSprite()->setGLProgramState(state);
	//}

	return true;
}
void HelloWorld::update(float deltaTime)
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
	auto moveEvent = MoveBy::create(0, Vec2(1, 0));
	auto moveEvents = MoveBy::create(0, Vec2(-1, 0));

	//Movement of monsters/player monsters
	//Play their respective animation sprites for movement here
	for (auto* s : monsters)
	{
		if (s != nullptr)
		{
			s->Update(deltaTime);

			if (s->move && s->getSprite() != nullptr)
			{
				if (s->GetTag() == "right")
				{
					s->getSprite()->setPosition(s->getSprite()->getPosition().x - 1, s->getSprite()->getPosition().y);
				}
				if (s->GetTag() == "left")
					s->getSprite()->setPosition(s->getSprite()->getPosition().x + 1, s->getSprite()->getPosition().y);
			}
		}
	}
	//Collision detection between monsters/player's monsters
	for (std::vector<GameChar *>::iterator a = monsters.begin(); a != monsters.end(); ++a)
	{
		GameChar *go = (GameChar *)*a;
		for (std::vector<GameChar*>::iterator it2 = a + 1; it2 != monsters.end(); ++it2)
		{
			GameChar*other = (GameChar*)*it2;
			GameChar *goA = go, *goB = other;
			
			if (goA != NULL && goB != NULL)
			{
				if (goA->getSprite() != nullptr && goB->getSprite() != nullptr)
				{
					Rect rect1 = goA->getSprite()->getBoundingBox();
					Rect rect2 = goB->getSprite()->getBoundingBox();
					{
						//If anything is in collision
						if (rect1.intersectsRect(rect2))
						{
							//Check if the tag not the same, all monsters have same tags, all players have same tags
							if (goA->GetTag() != goB->GetTag())
							{
								goA->move = false;
								goB->move = false;
								goA->ReduceTimer(deltaTime);
								goB->ReduceTimer(deltaTime);
								std::stringstream oss;

								oss << goA->GetAttackTimer() << "      " << goA->GetHealth();

								//health1->setString(oss.str());

								oss.str("");
								oss << goB->GetAttackTimer() << "      " << goB->GetHealth();
								//health2->setString(oss.str());
								oss.str("");

								//Attack timing?? Not really needed right now
								//Can play any animations here
								if (goA->GetAttackTimer() <= 0)
								{
									goB->MinusHealth(goA->GetDamage());									
									goA->ResetAttackTime();
								}
								if (goB->GetAttackTimer() <= 0)
								{
									goA->MinusHealth(goB->GetDamage());
									goB->ResetAttackTime();
								}
							}
						}
						if (goA->GetHealth() <= 0)
						{
							goA->RemoveSprite();
							for (std::vector<GameChar *>::iterator a = monsters.begin(); a != monsters.end(); ++a)
							{
								GameChar *go = (GameChar *)*a;
								if (go->GetTag() != goA->GetTag())
								{
									go->move = true;
								}
							}
						}
						if (goB->GetHealth() <= 0)
						{
							goB->RemoveSprite();
							for (std::vector<GameChar *>::iterator a = monsters.begin(); a != monsters.end(); ++a)
							{
								GameChar *go = (GameChar *)*a;
								if (go->GetTag() != goB->GetTag())
								{
									go->move = true;
								}
							}
							goA->move = true;
						}
					}
				}
			}
		}
	}
}
void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	for (auto* s : touchableSprites)
	{
		if (s->onTouchBegan(touch, event))
		{

		}
	}
}
void HelloWorld::onMouseMove(Event *event)
{
	//HOVERING change sprite
	EventMouse* e = (EventMouse*)event;

	for (auto* s : touchableSprites)
	{
		if (s->checkMouseDown(event))
		{
			s->getSprite()->setTexture("Button2.png");
		}
		else
			s->getSprite()->setTexture("Button1.png");
	}
}

void HelloWorld::onMouseUp(Event *event)
{
	EventMouse* e = (EventMouse*)event;
	
	std::stringstream oss;
	oss << e->getLocationInView().x;
	label2->setString(oss.str());

	//Detection for touching any touchable sprite

	//Buttons to summon monsters/players
	for (auto* s : touchableSprites)
	{	
		std::stringstream oss;

		//Checking if point is within sprite's box, and the tag of sprite
		if (s->checkMouseDown(event))
		{
			if (s->GetType() == Touchables::T_SUMMONBUT1)
			{
				s->getSprite()->setPosition(Vec2(100, 400));
				label->setString("Touched 1st Button!");

				//Spawn monster
				GameChar* dc = new GameChar();
				dc->init("Blue_Front1.png", "monster", visibleSize.width - visibleSize.width, visibleSize.height*0.5, "left",10,3,1);
				this->getChildByName("spriteNode")->addChild(dc->getSprite(), 1);
				dc->getSprite()->setGLProgram(shaderCharEffect);
				dc->getSprite()->setGLProgramState(state);
				monsters.push_back(dc);
			}
			if (s->GetType() == Touchables::T_SUMMONBUT2)
			{
				//s->getSprite()->setPosition(Vec2(300, 100));
				label->setString("Touched 2nd Button!");

				//Spawn monster
				GameChar* dc = new GameChar();
				dc->init("ZigzagGrass_Mud_Round.png", "monster", visibleSize.width, visibleSize.height*0.5, "right",10,5,2);
				dc->getSprite()->setGLProgram(shaderCharEffect);
				dc->getSprite()->setGLProgramState(state);
				this->getChildByName("spriteNode")->addChild(dc->getSprite(), 1);
				monsters.push_back(dc);
			}
			if (s->GetType() == Touchables::T_SUMMONBUT3)
			{
				label->setString("Touched 3rd Button!");
			}
		}
	}
	//a->MoveCharByCoord(e->getCursorX(), e->getCursorY());
}
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	moveDir = 0;
	//a->MoveChar(0);
}
void HelloWorld::menuCloseCallback(Ref* pSender)
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
