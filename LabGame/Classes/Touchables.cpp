#include "Touchables.h"
#include "HelloWorldScene.h"
#include "AnimationManager.h"

void Touchables::init(const char* sprite, const char* name, float x, float y, Touchables::Types t, float scale)
{
	intDir = 0;
	fSpeed = 0.01;

	mainSprite = Sprite::create(sprite);
	mainSprite->setAnchorPoint(Vec2(0, 0));
	mainSprite->setPosition(x, y);
	mainSprite->setName(name);
	mainSprite->setScale(scale);
	this->t = t;
	this->tag = t;
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
void Touchables::init(const char* sprite, const char* name, float x, float y, string t, float scale)
{
	intDir = 0;
	fSpeed = 0.01;

	mainSprite = Sprite::create(sprite);
	mainSprite->setAnchorPoint(Vec2(0, 0));
	mainSprite->setPosition(x, y);
	mainSprite->setName(name);
	mainSprite->setScale(scale);
	this->tag = t;
	this->t = Touchables::T_SUMMONBUT1;
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
void Touchables::SetImage(const char* sprite, const char* name, float scale)
{
	auto imgSprite = Sprite::create(sprite);
	imgSprite->setName(name);
	imageName = name;
	imgSprite->setScale(scale);
	imgSprite->setPosition(Vec2(mainSprite->getContentSize().width*.5, mainSprite->getContentSize().height*.5));
	mainSprite->addChild(imgSprite, 1);
}
void Touchables::AnimateImage(const char* spriteFrameName, int startFrame, int frameCount, float width, float height, float delay)
{
	if (GetImg(imageName) != nullptr && !disabled)
	{
		if (GetImg(imageName)->getActionManager() != nullptr)
			GetImg(imageName)->stopAllActions();

		playingAnimation = true;

		AnimationManager a;
		a.PlayAnimation(GetImg(imageName), spriteFrameName, startFrame, frameCount, width, height, delay);
	}
}
void Touchables::SetToolTip(std::string text, const char* sprite, int opacity, float offsetx, float offsety, float scale)
{
	auto imgSprite = Sprite::create(sprite);
	imgSprite->setName("ToolTip");
	imgSprite->setPosition(Vec2(mainSprite->getContentSize().width*0.5 + offsetx, mainSprite->getContentSize().height + offsety));
	imgSprite->setOpacity(opacity);
	imgSprite->setScale(scale);
	auto label = Label::createWithTTF(text, "fonts/Marker Felt.ttf", 32);
	label->setPosition(Vec2(imgSprite->getContentSize().width*.5, imgSprite->getContentSize().height*.5));
	label->setName("toolTipLabel");
	mainSprite->addChild(imgSprite, 2);
	imgSprite->addChild(label, 3);
	imgSprite->setVisible(false);
}
void Touchables::SetText(std::string text, float scale, const char* font, cocos2d::Color3B color, float offsetx = 0, float offsety = 0)
{
	auto label = Label::createWithTTF(text, font, 32);
	this->color = color;
	label->setColor(color);
	// Position the text in the center of the sprite
	label->setPosition(Vec2(mainSprite->getContentSize().width*.5 + offsetx, mainSprite->getContentSize().height*.5 + offsety));
	label->setScale(scale);
	label->enableShadow(Color4B(0, 0, 255, 255), Size(2, 5), 0);
	label->setName("label");
	mainSprite->addChild(label, 1);
}
bool Touchables::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{

	cocos2d::Vec2 p = touch->getLocation();
	cocos2d::Rect rect = mainSprite->getBoundingBox();
	if (rect.containsPoint(mainSprite->getParent()->convertToNodeSpace(p)))
	{
		// so you touched the Sprite, do something about it
		return true;
	}
	return false;
}

bool Touchables::checkMouseDown(Event *event)
{
	//Check if this is getting touched
	EventMouse* e = (EventMouse*)event;
	Vec2 posInWorldSpace = e->getLocationInView();

	if (mainSprite->getBoundingBox().containsPoint(mainSprite->getParent()->convertToNodeSpace(posInWorldSpace)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Touchables::Update(float delta)
{
	if (disabled && GetLabel("label") != nullptr)
	{
		if (GetLabel("label")->getString() != "Locked" && t != Touchables::T_SHOP)
		{
			GetLabel("label")->setString("Locked");
			GetLabel("label")->setColor(ccc3(0, 0, 0));
		}
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
