#pragma once
#include "gameNode.h"
class C_mapTool : public gameNode
{
private:
	S_tagRoom room;
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
	bool save(const char* fileName);
	bool load(const char* fileName);

public:
	void tileInit();
	void mapToolSetup();
	void setMap();

	OBSTACLE_TYPE objSelect(int frameX, int frameY);

	//MONSTER_TYPE monsterSelect(int frameX, int frameY);

	S_tagTile* getTile() { return room.tile; }

	
};

