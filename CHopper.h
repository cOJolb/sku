#pragma once
#include"CMonster.h"

class CHopper : public CMonster
{
private:
public:
	CHopper();
	~CHopper();

	HRESULT init(float x, float y);
	void release();
	void update();
	void render();
};

