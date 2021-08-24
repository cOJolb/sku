#pragma once
#include"gameNode.h"
#include "player.h"

class mainGame : public gameNode
{
private:
	C_player* player;

public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);
};

