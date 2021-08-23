#pragma once
#include"gameNode.h"
class pixelCollision : public gameNode
{
private:


	image* _ball;
	RECT _rc;
	float _x, _y;
	int _probeY;

public:
	pixelCollision();
	~pixelCollision();


	HRESULT init();
	void release();
	void update();
	void render();
};

