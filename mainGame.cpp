#include"framework.h"
#include "mainGame.h"
mainGame::mainGame()
{
}
mainGame::~mainGame()
{
}
HRESULT mainGame::init()
{
	gameNode::init(true);



	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
	//SCENE->release();

}

void mainGame::update()
{

	gameNode::update();
	//SCENE->update();
	//ANIMATION->update();
	//EFFECT->update();

}

void mainGame::render(/*HDC hdc*/)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================
	//IMAGE->render("���ȭ��", getMemDC());
	RECT rc = RectMakeCenter(500, 500, 200, 200);
	Rectangle(getMemDC(),rc.left,rc.top,rc.right,rc.bottom );
	//SCENE->render();
	//EFFECT->render();
	//==============================================
	TIME->render(getMemDC());


	//������� ������ HDC�׸���.(�ǵ帮�� ����.)
	this->getBackBuffer()->render(getHDC(), 0, 0);


}

