#include "Touchables.h"
#include "HelloWorldScene.h"

void Touchables::init(const char* sprite, const char* name, float x, float y, Touchables::Types t)
{
	intDir = 0;
	fSpeed = 0.01;

	mainSprite = Sprite::create(sprite);
	mainSprite->setAnchorPoint(Vec2(0, 0));
	mainSprite->setPosition(x, y);
	mainSprite->setName(name);
	this->t = t;
	this->tag = tag;
	disabled = false;
	//Only for shader effect
	/*mLoc.set(.5f, .5f);
	mLocInc.set(.005f, .01f);
	charEffect = new GLProgram();
	charEffect->initWithFilenames("Basic.vsh", "CharEffect.fsh");
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
	charEffect->link();
	charEffect->updateUniforms();*/
}
void Touchables::SetDisabled(bool disabled)
{
	this->disabled = disabled;
}
bool Touchables::GetDisabled()
{
	return disabled;
}
void Touchables::SetImage(const char* sprite, const char* name)
{
	auto imgSprite = Sprite::create(sprite);
	imgSprite->setName(name);
	imgSprite->setPosition(Vec2(mainSprite->getContentSize().width*.5, mainSprite->getContentSize().height*.5));

	mainSprite->addChild(imgSprite, 1);
}
void Touchables::SetText(std::string text, float scale, std::string font, cocos2d::Color3B & color, float offsetx = 0, float offsety = 0)
{
	auto label = Label::createWithTTF(text, font, 32);
	this->color = color;
	label->setColor(color);
	// Position the text in the center of the sprite
	label->setPosition(Vec2(mainSprite->getContentSize().width*.5+offsetx,mainSprite->getContentSize().height*.5+offsety));
	label->setScale(scale);
	label->enableShadow(Color4B(0, 0, 255, 255), Size(2, 5), 0);
	label->setName("label");
	mainSprite->addChild(label, 1);
}
bool Touchables::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	Rect rect1 = mainSprite->getBoundingBox();
	Point touchPoint = touch->getLocation();

	if (rect1.containsPoint(touchPoint))
	{
		log("Touched");
	}
	else
	{
		log("Not touched");
	}

	return true; // true if the function wants to swallow the touch
}

bool Touchables::checkMouseDown(Event *event)
{
	//Check if this is getting touched
	EventMouse* e = (EventMouse*)event;

	if (mainSprite->getBoundingBox().containsPoint(e->getLocationInView()) && !disabled)
	{
		return true;
	}
	else
		return false;
}

void Touchables::Update(float delta)
{
	if (disabled && GetLabel()->getString() != "Locked")
	{
		GetLabel()->setString("Locked");
		GetLabel()->setColor(ccc3(0, 0, 0));
	}
	//Only for shader effect
	/*GLProgramState*state = GLProgramState::getOrCreateWithGLProgram(charEffect);
	mainSprite->setGLProgram(charEffect);
	mainSprite->setGLProgramState(state);
	state->setUniformVec2("loc", mLoc);*/
}

Touchables::Touchables()
{
	
}

Touchables::~Touchables()
{
}
