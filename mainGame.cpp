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
	player = new C_player;
	for (float i = 0; i < 60; i++)
	{
		OBSTACLE->createObstacle(OBSTACLE_TYPE::LTC_LAND, { 18*i,500 });
	}
	OBSTACLE->createObstacle(OBSTACLE_TYPE::LTC_LAND, { 400,464 });
	OBSTACLE->createObstacle(OBSTACLE_TYPE::LTC_LAND, { 400,364 });
	OBSTACLE->createObstacle(OBSTACLE_TYPE::LTC_LAND, { 400,264 });
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
	player->update();
	//SCENE->update();
	//ANIMATION->update();
	//EFFECT->update();

}

void mainGame::render(/*HDC hdc*/)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================
	//IMAGE->render("배경화면", getMemDC());
	gameNode::render();
	player->render();

	//SCENE->render();
	//EFFECT->render();
	//==============================================
	TIME->render(getMemDC());


	//백버퍼의 내용을 HDC그린다.(건드리지 말것.)
	this->getBackBuffer()->render(getHDC(), 0, 0);


}

