#include "Shop.h"
#include "MenuScene.h"
#include "HelloWorldScene.h"
#include "SelectLevelScene.h"
#include "ui\CocosGUI.h"
#include <string>
using std::string;
#include "PlayerMonsterDatabase.h"
#include <iostream>
#include <sstream>
#include <fstream>
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
	this->setTouchEnabled(true);

	visibleSize = Director::getInstance()->getWinSizeInPixels();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	ui::ScrollView * scrollView = ui::ScrollView::create();
	scrollView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	scrollView->setBackGroundImage("2.png");
	scrollView->setBounceEnabled(true);
	scrollView->setContentSize(visibleSize);
	scrollView->setInnerContainerSize(Size(3000, 3000));
	scrollView->setTouchEnabled(true);
	scrollView->setSwallowTouches(false);

	scrollView->setAnchorPoint(Vec2::ZERO);
	scrollView->setPosition(Vec2(0, 0));
	auto nodeItems = Node::create();
	nodeItems->setName("nodeItems");
	// Background
	backgroundSprite = Sprite::create("2.png");
	backgroundSprite->setAnchorPoint(Vec2::ZERO);
	backgroundSprite->setContentSize(playingSize);
	backgroundSprite->setScaleX((visibleSize.width / backgroundSprite->getContentSize().width) * 1);
	backgroundSprite->setScaleY((visibleSize.height / backgroundSprite->getContentSize().height) * 1);
	//nodeItems->addChild(backgroundSprite, -1);


	playerGold = Label::createWithTTF("", "fonts/Marker Felt.ttf", 35);
	playerGold->setPosition(885, 670);
	playerGold->setPositionZ(10);
	nodeItems->addChild(playerGold, 1);

	auto spriteNode = Node::create();
	spriteNode->setName("spriteNode");
	auto scrollNode = Node::create();
	scrollNode->setName("scrollNode");

	// Shop button
	Touchables* shop = new Touchables();
	shop->init("red_button1.png", "mainSprite", visibleSize.width * 0.35, visibleSize.height * 0.8, Touchables::T_SHOP, 1.2);
	shop->SetDisabled(true);
	shop->SetText("SHOP", 1, "fonts/Soos.ttf", ccc3(255, 255, 255), 0.f, 0.f);
	shop->GetLabel("label")->disableEffect();
	spriteNode->addChild(shop->getSprite());

	//ReadFileSize();
	//PassInShopItems();



	//database.ReadFileSize("levels/Database.txt");
	//database.PassInData();
	
	//vector<PlayerMonsterDatabase::MonsterTypes*> mt - new ;
	//mt = database.ReturnDatabase;
	// Back button

	float x = 0.05;
	bool a = false;
	float widthX = 0.5;
	float heightY = -100;
	//scrollView->setContentSize(Size(visibleSize.width,visibleSize.height));

	Inventory = { "cat","dog","zombie" ,"zombieb" };
	for (int i = 0; i < Inventory.size(); i++)
	{
		ShopItems* newItem = new ShopItems;
		if (PlayerMonsterDatabase::getInstance()->checkIfExist(Inventory[i]))
		{
			newItem->type = PlayerMonsterDatabase::getInstance()->GetFromDatabase(Inventory[i])->type;
			newItem->price = PlayerMonsterDatabase::getInstance()->GetFromDatabase(Inventory[i])->goldNeededShop;
			shopItems.push_back(newItem);
		}
	}
	CCUserDefault *def = CCUserDefault::sharedUserDefault();
	def->setIntegerForKey("currency", 2000);
	currency = def->getIntegerForKey("currency");
	def->flush();


	scrollView->setInnerContainerSize(Size(330 * shopItems.size(),1200));
	for (int i = 0; i < shopItems.size(); i++)
	{
		/*ui::Button* button = ui::Button::create("ShopHover.png", "ShopNoHover.png");
		button->setPosition(Vec2(scrollView->getContentSize().width / 2, 100));
		scrollView->addChild(button);*/
		if (shopItems[i] != NULL)
		{
			if (PlayerMonsterDatabase::getInstance()->checkIfExist(shopItems[i]->type))
			{
				Touchables* itemsToBuy = new Touchables();
				itemsToBuy->init("ShopHover.png", shopItems[i]->type.c_str(), scrollView->getContentSize().width * x, scrollView->getContentSize().height- heightY, Touchables::T_SHOP1, 0.3);
				itemsToBuy->SetToolTip(PlayerMonsterDatabase::getInstance()->GetFromDatabase(shopItems[i]->type)->tooltip + '\n' + cocos2d::StringUtils::toString(PlayerMonsterDatabase::getInstance()->GetFromDatabase(shopItems[i]->type)->goldNeededShop) + " gold" + '\n' + cocos2d::StringUtils::toString(PlayerMonsterDatabase::getInstance()->GetFromDatabase(shopItems[i]->type)->damage) + " damage", "wood.png", 200, 0, -itemsToBuy->getSprite()->getContentSize().height, 2);
				string firstSprite = PlayerMonsterDatabase::getInstance()->GetFromDatabase(shopItems[i]->type)->animationSprites;
				itemsToBuy->SetImage(firstSprite.append("1.png").c_str(), shopItems[i]->type.c_str(), 3);
				touchableSprites.push_back(itemsToBuy);
				x += 0.3;
			}
		}
	}
	// Back button
	Touchables* back = new Touchables();
	back->init("back_button.png", "mainSprite", visibleSize.width * 0.8, visibleSize.height * 0.05, Touchables::T_BACK, 1.2);
	touchableSprites.push_back(back);

	for (auto* s : touchableSprites)
	{
		if (s->GetType() == Touchables::T_BACK)
			spriteNode->addChild(s->getSprite(), 1);
		else
			scrollView->addChild(s->getSprite());
	}
	nodeItems->addChild(scrollView);
	/*nodeItems->addChild(scrollManager);
	scrollManager->addChild(scrollView);*/
	auto listener1 = EventListenerTouchOneByOne::create();
	a = listener1->isEnabled();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = CC_CALLBACK_2(Shop::onTouchBegan, this);
	listener1->onTouchMoved = CC_CALLBACK_2(Shop::onTouchMove, this);
	listener1->onTouchEnded = CC_CALLBACK_2(Shop::onTouchEnd, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);


	label = Label::createWithTTF("HI", "fonts/Marker Felt.ttf", 32);
	label->setString("HI");
	label->setPosition(visibleSize.width * 0.35, visibleSize.height * 0.2);
	spriteNode->addChild(label, 2);

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


	this->scheduleUpdate();


	return true;
}

