#pragma once
#include"gameNode.h"
class CMapSettingSub : public gameNode
{
private:
	tagSampleTile objTile[OBJECTTILEX * OBJECTTILEY];
	tagSampleTile monsterTile[MONSTERTILEX * MONSTERTILEY];
	tagSampleTile roomTile[ROOMTILEX * ROOMTILEY];
	int currentIdx;
public:
	CMapSettingSub();
	~CMapSettingSub();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void mapToolSetup();
	void setMap();
};