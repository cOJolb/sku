#pragma once
#include "gameNode.h"
class CMapTool : public gameNode
{
private:
	CMapSetting* mapSet;
public:
	CMapTool();
	~CMapTool();

	HRESULT init();
	void release();
	void update();
	void render();
};

