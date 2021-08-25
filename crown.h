#pragma once
#include "player.h"
class C_crown : public C_player
{
protected:
private:

public:
	C_crown();
	virtual~C_crown();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

public:

};

