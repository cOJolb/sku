#pragma once
#include"CMonster.h"

class CFly : public CMonster
{
private:

public:
	CFly();
	~CFly();

	HRESULT init(float x , float y );
	void release();
	void update();
	void render();
};