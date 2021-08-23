#pragma once
#include"CMonster.h"
class BulletManager;
class CHost : public CMonster
{
private:


public:
	CHost();
	~CHost();

	HRESULT init(float x , float y );
	void release();
	void update();
	void render();

};

