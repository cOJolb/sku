#pragma once
#include"singleton.h"
class CCollider;
class CMap;
class CPlayer;
class CFSM;
class collisionManager : public Singleton<collisionManager>
{
protected:
	bool bossDie;
	vector2 bossDiePt;
	int count;
public:
	collisionManager();
	~collisionManager();

	bool isCollision(CCollider* _left, CCollider* _right);
	bool isCollision(RECT _left, RECT _right);
	//bool isRectCollision(RECT smallRc, RECT bigRc);

	int whereAreYouGoing(float& _prevX, float& _prevY, float _x, float _y);
	int whereAreYouGoing(vector2& _prevPt, vector2 _Pt);
	
	bool tileCollision(CMap* _map, vector2& _pt, vector2& _prevPt, int _foward , int _type);
	bool wallCollision(vector2& _objectPt, vector2 _startPt, float _sizeX, float _sizeY);
	DOOR_DIRECTION doorCollision(CMap* _map, CPlayer* player);
	bool goalCollision(CMap* _map, CPlayer* player);
	void monsterCollision(RECT& _rc, RECT& _prevRc, int _foward);
	vector2 sliding(int _foward, vector2 _pt);
	void stageCollision(CPlayer* _player);
	void isMonsterDie();
	void isBossDie();
	void bossdie(bool isdie) { bossDie = isdie; }
};