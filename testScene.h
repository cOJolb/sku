#pragma once
#include "gameNode.h"

#include"gameNode.h"
#include "player.h"
#include "mapSetting.h"
#include "collision.h"
#include "miniMap.h"
class testScene : public gameNode
{
private:
	C_player* player;
	C_mapSetting* mapSetting;
	C_collision* collision;
	C_miniMap* miniMap;
public: 
	testScene();
	~testScene();

public:
	HRESULT init();
	void release();
	void update();
	void render();

public:
	RECT checkGameSize();
};

