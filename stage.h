#pragma once
#include "gameNode.h"
#include "player.h"
#include "mapSetting.h"
#include "collision.h"
#include "miniMap.h"
//#include "camera.h"


class C_stage : public gameNode
{
private:
	C_player* player;
	C_mapSetting* mapSetting;
	C_collision* collision;
	C_miniMap* miniMap;

	image* Door;
	animation* DoorAni;
	//camera* BackSecond;
public:
	C_stage();
	~C_stage();

public:
	HRESULT init();
	void release();
	void update();
	void render();

public:
	RECT checkGameSize();
	void curRelease();
	bool isNextStage();
};

