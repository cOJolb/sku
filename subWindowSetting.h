#pragma once
#include "gameNode.h"
class C_subWindowSetting : public gameNode
{
private:
	tagSampleTile objTile[10];
	tagSampleTile monsterTile[10];
	tagSampleTile roomTile[10];
	int currentIdx;
public:
	C_subWindowSetting();
	~C_subWindowSetting();

public:
	HRESULT init();
	void release();
	void update();
	void render();

public:
	void mapToolSetUp();
	void setMap();
};

