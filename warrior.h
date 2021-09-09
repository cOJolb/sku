#pragma once
#include "skul.h"
class C_warrior : public C_skul
{
private:
	int delay;
protected:
public:
	C_warrior();
	~C_warrior();

public:
	//virtual HRESULT init();
	//virtual void release();
	//virtual void update();
	//virtual void render();
public:
	virtual void playerChange(vector2 _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo);
	virtual void playerDashMove(RECT& _rc, bool _isLeft, S_skulInfo _sInfo);
	virtual void playerAttack(vector2& _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo, int number);
	virtual void playerJumpAtk(vector2 _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo);
	virtual void skillA(vector2& _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo);
	virtual void skillB(vector2& _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo);
};

