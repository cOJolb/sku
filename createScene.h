#pragma once
#include "gameNode.h"
class C_mapTool;
class createScene : public gameNode
{
private:
	C_mapTool* mapTool;
public:
	createScene();
	~createScene();

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

