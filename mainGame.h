#pragma once
#include"gameNode.h"
#include "changePlayer.h"

class mainGame : public gameNode
{
private:
	changePlayer* player;

public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);
};

