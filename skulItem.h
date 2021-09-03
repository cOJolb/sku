#pragma once
#include "item.h"


class C_crownskul : public C_item
{
public:
	//C_crownskul();
	C_crownskul(vector2 _pt);
	//virtual~C_crownskul();
public:
	virtual void render();
	virtual void render(vector2 _pt);
};

class C_littleBoneskul : public C_item
{
public:
	//C_littleBoneskul();
	C_littleBoneskul(vector2 _pt);
	//virtual~C_littleBoneskul();
public:
	virtual void render();
	virtual void render(vector2 _pt);
};