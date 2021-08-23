#pragma once
#include "CUI.h"
class CBossUI : public CUI
{
private:
	CGurdy* boss;
	int minusHp;
	bool isDie;
	int count;
public:
	CBossUI();
	~CBossUI();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	void setBoss(CGurdy* _boss) { boss = _boss; }
};

