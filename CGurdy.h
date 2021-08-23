#pragma once
#include "CMonster.h"
class CGurdy : public CMonster
{
private:
	animation* anibody;
	RECT body;
	int maxHp;
public:
	CGurdy();
	~CGurdy();

	HRESULT init(float x , float y );
	void release();
	void update();
	void render();

	int getMaxHp() { return maxHp; }
};

