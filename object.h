#pragma once
#include"gameNode.h"
#include"collider.h"

const int GRAVITY = 10;

struct S_unitImageInfo
{
	string unitName;
	string unitFoward;
	string unitState;
};

class C_fsm;
class C_object : public gameNode
{
protected:
	animation* ani;
	vector2 pt;
	vector2 prevPt;
	C_collider* collider;
	RECT rc;
	RECT futureRc;
	RECT futureRcL;
	RECT futureRcT;
	RECT futureRcR;
	RECT futureRcB;


	C_fsm* ai;
	vector<C_fsm*> vAi;

	S_unitImageInfo unitImageInfo;

	/*list<int> searchList;
	list<int>::iterator searchListI;*/

	int hp;
	int maxHp;

	float jumpPower;
	bool isJump;
	float unitDamage;
	int atkDelay;

	bool wallCollision;
	bool landCollision;

private:
	/*RECT tile;
	bool NONEtile;*/
public:
	C_object();
	virtual~C_object();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

public:
	C_fsm* getAi() { return ai; }
	void AI_init(C_object* _object, UNIT_TYPE _type);
	void AI_update();
	STATE_TYPE getstate();

public:
	vector2 getPt() { return pt; }
	C_collider* getCollider() { return collider; }
	bool getIsJump() { return isJump; }
	S_unitImageInfo getImageInfo() { return unitImageInfo; }
	animation* getAni() { return ani; }
	int getAtkDelay() { return atkDelay; }
	int gethp() { return hp; }
	int getmaxHp() { return maxHp; }

public:
	void setPt(vector2 _pt) { pt = _pt; }
	void setUnitImageInfo(string _name, string _Foward, string _state);
	void setAni(animation* _ani) { ani = _ani; }
	void sethp(int _hp) { hp = _hp; }
	void setFutureRc(RECT _rc) { futureRc = _rc; }

public:
	bool isCollision(C_collider* _left, C_collider* _right);
	bool isCollision(RECT _left, RECT _right);
	//void Jump();
	void Gravity();
	void isLand();
	void isBump();
	void isClogged();
	void isWall();
	void ptUpdate() { prevPt = pt; }
	void futureRcLTRB();
	

	
	
	

	
	
	
};

