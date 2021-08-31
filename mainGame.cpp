#include"framework.h"
#include "mainGame.h"
mainGame::mainGame()
{
	//IMAGE->addImage("CVOSDC", WINSIZEX*3, WINSIZEY*3);
}
mainGame::~mainGame()
{
}
HRESULT mainGame::init()
{
	gameNode::init(true);
	SCENE->addScene("test", new testScene);
	SCENE->addScene("create", new createScene);

	SCENE->changeScene("test");
	return S_OK;
}

void mainGame::release()	
{
	gameNode::release();
	SCENE->release();
}

void mainGame::update()
{

	gameNode::update();
	SCENE->update();
}

void mainGame::render(/*HDC hdc*/)
{
	PatBlt(_CVOSBuffer->getMemDC(), 0, 0, _CVOSBuffer->getWidth() , _CVOSBuffer->getHeight(), WHITENESS);
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	//==============================================
	SCENE->render();

	//==============================================
	TIME->render(getMemDC());


	//백버퍼의 내용을 HDC그린다.(건드리지 말것.)
	switch (SCENE->getSCENETYPE())
	{
	case SCENE_TYPE::CREATE:
		gameSize = RectMake(0,0,GameSizeX,GameSizeY);
		this->getBackBuffer()->stretchRender(getHDC(), RectX(gameSize), RectY(gameSize), RectWidth(gameSize), RectHeight(gameSize));
		break;
	case SCENE_TYPE::PLAY:
		gameSize = checkGameSize();
		this->getBackBuffer()->stretchRender(getHDC(), RectX(gameSize), RectY(gameSize), RectWidth(gameSize), RectHeight(gameSize));
		break;
	default:
		break;
	}

	
	

}

RECT mainGame::checkGameSize()
{
	RECT rc = this->getClRect();
	float wid = rc.right;
	float hei = rc.bottom;
	float widOverHei = (float)(30 * 36) / (20 * 36);
	float heiOverWid = (float)(20 * 36) / (30 * 36);

	float w, h;
	//현재 가로에 맞춘 세로가 현재 창의 세로보다 크다면, 현재 세로에 맞춘다.
	(wid * heiOverWid > hei) ? w = hei * widOverHei, h = hei
		: w = wid, h = w * heiOverWid;

	int left, top, right, bottom;
	if (w < wid) {
		left = wid / 2 - w / 2;
		right = left + w;
		top = 0;
		bottom = h;
	}
	else {
		left = 0;
		right = w;
		top = hei / 2 - h / 2;
		bottom = top + h;
	}
	//MoveWindow(gethwnd(), left, top, right, bottom, TRUE);    // listbox의 size를 change
	return { left, top, right, bottom };

}

