#pragma once
#include "player.h"
class C_clown : public C_player
{
protected:
private:

public:
	C_clown();
	virtual~C_clown();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

public:

};

