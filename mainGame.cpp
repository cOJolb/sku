#include"framework.h"
#include "CMainMenu.h"
#include "CGameScene.h"
#include "CMapTool.h"
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
	SCENE->addScene("mainMenu", new CMainMenu);
	SCENE->addScene("game", new CGameScene);
	SCENE->addScene("mapTool", new CMapTool);
	SCENE->changeScene("mainMenu");
	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
}

void mainGame::update()
{
	gameNode::update();
}

void mainGame::render(/*HDC hdc*/)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================
	gameNode::render();
	//==============================================
	//백버퍼의 내용을 HDC그린다.(건드리지 말것.)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

