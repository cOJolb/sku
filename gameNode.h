#pragma once
#include"image.h"
#include"imageList.h"
static image* _backBuffer = IMAGE->addImage("backBuffer", WINSIZEX, WINSIZEY);
static image* _CVOSBuffer = IMAGE->addImage("CVOSBuffer", WINSIZEX * 3, WINSIZEY * 3);
class gameNode
{

private:

	//image* _backBuffer;	//백버퍼
	//void setBackBuffer();//백버퍼 셋팅

	C_imageList* imageList;

	HDC _hdc;
	bool  _managerInit;
	RECT rt;
public:
	gameNode();
	virtual~gameNode();

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);
	virtual void render(HDC hdc);


	image* getBackBuffer()const { return _backBuffer; }
	image* getCVOSBuffer()const { return _CVOSBuffer; }
	HDC getHDC()const { return _hdc; }
	HDC getMemDC()const { return _backBuffer->getMemDC(); }
	HDC getCVOSDC()const { return _CVOSBuffer->getMemDC(); }
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	RECT getClRect() { return rt; }
};

