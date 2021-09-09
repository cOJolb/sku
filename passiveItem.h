#pragma once
#include "item.h"
class C_player;
class passiveItem
{
};

class C_DimLightDarkcite : public C_item
{
private:
	float stats;
public:
	//C_DimLightDarkcite();
	C_DimLightDarkcite(vector2 _pt);
	//~C_DimLightDarkcite();
public:
	virtual HRESULT init(C_player* _player);
	virtual void release(C_player* _player);
	//virtual void update(C_player* _player);
	virtual void render();
	virtual void render(vector2 _pt);
};

class C_MedalOfCarleon : public C_item
{
private:
	float stats;
public:
	//C_MedalOfCarleon();
	C_MedalOfCarleon(vector2 _pt);
	//~C_MedalOfCarleon();
public:
	virtual HRESULT init(C_player* _player);
	virtual void release(C_player* _player);
	virtual void update(C_player* _player);
	virtual void render();
	virtual void render(vector2 _pt);
};


class C_BasicCaerleonSword : public C_item
{
private:
	float stats;
public:
	//C_DimLightDarkcite();
	C_BasicCaerleonSword(vector2 _pt);
	//~C_DimLightDarkcite();
public:
	virtual HRESULT init(C_player* _player);
	virtual void release(C_player* _player);
	//virtual void update(C_player* _player);
	virtual void render();
	virtual void render(vector2 _pt);
};