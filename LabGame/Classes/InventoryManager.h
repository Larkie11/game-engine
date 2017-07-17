#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class Inventory 
{
private:
	char invent[9];
	int invLimit;
	
public:
	void init();
	void addToInv();
	void getInv();
	void loadout();
	void changeLoadout();
	
	Inventory();
	~Inventory();
};

