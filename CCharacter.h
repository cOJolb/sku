#pragma once
#include "CObject.h"
#include"BulletManager.h"
class CFSM;
class CCharacter : public CObject
{
protected:
	int				hp;

	CFSM* m_pAI;
	vector<CFSM*> vAI;
public:
	CCharacter();
	CCharacter(Vec2 _pos, RECT _rc, int _hp);
	~CCharacter();

	virtual HRESULT init();
	virtual HRESULT init(vector2 _pt, RECT _rc, vector2 _objectPt, vector2 _objectSize, float _shadowdistance, vector2 _objectShadowPt, vector2 _objectShadowSize, int _hp);
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	CFSM* getAI() { return m_pAI; }
	void AI_init(CCharacter* monster, MONSTER_TYPE type);
	void AI_update();
	STATE_TYPE getstate();

	int gethp() { return hp; }
	void sethp(int _hp) { hp = _hp; }


};