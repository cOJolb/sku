#pragma once
#include "collider.h"
class C_skul
{
private:
protected:
	S_skulInfo skulInfo;
	string unitName;
	C_collider* attackRange;
	SKUL_TYPE type;


	bool isPlayAtkA;
	bool isPlayAtkB;
	bool isPlaySkillA;
	bool isPlaySkillB;
	bool isPlayJumpAtk;
	bool isChange;
	
	int count;
public:
	C_skul();
	~C_skul();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update(vector2& _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo);
	virtual void render();

public:
	virtual void playerDashMove(RECT& _rc, bool _isLeft, S_skulInfo _sInfo);
	virtual void playerAttack(vector2& _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo, int number);
	virtual void playerJumpAtk(vector2 _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo);
	virtual void skillA(vector2& _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo);
	virtual void skillB(vector2& _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo);
	virtual void playerChange(vector2 _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo);
public :
	virtual bool PlayAtkA();
	virtual bool PlayAtkB();
	virtual bool PlaySkillA();
	virtual bool PlaySkillB();
	virtual bool PlayJumpAtk();
	virtual bool PlayChange();
public:
	S_skulInfo getskulInfo() { return skulInfo; }
	string getUnitName() { return unitName; }
	SKUL_TYPE getSkulType() { return type; }
	bool getisChagne() { return isChange; }
};

