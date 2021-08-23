#pragma once
#include"CMonster.h"

class Csmallfly : public CMonster
{
private:
public:
	Csmallfly();
	~Csmallfly();

	HRESULT init(float x, float y);
	void release();
	void update();
	void render();
};

