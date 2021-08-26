#pragma once
#include"gameNode.h"
#include"collider.h"

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

	C_fsm* ai;
	vector<C_fsm*> vAi;

	S_unitImageInfo unitImageInfo;

	float jumpPower;
	bool isJump;
	float unitDamage;

private:

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

	vector2 getPt() { return pt; }
	void setPt(vector2 _pt) { pt = _pt; }

	C_collider* getCollider() { return collider; }

	bool isCollision(C_collider* _left, C_collider* _right);
	//void Jump();
	void Gravity();
	void isLand();
	void isBump();
	void isClogged();
	void isWall();

	void ptUpdate() { prevPt = pt; }
	
	bool getIsJump() { return isJump; }

	S_unitImageInfo getImageInfo() { return unitImageInfo; }
	void setUnitImageInfo(string _name, string _Foward, string _state);
	void setAni(animation* _ani) { ani = _ani; }
};

