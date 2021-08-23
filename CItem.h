#pragma once
#include "CObject.h"
class CItem : public CObject
{
protected:
	ITEM_TYPE type;
private:
public:
	CItem();
	~CItem();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	ITEM_TYPE getItemType() { return type; }
};
class CHeart : public CItem
{
private:
public:
	CHeart();
	CHeart(vector2 _pt);
	~CHeart();

	virtual HRESULT init();
	virtual void release();
	//virtual void update();
	virtual void render();
};
class CCoin : public CItem
{
private:
public:
	CCoin();
	CCoin(vector2 _pt);
	~CCoin();

	virtual HRESULT init();
	virtual void release();
	//virtual void update();
	virtual void render();
};

class CBomb : public CItem
{
private:

public:
	CBomb();
	CBomb(vector2 _pt);
	~CBomb();

	virtual HRESULT init();
	virtual void release();
	//virtual void update();
	virtual void render();
};

class CKey : public CItem
{
private:
public:
	CKey();
	CKey(vector2 _pt);
	~CKey();

	virtual HRESULT init();
	virtual void release();
	//virtual void update();
	virtual void render();
};

class CInnerEye : public CItem
{
private:
public:
	CInnerEye();
	CInnerEye(vector2 _pt);
	~CInnerEye();

	virtual HRESULT init();
	virtual void release();
	//virtual void update();
	virtual void render();
};

class CLipstick : public CItem
{
private:
public:
	CLipstick();
	CLipstick(vector2 _pt);
	~CLipstick();

	virtual HRESULT init();
	virtual void release();
	//virtual void update();
	virtual void render();
};

class CPentagram : public CItem
{
private:
public:
	CPentagram();
	CPentagram(vector2 _pt);
	~CPentagram();


	virtual HRESULT init();
	virtual void release();
	//virtual void update();
	virtual void render();
};

class CBloodbag : public CItem
{
private:
public:
	CBloodbag();
	CBloodbag(vector2 _pt);
	~CBloodbag();

	virtual HRESULT init();
	virtual void release();
	//virtual void update();
	virtual void render();
};

class CSpeedBall : public CItem
{
private:
public:
	CSpeedBall();
	CSpeedBall(vector2 _pt);
	~CSpeedBall();

	virtual HRESULT init();
	virtual void release();
	//virtual void update();
	virtual void render();
};