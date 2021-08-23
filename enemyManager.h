#pragma once
//#include"CHopper.h"
//#include"CFly.h"
//#include"CHost.h"
//#include"CWORM.h"
//#include"CMulligan.h"
//#include"CGurdy.h"

#include"singleton.h"
class CMonster;

class CHopper;
class CFly;
class CHost;
class CWORM;
class CMulligan;
class CGurdy;
class Csmallfly;

class CCollider;

class CPlayer;
struct summon
{
	MONSTER_TYPE m_Mtype;
	Vec2 p_pos;
	bool isrespawn;
};
typedef vector<CMonster*> vminion;
typedef vector<CMonster*>::iterator viminion;

class enemyManager : public Singleton<enemyManager>
{
private:
	vminion _vminion;
	viminion _viminion;

	vector<summon> vsummon;
	vector<summon>::iterator visummon;

	CPlayer* player;

	int count;
private:
	//vminion _vminion;
	//viminion _viminion;
protected:
	

public:
	enemyManager();
	~enemyManager();
	

	HRESULT init();
	void release();
	void update();
	void render();

	void respawnMinion(MONSTER_TYPE type, Vec2 pos);
	void respawn(MONSTER_TYPE type, Vec2 pos);
	void eraserEnemy(int number) { _vminion.erase(_vminion.begin() + number); }
	void eraserAllEnemy() { _vminion.clear(); }

	vminion getvmonster() { return _vminion; }
	viminion getvimonster(int number);

	void SetPlayer(CPlayer* _player) { player = _player; }
	CPlayer* GetPlayer() { return player; }

	//void bossDie();
};

