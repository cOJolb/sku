#pragma once
#include "stageScene.h"
class stage1_1 : public stageScene
{
private:

public:
	stage1_1();
	~stage1_1();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

