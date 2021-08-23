#pragma once
#include"CMonster.h"

class CWORM : public CMonster
{
private:

public:
	CWORM();
	~CWORM();

	HRESULT init(float x , float y);
	void release();
	void update();
	void render();
};