void Shop::ReadFileSize()
{
	std::string line;
	ssize_t fileSize = 0;
	unsigned char * fileContents = NULL;
	string thisLine, result, fullPath, contents;
	string fileName = "Levels/Shop.txt";

	fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName.c_str());
	fileContents = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &fileSize);
	contents.append((char *)fileContents);

	std::istringstream fileStringStream(contents);
	string op;
	std::stringstream oss;
	while (std::getline(fileStringStream, line))
	{
		//line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
		++number_of_lines;
		oss.clear();
		oss << line;
		//ShopItems* newItem = new ShopItems;
		//newItem->type = line;
		//shopItems.push_back(newItem);
	}
	std::cout << shopItems.size();
	std::cout << "Number of lines in text file: " << number_of_lines << op;
}
void Shop::PassInShopItems()
{
	/*std::string line;
	ssize_t fileSize = 0;
	unsigned char * fileContents = NULL;
	string thisLine, result, fullPath, contents;
	string fileName = "Levels/Shop.txt";

	fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName.c_str());
	fileContents = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &fileSize);
	contents.append((char *)fileContents);

	std::istringstream fileStringStream(contents);
	string op;
	std::stringstream oss;
	while (std::getline(fileStringStream, line))
	{
		ShopItems* newItem = new ShopItems;
		newItem->type = line;
		shopItems.push_back(newItem);
		string a;
	}*/
}

