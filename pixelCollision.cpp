#include "framework.h"
#include "pixelCollision.h"

pixelCollision::pixelCollision()
{
}

pixelCollision::~pixelCollision()
{
}

HRESULT pixelCollision::init()
{

	IMAGE->addImage("배경화면", "images/사나.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("산", "images/mountain1.bmp", WINSIZEX,WINSIZEY, true, RGB(255, 0, 255));

	_ball = IMAGE->addImage("ball", "images/ball.bmp", 60, 60,true, RGB(255, 0, 255));

	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2 + 100;

	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());
	
	_probeY = _y + _ball->getHeight() / 2;


	return S_OK;
}

void pixelCollision::release()
{
}

void pixelCollision::update()
{
	if (InputManager->isStayKeyDown(VK_LEFT))_x -= 2.0f;
	if (InputManager->isStayKeyDown(VK_RIGHT))_x += 2.0f;
	_probeY = _y + _ball->getHeight() / 2;

	for (int i = _probeY-10; i < _probeY+10; i++)
	{	
		COLORREF  color = GetPixel(IMAGE->findImage("산")->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - _ball->getHeight() / 2;
			break;
		}
	}
	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());
}

void pixelCollision::render()
{
	IMAGE->findImage("배경화면")->render(getMemDC());
	IMAGE->findImage("산")->render(getMemDC());
	_ball->render(getMemDC(), _rc.left, _rc.top);

}
