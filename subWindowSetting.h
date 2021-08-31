#pragma once
#include"gameNode.h"
class C_subWindowSetting : public gameNode
{
private:
	S_tagSampleTile objTile[ObstacleTileX * ObstacleTileY];
	//S_tagSampleTile monsterTile[MONSTERTILEX * MONSTERTILEY];
	//S_tagSampleTile roomTile[ROOMTILEX * ROOMTILEY];
	int currentIdx;

public:
	C_subWindowSetting();
	~C_subWindowSetting();

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

public:
	void mapToolSetup();
	void setMap();
};

