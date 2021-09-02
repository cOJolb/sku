#pragma once
#include"gameNode.h"
#include "testScene.h"
#include "createScene.h"
#include "itemScene.h"
class mainGame : public gameNode
{
private:
	RECT gameSize;
public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);

public:
	RECT checkGameSize();

};

