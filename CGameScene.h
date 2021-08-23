#pragma once
#include "gameNode.h"
class CGameScene : public gameNode
{
private:
	bool isPause;
	bool isKeyDown;
	bool isPlayerDead;

	int frameCnt;
	int selectMenu;
public:
	CGameScene();
	~CGameScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

