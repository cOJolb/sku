#pragma once
#include "CUI.h"
class CPlayer;
class CPlayerUI : public CUI
{
private:
public:
	CPlayerUI();
	~CPlayerUI();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(CPlayer* _player);
};

