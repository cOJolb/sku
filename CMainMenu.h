#pragma once
#include "gameNode.h"
class CMainMenu : public gameNode
{
private:
	bool isBreakoutTitle;
	bool isPassNextScene;
	int selectMenu;
	int alphaValue;
public:
	CMainMenu();
	~CMainMenu();

	HRESULT init();
	void release();
	void update();
	void render();
};

