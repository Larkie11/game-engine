#include "Character.h"
#include "HelloWorldScene.h"

void GameChar::init(const char* sprite, const char* name, float x, float y, std::string tag, int health, float attackTimer, int damage,float speed)
{
	intDir = 0;
	fSpeed = speed;

	mainSprite = Sprite::create(sprite);
	//mainSprite = SpriteLoader();
	mainSprite->setAnchorPoint(Vec2(0, 0));
	mainSprite->setPosition(x, y);
	mainSprite->setName(name);
	this->tag = tag;
	this->health = health;
	this->defaultAttackTimer = attackTimer;
	this->attackTimer = defaultAttackTimer;
	this->damage = damage;
	mLoc.set(.5f, .5f);
	mLocInc.set(.005f, .01f);
	charEffect = new GLProgram();
	charEffect->initWithFilenames("Basic.vsh", "CharEffect.fsh");
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
	charEffect->link();
	charEffect->updateUniforms();
	move = true;
}

void GameChar::MoveChar(int dirX)
{
	intDir = dirX;
}

void GameChar::SpriteAnimation(int frames, const char* spriteName)
{
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(frames);
	animFrames.pushBack(SpriteFrame::create("Sprites\cat\walk\walk_1.png", Rect(0, 0, 256, 256)));
	animFrames.pushBack(SpriteFrame::create("Sprites\cat\walk\walk_2.png", Rect(0, 0, 256, 256)));
	animFrames.pushBack(SpriteFrame::create("Sprites\cat\walk\walk_3.png", Rect(0, 0, 256, 256)));
	animFrames.pushBack(SpriteFrame::create("Sprites\cat\walk\walk_4.png", Rect(0, 0, 256, 256)));
	animFrames.pushBack(SpriteFrame::create("Sprites\cat\walk\walk_5.png", Rect(0, 0, 256, 256)));
	animFrames.pushBack(SpriteFrame::create("Sprites\cat\walk\walk_6.png", Rect(0, 0, 256, 256)));
	animFrames.pushBack(SpriteFrame::create("Sprites\cat\walk\walk_7.png", Rect(0, 0, 256, 256)));

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
	Animate* animateWalk = Animate::create(animation);
	character1->runAction(RepeatForever::create(animateWalk));

	//SpriteBatchNode* spritebatch = SpriteBatchNode::create(spriteName);
	//SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	//cache->addSpriteFramesWithFile(spriteName);

	//character1 = Sprite::createWithSpriteFrameName("walk_1.png");
	//spritebatch->addChild(character1);
	////addChild(spritebatch);

	//Vector<SpriteFrame*> animFrames(frames);

	//char str[100] = { 0 };
	//for (int i = 0; i < frames; i++)
	//{
	//	sprintf(str, spriteName, i);
	//	SpriteFrame* frame = cache->getSpriteFrameByName(str);
	//	animFrames.pushBack(frame);
	//	//animFrames->addObject(frame);
	//}

	//auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
	//auto animate = Animate::create(animation);
	//character1->runAction(RepeatForever::create(animate));
}

void GameChar::Left()
{
	mainSprite->stopAllActions();

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(3);
	animFrames.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 60, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Left2.png", Rect(0, 0, 60, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Left3.png", Rect(0, 0, 60, 81)));

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);;
	Animate* animateLeft = Animate::create(animation);

	mainSprite->runAction(RepeatForever::create(animateLeft));
}
void GameChar::Right()
{
	mainSprite->stopAllActions();

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(3);
	animFrames.pushBack(SpriteFrame::create("Blue_Right1.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Right2.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Right3.png", Rect(0, 0, 65, 81)));

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);;
	Animate* animateRight = Animate::create(animation);

	mainSprite->runAction(RepeatForever::create(animateRight));
}



void GameChar::MoveCharByCoord(float x, float y)
{
	//auto moveEvent = MoveTo::create(1.0f, Vec2(x, y));
	mainSprite->stopAllActions();

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(3);
	animFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Back2.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Back3.png", Rect(0, 0, 65, 81)));

	
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);;
	Animate* animateRight = Animate::create(animation);

	mainSprite->runAction(RepeatForever::create(animateRight));
	float diffX = x - mainSprite->getPosition().x;
	float diffY = y - mainSprite->getPosition().y;
	Vec2 vec = Vec2(diffX, diffY);
	auto moveEvent = MoveBy::create(vec.length()*fSpeed, vec);

	/*
	auto callback = CallFunc::create([this]() {
		this->Stop();
	});*/

	auto callback = CallFunc::create([]() {
		auto scene = Director::getInstance()->getRunningScene();
		auto layer = scene->getChildByTag(999);
		HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
		if (helloLayer != NULL)
			helloLayer->GetPlayer()->Stop();
	});

	auto seq = Sequence::create(moveEvent, callback, nullptr);

	mainSprite->runAction(seq);
}

void GameChar::Update(float delta)
{
	if (intDir != 0)
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(1.0f, 0.f)*intDir * delta);
		mainSprite->runAction(moveEvent);
	}
	
	if (mainSprite != nullptr)
	{
		GLProgramState*state = GLProgramState::getOrCreateWithGLProgram(charEffect);
		mainSprite->setGLProgram(charEffect);
		mainSprite->setGLProgramState(state);
		state->setUniformVec2("loc", mLoc);
	}
}

void GameChar::Stop()
{
	intDir = 0;
	mainSprite->stopAllActions();

	Vector<SpriteFrame*> animFrames;

	animFrames.reserve(4);
	animFrames.pushBack(SpriteFrame::create("Blue_Front2.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Front3.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);;
	Animate* animateIdle = Animate::create(animation);

	//mainSprite->runAction(RepeatForever::create(animateIdle));
}

GameChar::GameChar()
{
	
}

GameChar::~GameChar()
{
}
