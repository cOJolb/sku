#pragma once
#include"gameNode.h"
#include"collider.h"
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

	int jumpPower;
	bool isJump;
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
	void AI_init(C_object* _object);
	void AI_update();
	STATE_TYPE getstate();

	vector2 getPt() { return pt; }
	void setPt(vector2 _pt) { pt = _pt; }

	C_collider* getCollider() { return collider; }

	bool isCollision(C_collider* _left, C_collider* _right);
	void Gravity();
	void isLand();
	void isClogged();
	void isWall();

	void ptUpdate() { prevPt = pt; }
};

