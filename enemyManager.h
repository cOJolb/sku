#pragma once
//#include"CHopper.h"
//#include"CFly.h"
//#include"CHost.h"
//#include"CWORM.h"
//#include"CMulligan.h"
//#include"CGurdy.h"

#include"singleton.h"
class C_enemy;

typedef vector<C_enemy*> venemy;
typedef vector<C_enemy*>::iterator vienemy;

class enemyManager : public Singleton<enemyManager>
{
private:
	venemy vEnemy;
	vienemy viEnemy;

protected:

public:
	enemyManager();
	~enemyManager();

public:
	HRESULT init();
	void release();
	void update();
	void render();

public:
	void respawnEnemy(UNIT_TYPE _type, vector2 _pt);

	void eraserEnemy(int number) { vEnemy.erase(vEnemy.begin() + number); }
	void eraserAllEnemy() { vEnemy.clear(); }

	venemy getvEnemy() { return vEnemy; }
	vienemy getviEnemy(int number);
	//void bossDie();
};

