#pragma once
#include "gameNode.h"
class endScene : public gameNode
{
private:

public:
	endScene();
	~endScene();

public:
	HRESULT init();
	void release();
	void update();
	void render();

};

