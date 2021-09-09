#pragma once
#include "gameNode.h"
class startScene : public gameNode
{
private:

public:
	startScene();
	~startScene();

public:
	HRESULT init();
	void release();
	void update();
	void render();

};

