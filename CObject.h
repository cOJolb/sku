#pragma once
#include"gameNode.h"
#include"CCollider.h"
class CObject : public gameNode
{
protected:
	vector2			pt;
	RECT			rc;
	animation*		ani;
	CCollider*		collider;
	CCollider*		colliderShadow;

	//animation anitest;

	int foward;
	vector2 prevPt;

	float shadowdistance;

	int moveCount;
	int moveNatual;

public:
	CObject();
	CObject(Vec2 _pos, RECT _rc);
	~CObject();

	virtual HRESULT init();
	virtual HRESULT init(vector2 _pt, RECT _rc, vector2 _objectPt, vector2 _objectSize, float _shadowdistance, vector2 _objectShadowPt, vector2 _objectShadowSize);
	virtual void release();
	virtual void update();
	virtual void render();

	vector2 getPt() { return pt; }
	void setPt(vector2 _pt) { pt = _pt; }

	RECT getRC() { return rc; }
	void setRC(RECT _rc) { rc = _rc; }

	void setAni(animation* ani) { this->ani = ani; }
	animation* getAni() { return ani; }

	CCollider* getcollider() { return collider; }
	CCollider* GetcolliderShadow() { return colliderShadow; }
	float getshadowdistance() { return shadowdistance; }
	void setshadowdistance(float distance) { shadowdistance = distance; }
	int GetFoward() { return foward; }

	int getMoveCount() { return moveCount; }
	void setMoveCount(int _moveCount) { moveCount = _moveCount; }
	int getMoveNatual() { return moveNatual; }
	void setMoveNatual(int _moveNatual) { moveNatual = _moveNatual; }
};

