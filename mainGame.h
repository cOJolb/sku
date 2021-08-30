#pragma once
#include"gameNode.h"
#include "player.h"
#include "mapSetting.h"
#include "collision.h"
#include "miniMap.h"
class C_subWindowSetting;
class mainGame : public gameNode
{
private:
	C_player* player;
	C_mapSetting* mapSetting;
	C_collision* collision;
	C_miniMap* miniMap;
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

