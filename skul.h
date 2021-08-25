#pragma once
#include "player.h"
class C_skul : public C_player
{
protected:
private:

public:
	C_skul();
	virtual~C_skul();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

public:

};

