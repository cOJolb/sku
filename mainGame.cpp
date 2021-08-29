#include"framework.h"
#include "mainGame.h"
mainGame::mainGame()
{
	mapSetting = new C_mapSetting;
	collision = new C_collision;
	player = new C_player;
	miniMap = new C_miniMap;
	IMAGE->addImage("CVOSDC", WINSIZEX*3, WINSIZEY*3);
}
mainGame::~mainGame()
{
}
HRESULT mainGame::init()
{
	gameNode::init(true);
	
	
	//player = new changePlayer;
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
	ENEMY->respawnEnemy(UNIT_TYPE::KNIGHT, { 550,200 });
	ENEMY->respawnEnemy(UNIT_TYPE::KNIGHT, { 450,200 });
	ENEMY->respawnEnemy(UNIT_TYPE::KNIGHT, { 340,200 });
	ENEMY->respawnEnemy(UNIT_TYPE::KNIGHT, { 400,200 });
	player->init();
	CAMERA->init(player->getPt().x, player->getPt().y, 30 * 36, 20 * 36, 0, 0, 30 * 36 / 4, 20 * 36 / 4, 30 * 36 / 2, 20 * 36 / 2);
	for (int i = 0; i < 30*20; i++)
	{
		miniMap->init(mapSetting->getTile(i));
	}
	
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
	
	/*if (InputManager->isOnceKeyDown(VK_SPACE))
	{
		player->changeSkul();
	}*/
	player->update();
	CAMERA->movePivot(player->getPt().x, player->getPt().y);
	CAMERA->update();
	ENEMY->update();
	collision->stageCollision();
	//SCENE->update();
	//ANIMATION->update();
	//EFFECT->update();

}

void mainGame::render(/*HDC hdc*/)
{
	PatBlt(_CVOSBuffer->getMemDC(), 0, 0, _CVOSBuffer->getWidth() , _CVOSBuffer->getHeight(), WHITENESS);
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================
	//IMAGE->render("배경화면", getMemDC());

	gameNode::render();
	player->render();
	ENEMY->render();
	RECT recCamera = RectMake(200,200, 1000,1000 );
	_CVOSBuffer->render(IMAGE->findImage("CVOSDC")->getMemDC(), 0, 0, CAMERA->getRect().left, CAMERA->getRect().top,
		RectWidth(CAMERA->getRect()), RectHeight(CAMERA->getRect()));
	IMAGE->findImage("CVOSDC")->stretchRenderXY(getMemDC(),0,0,2);
	miniMap->render();
	//SCENE->render();
	//EFFECT->render();
	

	//==============================================
	TIME->render(getMemDC());


	//백버퍼의 내용을 HDC그린다.(건드리지 말것.)
	RECT gameSize = checkGameSize();
	this->getBackBuffer()->stretchRender(getHDC(), RectX(gameSize), RectY(gameSize), RectWidth(gameSize), RectHeight(gameSize));


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

