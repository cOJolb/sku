#include "framework.h"
#include "testScene.h"

testScene::testScene()
{
	mapSetting = new C_mapSetting;
	collision = new C_collision;
	player = new C_player;
	miniMap = new C_miniMap;
	IMAGE->addImage("CVOSDC", WINSIZEX * 3, WINSIZEY * 3);
}

testScene::~testScene()
{
}

HRESULT testScene::init()
{
	//player = new changePlayer;
//for (float i = 0; i < 60; i++)
//{
//	OBSTACLE->createObstacle(OBSTACLE_TYPE::LTC_LAND, { 18*i,500 });
//}
//OBSTACLE->createObstacle(OBSTACLE_TYPE::LTC_LAND, { 400,464 });
//OBSTACLE->createObstacle(OBSTACLE_TYPE::LTC_LAND, { 400,364 });
//OBSTACLE->createObstacle(OBSTACLE_TYPE::LTC_LAND, { 400,264 });
	mapSetting->init();
	for (int i = 0; i < 1; i++)
	{
		ENEMY->respawnEnemy(UNIT_TYPE::KNIGHT, { 400,200 });
	}
	/*ITEM->respawnGoodsItem(GOODSITEM::GOLD, { 300,300 });
	ITEM->respawnPassiveItem(PASSIVEITEM::CRISTAL, { 300,400 });
	ITEM->respawnPassiveItem(PASSIVEITEM::CRISTAL, { 350,400 });
	ITEM->respawnPassiveItem(PASSIVEITEM::CRISTAL, { 400,400 });
	ITEM->respawnPassiveItem(PASSIVEITEM::MEDAL, { 400,450 });
	ITEM->respawnSkulItem(SKUL_TYPE::SKUL, { 300, 450 });
	ITEM->respawnSkulItem(SKUL_TYPE::CLOWN, { 350, 450 });*/
	player->init();
	CAMERA->init(player->getPt().x, player->getPt().y, 30 * 36, 20 * 36, 0, 0, 30 * 36 / 4, 20 * 36 / 4, 30 * 36 / 2, 20 * 36 / 2);
	for (int i = 0; i < 30 * 20; i++)
	{
		miniMap->init(mapSetting->getTile(i));
	}
	SUBWIN->init();
	SCENE->setSCENETYPE(SCENE_TYPE::PLAY);
	//SUBWIN->SetScene(new CMapSettingSub);
	return S_OK;
}

void testScene::release()
{
}

void testScene::update()
{
	/*if (InputManager->isOnceKeyDown(VK_SPACE))
{
	player->changeSkul();
}*/
	if (InputManager->isOnceKeyDown('U'))
	{
		ITEM->respawnPassiveItem(PASSIVEITEM::MEDAL, { 400,450 });
	}
	if (InputManager->isOnceKeyDown('O'))
	{
		ITEM->respawnPassiveItem(PASSIVEITEM::CRISTAL, { 400,450 });
	}
	if (InputManager->isOnceKeyDown(VK_TAB))
	{
		SCENE->changeScene("item");
	}
	player->update();
	CAMERA->movePivot(player->getPt().x, player->getPt().y);
	CAMERA->update();
	ENEMY->update();
	collision->stageCollision(player);
	//SUBWIN->update();
	//SCENE->setRenderRect(checkGameSize());
	//SCENE->update();
	//ANIMATION->update();
	//EFFECT->update();
}

void testScene::render()
{
	player->render();
	OBSTACLE->render();
	ENEMY->render();
	ITEM->render();
	RECT recCamera = RectMake(200, 200, 1000, 1000);
	_CVOSBuffer->render(IMAGE->findImage("CVOSDC")->getMemDC(), 0, 0, CAMERA->getRect().left, CAMERA->getRect().top,
		RectWidth(CAMERA->getRect()), RectHeight(CAMERA->getRect()));
	IMAGE->findImage("CVOSDC")->stretchRenderXY(getMemDC(), 0, 0, 2);
	miniMap->render();
	//SCENE->render();
	//EFFECT->render();
	//SUBWIN->render();

}

RECT testScene::checkGameSize()
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