void Shop::update(float deltaTime)
{
	if (moveDir != 0)
	{
		auto cam = Camera::getDefaultCamera();
		cam->setPosition(Vec2(cam->getPosition().x + moveDir, cam->getPosition().y));
	}
	std::stringstream oss;
	oss << "Gold: " << currency;
	playerGold->setString(oss.str());

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
				/*if(s->GetImg("but1")->getActionManager()!=nullptr)
				s->GetImg("but1")->stopAllActions();*/
			}
			switch (s->GetType())
			{

			case Touchables::T_SHOP1:
				if (s->GetDisabled() != true)
				{
					{
						s->getSprite()->setTexture("ShopNoHover.png");
						for (int i = 0; i < touchableSprites.size(); i++)
						{
							if (touchableSprites[i]->checkMouseDown(event))
							{
								string a = PlayerMonsterDatabase::getInstance()->GetFromDatabase(touchableSprites[i]->getSprite()->getName())->animationSprites;
								s->AnimateImage(a.c_str(), 1, PlayerMonsterDatabase::getInstance()->GetFromDatabase(touchableSprites[i]->getSprite()->getName())->spriteCount, PlayerMonsterDatabase::getInstance()->GetFromDatabase(touchableSprites[i]->getSprite()->getName())->spriteX, PlayerMonsterDatabase::getInstance()->GetFromDatabase(touchableSprites[i]->getSprite()->getName())->spriteY, 0.1);
							}
						}
					}
				}
				break;
			case Touchables::T_SHOP3:
				if (s->GetDisabled() != true)
				{
					{
						s->getSprite()->setTexture("ShopNoHover.png");
						//s->AnimateImage("Sprites/cat/walk/walk_", 1, 7, 177, 177,0.1);
					}
				}

				break;
			case Touchables::T_SHOP2:
				if (s->GetDisabled() != true)
				{
					{
						s->getSprite()->setTexture("Shop2NoHover.png");
						//s->AnimateImage("Sprites/cat/walk/walk_", 1, 7, 177, 177,0.1);
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
void Shop::onTouchEnd(cocos2d::Touch * touch, cocos2d::Event * event)
{
	label->setString("TOUCH END" + cocos2d::StringUtils::toString(touch->getLocationInView().x));

	for (auto* s : touchableSprites)
	{
		std::stringstream oss;
		if (s->onTouchBegan(touch,event))
		{
			switch (s->GetType())
			{
			case Touchables::T_BACK:
			{
				CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5, MenuScene::createScene(), Color3B(0, 0, 0)));
				//AudioEngine::play2d("audio/click.wav", false);
				break;
			}
			case Touchables::T_SHOP1:
			case Touchables::T_SHOP2:
			case Touchables::T_SHOP3:
			{
				if (!s->GetDisabled())
				{
					int a = PlayerMonsterDatabase::getInstance()->GetFromDatabase(s->getSprite()->getName())->goldNeededShop;
					if (currency >= a)
					{
						currency -= a;

						//AudioEngine::play2d("audio/purchase.wav", false);
						s->SetDisabled(true);
						s->SetImage("ducttape.png", "purchased", 1);
						s->StopAnimation();
					}
				}
				else
				{
					//AudioEngine::play2d("audio/disabled.wav", false);
				}
				break;
			}
			}
		}
		else
		{
			if (s->GetToolTip() != nullptr)
				s->GetToolTip()->setVisible(false);
		}
	}
}
void Shop::onTouchMove(cocos2d::Touch * touch, cocos2d::Event * event)
{
}
bool Shop::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	Vec2 opps = touch->getLocationInView();
	label->setString("TOUCH MOVE" + cocos2d::StringUtils::toString(touch->getLocationInView().x));
	for (auto* s : touchableSprites)
	{
		//change
		if (s->onTouchBegan(touch,event))
		{
			if (s->GetDisabled() != true)
			{
				if (s->GetToolTip() != nullptr && s->GetDisabled() != true)
					s->GetToolTip()->setVisible(true);
			}
			else
			{
				/*if(s->GetImg("but1")->getActionManager()!=nullptr)
				s->GetImg("but1")->stopAllActions();*/
			}
			switch (s->GetType())
			{

			case Touchables::T_SHOP1:
				if (s->GetDisabled() != true)
				{
					{
						s->getSprite()->setTexture("ShopNoHover.png");
						for (int i = 0; i < touchableSprites.size(); i++)
						{
							if (touchableSprites[i]->checkMouseDown(event))
							{
								string a = PlayerMonsterDatabase::getInstance()->GetFromDatabase(touchableSprites[i]->getSprite()->getName())->animationSprites;
								s->AnimateImage(a.c_str(), 1, PlayerMonsterDatabase::getInstance()->GetFromDatabase(touchableSprites[i]->getSprite()->getName())->spriteCount, PlayerMonsterDatabase::getInstance()->GetFromDatabase(touchableSprites[i]->getSprite()->getName())->spriteX, PlayerMonsterDatabase::getInstance()->GetFromDatabase(touchableSprites[i]->getSprite()->getName())->spriteY, 0.1);
							}
						}
					}
				}
				break;
			case Touchables::T_SHOP3:
				if (s->GetDisabled() != true)
				{
					{
						s->getSprite()->setTexture("ShopNoHover.png");
						//s->AnimateImage("Sprites/cat/walk/walk_", 1, 7, 177, 177,0.1);
					}
				}

				break;
			case Touchables::T_SHOP2:
				if (s->GetDisabled() != true)
				{
					{
						s->getSprite()->setTexture("Shop2NoHover.png");
						//s->AnimateImage("Sprites/cat/walk/walk_", 1, 7, 177, 177,0.1);
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
	return true;
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
				//AudioEngine::play2d("audio/click.wav", false);
				break;
			}
			case Touchables::T_SHOP1:
			case Touchables::T_SHOP2:
			case Touchables::T_SHOP3:
			{
				if (!s->GetDisabled())
				{
					int a = PlayerMonsterDatabase::getInstance()->GetFromDatabase(s->getSprite()->getName())->goldNeededShop;
					if (currency >= a)
					{
						currency -= a;

						//AudioEngine::play2d("audio/purchase.wav", false);
						s->SetDisabled(true);
						s->SetImage("ducttape.png", "purchased", 1);
						s->StopAnimation();
					}
				}
				else
				{
					//AudioEngine::play2d("audio/disabled.wav", false);
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
