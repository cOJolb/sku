#pragma once
#include "gameNode.h"

class C_mapTool : public gameNode
{
private:
	tagRoom room;
	bool isDebug;

public:
	C_mapTool();
	~C_mapTool();

public:
	HRESULT init();
	void release();
	void update();
	void render();

public:
	void tileInit();
	void mapToolSetup();
	void setMap();

	bool save(const char* fileName);
	bool load(const char* fileName);

	OBSTACLE_TYPE objSelect(int frameX, int frameY);

	MONSTER_TYPE monsterSelect(int frameX, int frameY);

	S_tagTile* getTile() { return room.tile; }
};

