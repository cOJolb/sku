#include"framework.h"
#include "mainGame.h"
mainGame::mainGame()
{
	mapSetting = new C_mapSetting;
	collision = new C_collision;
}
mainGame::~mainGame()
{
}
HRESULT mainGame::init()
{
	gameNode::init(true);
	
	player = new changePlayer;
	//for (float i = 0; i < 60; i++)
	//{
	//	OBSTACLE->createObstacle(OBSTACLE_TYPE::LTC_LAND, { 18*i,500 });
	//}
	//OBSTACLE->createObstacle(OBSTACLE_TYPE::LTC_LAND, { 400,464 });
	//OBSTACLE->createObstacle(OBSTACLE_TYPE::LTC_LAND, { 400,364 });
	//OBSTACLE->createObstacle(OBSTACLE_TYPE::LTC_LAND, { 400,264 });
	for (int i = 300; i < 320; i++)
	{
		mapSetting->tileSet(i, OBSTACLE_TYPE::LTC_LAND);
	}
	mapSetting->tileSet(100, OBSTACLE_TYPE::LTC_LAND);
	mapSetting->tileSet(150, OBSTACLE_TYPE::LTC_LAND);
	mapSetting->tileSet(170, OBSTACLE_TYPE::LTC_LAND);
	mapSetting->tileSet(220, OBSTACLE_TYPE::LTC_LAND);
	mapSetting->init();
	ENEMY->respawnEnemy(UNIT_TYPE::KNIGHT, { 500,200 });
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
	
	if (InputManager->isOnceKeyDown(VK_SPACE))
	{
		player->changeSkul();
	}
	player->update();

	ENEMY->update();
	collision->stageCollision();
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
	ENEMY->render();
	//SCENE->render();
	//EFFECT->render();
	//==============================================
	TIME->render(getMemDC());


	//백버퍼의 내용을 HDC그린다.(건드리지 말것.)
	this->getBackBuffer()->render(getHDC(), 0, 0);


}

