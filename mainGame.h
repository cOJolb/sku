#pragma once
#include"gameNode.h"
#include "player.h"
#include "testScene.h"
#include "createScene.h"
#include "itemScene.h"
#include "stageScene.h"
#include "stage.h"
class mainGame : public gameNode
{
private:
	RECT gameSize;
	C_player* player;
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

