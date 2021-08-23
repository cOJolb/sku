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
	//IMAGE->render("배경화면", getMemDC());
	RECT rc = RectMakeCenter(500, 500, 200, 200);
	Rectangle(getMemDC(),rc.left,rc.top,rc.right,rc.bottom );
	//SCENE->render();
	//EFFECT->render();
	//==============================================
	TIME->render(getMemDC());


	//백버퍼의 내용을 HDC그린다.(건드리지 말것.)
	this->getBackBuffer()->render(getHDC(), 0, 0);


}

