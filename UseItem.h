#pragma once
#include "CItem.h"
class CPlayer;
class CUseItem : public CItem
{
protected:
	USE_ITEM usetype;
	CPlayer* player;
	bool isUse;
private:
public:
	CUseItem();
	CUseItem(vector2 _pt);
	~CUseItem();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	bool getisUse() { return isUse; }
	void setPlayer(CPlayer* _player) { player = _player; }
};
class CUseBomb : public CUseItem
{
private:
	int count;
public:
	CUseBomb();
	CUseBomb(vector2 _pt);
	~CUseBomb();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


};