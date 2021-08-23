#pragma once
#include"gameNode.h"

class mainGame : public gameNode
{
private:
	



public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);


	
	
};

