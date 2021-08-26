#pragma once
#include"gameNode.h"
#include "changePlayer.h"
#include "mapSetting.h"
#include "collision.h"
class mainGame : public gameNode
{
private:
	changePlayer* player;
	C_mapSetting* mapSetting;
	C_collision* collision;
public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);
};

