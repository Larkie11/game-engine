#include "HelloWorldScene.h"
#include "SelectLevelScene.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "PlayerMonsterDatabase.h"
#include <string>
using std::string;
#include <iostream>
#include <sstream>>


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
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
	spawnTimer = 2;

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));
	auto nodeItems = Node::create();
	nodeItems->setName("nodeItems");

	auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	float width = sprite->getContentSize().width;
	auto physicsBody = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height), PhysicsMaterial(0.1, 1.0, 0.0));
	physicsBody->setDynamic(false);
	sprite->addComponent(physicsBody);

	backgroundSprite = Sprite::create("1.png");
	backgroundSprite->setAnchorPoint(Vec2::ZERO);
	backgroundSprite->setContentSize(playingSize);
	backgroundSprite->setScaleX((visibleSize.width / backgroundSprite->getContentSize().width) * 1);
	backgroundSprite->setScaleY((visibleSize.height / backgroundSprite->getContentSize().height) * 1);

	auto towerSprite = Sprite::create("tower.png");
	towerSprite->setAnchorPoint(Vec2::ZERO);
	float towerWidth = towerSprite->getContentSize().width;

	nodeItems->addChild(backgroundSprite, -1);
	int loop = std::ceil(visibleSize.width / width) +3;

	sprite->setPosition(0, 0);

	for (int i = 0; i < loop; i++)
	{
		auto sprite2 = Sprite::create("ZigzagGrass_Mud_Round.png");
		sprite2->setAnchorPoint(Vec2::ZERO);
		sprite2->setPosition((i * width)+(-sprite2->getContentSize().width), (visibleSize.height / 2) - sprite2->getContentSize().height);
		auto physicsBody2 = PhysicsBody::createBox(Size(sprite2->getContentSize().width, sprite2->getContentSize().height), PhysicsMaterial(0.1, 1.0, 0.0));
		physicsBody2->setDynamic(false);
		sprite2->addComponent(physicsBody2);
		nodeItems->addChild(sprite2, 1);
	}

	spriteNode = Node::create();
	spriteNode->setName("spriteNode");
	Inventory = { "cat","dog","zombie" ,"cat"};
	//Adding touchable sprites to vector, different type of sprites different vectors?
	//Enemy 1 vector
	//Player monsters 1 vector
	//Touchable sprites 1 vector, etc
	float x = 0.05;
	
	PlayerMonsterDatabase::getInstance()->GetFromDatabase("cat")->damage;

	for (int i = 0; i < Inventory.size(); i++)
	{
		Touchables* inventorySummon = new Touchables();
		inventorySummon->init("Button1.png", PlayerMonsterDatabase::getInstance()->GetFromDatabase(Inventory[i])->type.c_str(), visibleSize.width * x,
			visibleSize.height * 0.1, PlayerMonsterDatabase::getInstance()->GetFromDatabase(Inventory[i])->type, 0.4f);
		summonButtons.push_back(inventorySummon);
		x += 0.15;
	}

	// Back button
	Touchables* back = new Touchables();
	back->init("back_button.png", "mainSprite", visibleSize.width * 0.8, visibleSize.height * 0.1, Touchables::T_BACK, 1.2);

	// Gold Upgrade
	Touchables* goldUpgrade = new Touchables();
	goldUpgrade->init("gold.png", "mainSprite", visibleSize.width * 0.1, visibleSize.height * 0.8, Touchables::T_GOLDUPGRADE,0.3);
	goldUpgrade->SetToolTip("Increase gold speed", "wood.png", 200, 0, goldUpgrade->getSprite()->getContentSize().height*0.5, 1.5);
	goldUpgrade->GetToolTipLabel()->setScale(1.5);

	std::stringstream oss;
	oss << high_score;
	label2 = Label::createWithTTF(oss.str(), "fonts/Marker Felt.ttf", 32);
	label2->setPosition(500, 200);
	//nodeItems->addChild(label2,1);
	health1 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 32);
	health1->setPosition(400, 330);
	//nodeItems->addChild(health1,1);
	health2 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 32);
	health2->setPosition(400, 300);
	//nodeItems->addChild(health2,1);

	// Gold
	gold = Label::createWithTTF("", "fonts/Marker Felt.ttf", 35);
	gold->setPosition(885, 670);
	gold->setPositionZ(10);
	nodeItems->addChild(gold, 1);


	tower1Health = Label::createWithTTF("", "fonts/Marker Felt.ttf", 35);
	tower1Health->setPosition(visibleSize.width * 0.2, visibleSize.height * 0.3);
	tower1Health->setPositionZ(10);
	nodeItems->addChild(tower1Health, 1);


	tower2Health = Label::createWithTTF("", "fonts/Marker Felt.ttf", 35);
	tower2Health->setPosition(visibleSize.width * 0.7, visibleSize.height * 0.3);
	tower2Health->setPositionZ(10);
	nodeItems->addChild(tower2Health, 1);

	incomeSpeed = Label::createWithTTF("", "fonts/Marker Felt.ttf", 35);
	incomeSpeed->setPosition(700, 670);
	incomeSpeed->setPositionZ(10);
	nodeItems->addChild(incomeSpeed, 1);

	//touchableSprites.push_back(a);
	//touchableSprites.push_back(b);
	//touchableSprites.push_back(c);
	touchableSprites.push_back(back);
	touchableSprites.push_back(goldUpgrade);

	for (auto* s : touchableSprites)
	{
		spriteNode->addChild(s->getSprite(), 1);
	}
	for (auto* s : summonButtons)
	{
		spriteNode->addChild(s->getSprite(), 1);
	}
	for (int i = 0; i < summonButtons.size(); i++)
	{
		string temp = PlayerMonsterDatabase::getInstance()->GetFromDatabase(summonButtons[i]->GetTag())->animationSprites;
		temp.append("1.png");
		summonButtons[i]->SetImage(temp.c_str(), "but1", 1);
		string goldTemp = std::to_string(PlayerMonsterDatabase::getInstance()->GetFromDatabase(summonButtons[i]->GetTag())->goldNeededGame) + " GOLD";
		summonButtons[i]->SetText(goldTemp, 3, "fonts/Soos.ttf", ccc3(0, 200, 255), 0, summonButtons[i]->getSprite()->getContentSize().width*.3);
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.2);

	auto tower = new GameChar();
	tower->init("tower.png", "tower1", 0, visibleSize.height*0.5, "tower1",1000, 3, 1, 0);
	tower->getSprite()->setPositionX(0-(tower->getSprite()->getContentSize().width*0.38));
	tower->getSprite()->setScale(1);
	auto physicsBodyTower1 = PhysicsBody::createBox(Size(tower->getSprite()->getContentSize().width, tower->getSprite()->getContentSize().height), PhysicsMaterial(0.1, 1.0, 0.0));
	physicsBodyTower1->setDynamic(false);
	physicsBodyTower1->setCollisionBitmask(0x0000002);
	physicsBodyTower1->setContactTestBitmask(true);
	tower->getSprite()->addComponent(physicsBodyTower1);

	auto tower2 = new GameChar();
	tower2->init("tower.png", "tower2", visibleSize.width, visibleSize.height*0.5, "tower2",  1000, 3, 1, 0);
	tower2->getSprite()->setPositionX(visibleSize.width - tower->getSprite()->getContentSize().width * 0.6);
	tower2->getSprite()->setScale(1);
	auto physicsBodyTower2 = PhysicsBody::createBox(Size(tower2->getSprite()->getContentSize().width, tower2->getSprite()->getContentSize().height), PhysicsMaterial(0.1, 1.0, 0.0));
	physicsBodyTower2->setDynamic(false);
	physicsBodyTower2->setCollisionBitmask(0x0000001);
	physicsBodyTower2->setContactTestBitmask(true);


	towers.push_back(tower);
	towers.push_back(tower2);

	tower2->getSprite()->addComponent(physicsBodyTower2);
	spriteNode->addChild(tower->getSprite(), 2);
	spriteNode->addChild(tower2->getSprite(), 2);
	physicsBodyTower1->getNode()->setUserData(tower);
	physicsBodyTower2->getNode()->setUserData(tower2);

	//Amos try out animation
	// Sprite Sheet Animation Code Start
	/*Vector<SpriteFrame*> animFrames(7);
	char str[100] = { 0 };
	for (int i = 0; i < 7; i++)
	{
		sprintf(str, "walk_1.png", i);
		auto frame = SpriteFrame::create(str, Rect(0, 0, 40, 40));
		animFrames.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	auto animate = Animate::create(animation);
	sprite->runAction(animate);*/

	// Sprite Sheet Animation Code End

	//Move to is absolute movement
	//Move by is relative vector
	//mainSprite->runAction(moveEvent->reverse());
	//Cannot use action on more than 1, need to clone
	//if wan to use moveEvent for another sprite, it will double to pixel and time

	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->addChild(nodeItems, 1);
	this->addChild(spriteNode, 2);

	auto _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
	_mouseListener->onMouseMove = CC_CALLBACK_1(HelloWorld::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	contactListener->onContactPostSolve = CC_CALLBACK_1(HelloWorld::onInContact, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(HelloWorld::onContactEnd, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

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
	rendtexSprite->setPosition(Vec2(-1.0,-1.0));
	rendtexSprite->setFlippedY(true);
	rendtexSprite->setGLProgram(proPostProcess);

	//Load Sound
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgm2.wav", true);
	//audioMng->playBGM("game", 1);

	return true;
}
bool HelloWorld::onContactEnd(PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	GameChar* a;
	GameChar* b;

	if (bodyA->getOwner()->getUserData() != NULL)
		a = (GameChar*)bodyA->getOwner()->getUserData();
	if (bodyB->getOwner()->getUserData() != NULL)
		b = (GameChar*)bodyB->getOwner()->getUserData();

	if (bodyA->getCollisionBitmask() != bodyB->getCollisionBitmask())
	{
		if (a->GetTag() != "tower1" && a->GetTag() != "tower2")
		{
			a->getSprite()->getPhysicsBody()->setVelocity(Vec2(PlayerMonsterDatabase::getInstance()->GetFromDatabase(a->GetTag())->speed, 0));

			if (!a->move)
			{
				a->AnimateSprite(PlayerMonsterDatabase::getInstance()->GetFromDatabase(a->GetTag())->animationSprites.c_str(), 1, PlayerMonsterDatabase::getInstance()->GetFromDatabase(a->GetTag())->spriteCount, PlayerMonsterDatabase::getInstance()->GetFromDatabase(a->GetTag())->spriteX, PlayerMonsterDatabase::getInstance()->GetFromDatabase(a->GetTag())->spriteY, 0.1);
				a->move = true;
			}
		}
		if (b->GetTag() != "tower1" && b->GetTag() != "tower2")
		{
			b->getSprite()->getPhysicsBody()->setVelocity(Vec2(PlayerMonsterDatabase::getInstance()->GetFromDatabase(b->GetTag())->speed, 0));

			if (!b->move)
			{
				b->AnimateSprite(PlayerMonsterDatabase::getInstance()->GetFromDatabase(b->GetTag())->animationSprites.c_str(), 1, PlayerMonsterDatabase::getInstance()->GetFromDatabase(b->GetTag())->spriteCount, PlayerMonsterDatabase::getInstance()->GetFromDatabase(b->GetTag())->spriteX, PlayerMonsterDatabase::getInstance()->GetFromDatabase(b->GetTag())->spriteY, 0.1);
				b->move = true;
			}
		}
		return true;
	}
	else
		return false;
}
bool HelloWorld::onInContact(PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	GameChar* a;
	GameChar* b;

	if (bodyA->getOwner()->getUserData() != NULL)
		a = (GameChar*)bodyA->getOwner()->getUserData();
	if (bodyB->getOwner()->getUserData() != NULL)
		b = (GameChar*)bodyB->getOwner()->getUserData();
	if (bodyA->getCollisionBitmask() != bodyB->getCollisionBitmask())
	{
		a->ReduceTimer(dt);
		b->ReduceTimer(dt);

		if (a->GetAttackTimer() <= 0)
		{
			b->MinusHealth(a->GetDamage());
			a->ResetAttackTime();
		}
		if (b->GetAttackTimer() <= 0)
		{
			a->MinusHealth(b->GetDamage());
			b->ResetAttackTime();
		}
		return true;
	}
	else
	{
		return false;
	}
}
bool HelloWorld::onContactBegin(PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	GameChar* a;
	GameChar* b;
	if(bodyA->getOwner()->getUserData()!= NULL)
	a = (GameChar*)bodyA->getOwner()->getUserData();
	if (bodyB->getOwner()->getUserData() != NULL)
	b = (GameChar*)bodyB->getOwner()->getUserData();

	if (bodyA->getCollisionBitmask() != bodyB->getCollisionBitmask())
	{
		if (a->GetTag() != "tower1" && a->GetTag() != "tower2")
		{
			if(a->move)
			a->AnimateSprite(PlayerMonsterDatabase::getInstance()->GetFromDatabase(a->GetTag())->attackSprite.c_str(), 1, PlayerMonsterDatabase::getInstance()->GetFromDatabase(a->GetTag())->spriteCount, PlayerMonsterDatabase::getInstance()->GetFromDatabase(a->GetTag())->spriteX, PlayerMonsterDatabase::getInstance()->GetFromDatabase(a->GetTag())->spriteY, 0.1);
			a->getSprite()->getPhysicsBody()->setVelocity(Vec2(0, 0));
			a->getSprite()->getPhysicsBody()->setAngularDamping(1);
			a->getSprite()->getPhysicsBody()->setMoment(0);

			a->move = false;
		}
		if (b->GetTag() != "tower1" && b->GetTag() != "tower2")
		{
			if(b->move)
			b->AnimateSprite(PlayerMonsterDatabase::getInstance()->GetFromDatabase(b->GetTag())->attackSprite.c_str(), 1, PlayerMonsterDatabase::getInstance()->GetFromDatabase(b->GetTag())->spriteCount, PlayerMonsterDatabase::getInstance()->GetFromDatabase(b->GetTag())->spriteX, PlayerMonsterDatabase::getInstance()->GetFromDatabase(b->GetTag())->spriteY, 0.1);
			b->getSprite()->getPhysicsBody()->setVelocity(Vec2(0, 0));
			b->getSprite()->getPhysicsBody()->setAngularDamping(1);
			b->getSprite()->getPhysicsBody()->setMoment(0);
			b->move = false;
		}
		return true;
	}
	else
		return false;

}
void HelloWorld::update(float deltaTime)
{
	// Gold
	dt = deltaTime;
	money += 1 * speedOfIncome * deltaTime;
	std::stringstream oss;
	oss << "Gold: " << money;
	gold->setString(oss.str());


	oss.str("");

	for (auto* s : towers)
	{
		oss.str("");

		if (s->GetTag() == "tower1")
		{
			oss << "Own Tower: " << s->GetHealth();
			tower1Health->setString(oss.str());
		}

		if (s->GetTag() == "tower2")
		{
			oss << "Enemy Tower: " << s->GetHealth();
			tower2Health->setString(oss.str());
		}
	}
	oss.str("");

	oss << "Gold Speed: " << speedOfIncome;
	incomeSpeed->setString(oss.str());

	for (auto* s : touchableSprites)
	{
		s->Update(deltaTime);
	}
	
	if (spawnTimer > 0)
		spawnTimer -= deltaTime;

	else if (spawnTimer <= 0)
	{
		GameChar* enemy = new GameChar();
		string testingEnemy = "enemydog";
		if (PlayerMonsterDatabase::getInstance()->checkIfExist(testingEnemy) != false)
		{
			enemy->init("walk_2.png", "dog", visibleSize.width + 50, visibleSize.height*0.5, "enemydog", PlayerMonsterDatabase::getInstance()->GetFromDatabase(testingEnemy)->health, 1, PlayerMonsterDatabase::getInstance()->GetFromDatabase(testingEnemy)->damage, PlayerMonsterDatabase::getInstance()->GetFromDatabase(testingEnemy)->speed);
			enemy->getSprite()->setFlippedX(true);
			enemy->getSprite()->setScale(0.5);
			enemy->AnimateSprite(PlayerMonsterDatabase::getInstance()->GetFromDatabase(testingEnemy)->animationSprites.c_str(), 1, 7, 150, 173, 0.1);
			enemy->getSprite()->setGLProgram(shaderCharEffect);
			enemy->getSprite()->setGLProgramState(state);
			this->getChildByName("spriteNode")->addChild(enemy->getSprite(), 1);
			auto a = PhysicsBody::createBox(Size(enemy->getSprite()->getContentSize().width, enemy->getSprite()->getContentSize().height), PhysicsMaterial(0.1, 1.0, 0.0));
			a->setCollisionBitmask(00000001);
			a->setTag(1);
			a->setRotationEnable(false);
			a->setVelocity(Vec2(enemy->GetSpeed(), 0));
			a->setContactTestBitmask(true);
			enemy->getSprite()->addComponent(a);
			a->getNode()->setUserData(enemy);
			monsters.push_back(enemy);
			spawnTimer = 7;
		}
	}

	//Movement of monsters/player monsters
	//Play their respective animation sprites for movement here
	for (auto* s : monsters)
	{
		s->Update(deltaTime);

		if (s != nullptr)
		{
			/*if (s->move && s->getSprite() != nullptr && s->GetHealth() >= 0)
			{
				PhysicsBody* curPhysics = s->getSprite()->getPhysicsBody();
				curPhysics->setRotationEnable(false);
				PlayerMonsterDatabase::getInstance()->GetFromDatabase(s->GetTag())->speed;
				curPhysics->setVelocity(Vec2(PlayerMonsterDatabase::getInstance()->GetFromDatabase(s->GetTag())->speed, 0.f));
			}*/

			if (s->GetHealth() <= 0)
			{
				s->RemoveSprite();
				monsters.erase(std::remove(monsters.begin(), monsters.end(),s), monsters.end());
			}
		}
	}
	//Collision detection between monsters/player's monsters
	//for (std::vector<GameChar *>::iterator a = monsters.begin(); a != monsters.end(); ++a)
	//{
	//	GameChar *go = (GameChar *)*a;
	//	for (std::vector<GameChar*>::iterator it2 = a + 1; it2 != monsters.end(); ++it2)
	//	{
	//		GameChar*other = (GameChar*)*it2;
	//		GameChar *goA = go, *goB = other;
	//		
	//		if (goA != NULL && goB != NULL)
	//		{
	//			if (goA->getSprite() != nullptr && goB->getSprite() != nullptr)
	//			{
	//				Rect rect1 = goA->getSprite()->getBoundingBox();
	//				Rect rect2 = goB->getSprite()->getBoundingBox();
	//				{
	//					//If anything is in collision
	//					if (rect1.intersectsRect(rect2))
	//					{
	//						//Check if the tag not the same, all monsters have same tags, all players have same tags
	//						if (goA->GetType() != goB->GetType())
	//						{
	//							
	//								//goA->move = false;
	//								if(goA->GetType() == GameChar::C_CAT)
	//									goA->AnimateSprite("Sprites/cat/attack/attack_", 1, 7, 177, 177,0.1);
	//								if (goA->GetType() == GameChar::C_DOG)
	//									goA->AnimateSprite("Sprites/dog/attack/attack_", 1, 7, 150, 173,0.1);
	//							
	//								//goB->move = false;
	//								if (goB->GetType() == GameChar::C_CAT)
	//									goB->AnimateSprite("Sprites/cat/attack/attack_", 1, 7, 177, 177, 0.1);
	//								if (goB->GetType() == GameChar::C_DOG)
	//									goB->AnimateSprite("Sprites/dog/attack/attack_", 1, 7, 150, 173, 0.1);
	//							
	//							goA->ReduceTimer(deltaTime);
	//							goB->ReduceTimer(deltaTime);
	//							std::stringstream oss;

	//							oss << goA->GetAttackTimer() << "      " << goA->GetHealth();

	//							//health1->setString(oss.str());

	//							oss.str("");
	//							oss << goB->GetAttackTimer() << "      " << goB->GetHealth();
	//							//health2->setString(oss.str());
	//							oss.str("");

	//							//Attack timing?? Not really needed right now
	//							//Can play any animations here
	//							if (goA->GetAttackTimer() <= 0)
	//							{
	//								goB->MinusHealth(goA->GetDamage());									
	//								goA->ResetAttackTime();
	//							}
	//							if (goB->GetAttackTimer() <= 0)
	//							{
	//								goA->MinusHealth(goB->GetDamage());
	//								goB->ResetAttackTime();
	//							}
	//						}
	//					}
	//					if (goA->GetHealth() <= 0)
	//					{
	//						goA->RemoveSprite();
	//						for (std::vector<GameChar *>::iterator a = monsters.begin(); a != monsters.end(); ++a)
	//						{
	//							GameChar *go = (GameChar *)*a;
	//							if (go->GetType() != goA->GetType())
	//							{
	//								go->move = true;
	//								if (go->GetType() == GameChar::C_CAT)
	//									go->AnimateSprite("Sprites/cat/walk/walk_", 1, 7, 177, 177, 0.05);
	//								if (go->GetType() == GameChar::C_DOG)
	//									go->AnimateSprite("Sprites/dog/walk/walk_", 1, 7, 150, 173, 0.1);
	//							}
	//						}
	//					}
	//					if (goB->GetHealth() <= 0)
	//					{
	//						goB->RemoveSprite();
	//						for (std::vector<GameChar *>::iterator a = monsters.begin(); a != monsters.end(); ++a)
	//						{
	//							GameChar *go = (GameChar *)*a;
	//							if (go->GetType() != goB->GetType())
	//							{
	//								go->move = true;
	//								if (go->GetType() == GameChar::C_CAT)
	//									go->AnimateSprite("Sprites/cat/walk/walk_", 1, 7, 177, 177, 0.05);
	//								if (go->GetType() == GameChar::C_DOG)
	//									go->AnimateSprite("Sprites/dog/walk/walk_", 1, 7, 150, 173, 0.1);
	//							}
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
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
	//audioMng->playBGM("game", 1);
	//HOVERING change sprite
	EventMouse* e = (EventMouse*)event;

	for (auto* s : summonButtons)
	{
		if (s->checkMouseDown(event))
		{
			if (s->GetType() != Touchables::T_BACK && s->GetType() != Touchables::T_GOLDUPGRADE)
				s->getSprite()->setTexture("Button2.png");

			if (s->GetToolTip() != nullptr && s->GetDisabled() != true)
				s->GetToolTip()->setVisible(true);

			if (s->GetLabel("label") != nullptr)
			{
				s->GetLabel("label")->setColor(ccc3(0, 0, 255));
			}
		}
		else
		{
			if (s->GetToolTip() != nullptr)
				s->GetToolTip()->setVisible(false);

			if (s->GetType() != Touchables::T_BACK && s->GetType() != Touchables::T_GOLDUPGRADE)

				s->getSprite()->setTexture("Button1.png");
			if (s->GetLabel("label") != nullptr)
			{
				s->GetLabel("label")->setColor(ccc3(0, 200, 255));
			}
		}
	}
	for (auto* s : touchableSprites)
	{
		if (s->checkMouseDown(event))
		{
			if (s->GetType() != Touchables::T_BACK && s->GetType() != Touchables::T_GOLDUPGRADE)
			s->getSprite()->setTexture("Button2.png");

			if (s->GetToolTip() != nullptr && s->GetDisabled() != true)
				s->GetToolTip()->setVisible(true);

			if (s->GetLabel("label") != nullptr)
			{
				s->GetLabel("label")->setColor(ccc3(0, 0, 255));
			}
		}
		else
		{
			if (s->GetToolTip() != nullptr)
				s->GetToolTip()->setVisible(false);

			if (s->GetType() != Touchables::T_BACK && s->GetType() != Touchables::T_GOLDUPGRADE)

			s->getSprite()->setTexture("Button1.png");
			if (s->GetLabel("label") != nullptr)
			{
				s->GetLabel("label")->setColor(ccc3(0, 200, 255));
			}
		}
	}
}


void HelloWorld::onMouseUp(Event *event)
{
	EventMouse* e = (EventMouse*)event;

	//Detection for touching any touchable sprite
	GameChar* dc = new GameChar();

	for (int i = 0; i < summonButtons.size(); i++)
	{
		if (summonButtons[i]->checkMouseDown(event))
		{
			PhysicsBody* body;
			if (money > PlayerMonsterDatabase::getInstance()->GetFromDatabase(summonButtons[i]->GetTag())->goldNeededGame)
			{

				if (PlayerMonsterDatabase::getInstance()->GetFromDatabase(summonButtons[i]->GetTag())->type == "cat")
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/meow.mp3");
				}
				if (PlayerMonsterDatabase::getInstance()->GetFromDatabase(summonButtons[i]->GetTag())->type == "dog")
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/woof.mp3");
				}

				money -= PlayerMonsterDatabase::getInstance()->GetFromDatabase(summonButtons[i]->GetTag())->goldNeededGame;
				string a = PlayerMonsterDatabase::getInstance()->GetFromDatabase(summonButtons[i]->GetTag())->animationSprites;
				string temp = a;
				temp.append("1.png");
				dc->init(temp.c_str(), PlayerMonsterDatabase::getInstance()->GetFromDatabase(summonButtons[i]->GetTag())->type.c_str(), visibleSize.width - visibleSize.width - 100, visibleSize.height*0.5, PlayerMonsterDatabase::getInstance()->GetFromDatabase(summonButtons[i]->GetTag())->type.c_str(), PlayerMonsterDatabase::getInstance()->GetFromDatabase(summonButtons[i]->GetTag())->health,1, PlayerMonsterDatabase::getInstance()->GetFromDatabase(summonButtons[i]->GetTag())->damage, PlayerMonsterDatabase::getInstance()->GetFromDatabase(summonButtons[i]->GetTag())->speed);
				dc->getSprite()->setScale(0.5);
				dc->AnimateSprite(a.c_str(), 1, PlayerMonsterDatabase::getInstance()->GetFromDatabase(summonButtons[i]->getSprite()->getName())->spriteCount, PlayerMonsterDatabase::getInstance()->GetFromDatabase(summonButtons[i]->getSprite()->getName())->spriteX, PlayerMonsterDatabase::getInstance()->GetFromDatabase(summonButtons[i]->getSprite()->getName())->spriteY, 0.1);
				this->setName(PlayerMonsterDatabase::getInstance()->GetFromDatabase(summonButtons[i]->GetTag())->type);
				this->getChildByName("spriteNode")->addChild(dc->getSprite(), 1);
				body = PhysicsBody::createBox(Size(dc->getSprite()->getContentSize().width, dc->getSprite()->getContentSize().height), PhysicsMaterial(0.1, 1.0, 0.0));
				body->setCollisionBitmask(00000002);
				body->setTag(1);
				body->setRotationEnable(false);
				body->setVelocity(Vec2(dc->GetSpeed(), 0));
				body->setContactTestBitmask(true);
				dc->getSprite()->addComponent(body);
				body->getNode()->setUserData(dc);
				monsters.push_back(dc);
			}
		}
	}
	//Buttons to summon monsters/players
	for (auto* s : touchableSprites)
	{	
		std::stringstream oss;
		PhysicsBody* a;

		//Checking if point is within sprite's box, and the tag of sprite
		if (s->checkMouseDown(event))
		{
			CCUserDefault *def = CCUserDefault::sharedUserDefault();
			switch (s->GetType())
			{
			case Touchables::T_SUMMONBUT3:
				break;
			case Touchables::T_BACK:
				def->setIntegerForKey("LevelUnlockedTest", 2);
				CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5, MenuScene::createScene(), Color3B(0, 0, 0)));
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/click.wav");
				break;
			case Touchables::T_GOLDUPGRADE:
				speedOfIncome += 10;
				break;
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
		CCUserDefault *def = CCUserDefault::sharedUserDefault();
		//Once finish then unlock second level, for now this is testing the unlock system with space
		def->setIntegerForKey("LevelUnlockedTest", 2);
		def->flush();
		CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5, SelectLevel::createScene(), Color3B(0, 255, 255)));
		break;
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
