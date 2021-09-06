#include "framework.h"
#include "stage.h"

C_stage::C_stage()
{
	//mapSetting = new C_mapSetting;
	//collision = new C_collision;
	//miniMap = new C_miniMap;
	//player = nullptr;
	//BackSecond = new camera;
	IMAGE->addImage("CVOSDC", WINSIZEX * 3, WINSIZEY * 3);
	IMAGE->addImage("backGroundDC", WINSIZEX * 3, WINSIZEY * 3);
	Door = new image;
	DoorAni = new animation;

}

C_stage::~C_stage()
{
}

HRESULT C_stage::init()
{
	//Door->init("images/map/normalStage.bmp",1000,200,5,1,true,RGB(255,0,255));
	//IMAGE->addImage("MedalOfCarleon", "images/item/MedalOfCarleon1.bmp", 30, 30, true, RGB(255, 0, 255));

	//DoorAni->init(1000, 200, 5, 1);
	//DoorAni->start();

	mapSetting = new C_mapSetting;
	collision = new C_collision;
	miniMap = new C_miniMap;
	//player = nullptr;

	Door->init("images/map/normalStage.bmp", 1000, 200, 5, 1, true, RGB(255, 0, 255));
	DoorAni->init(1000, 200, 200, 200);
	DoorAni->setDefPlayFrame(false, true);
	DoorAni->setFPS(5);
	DoorAni->start();

	mapSetting->init();
	player = PLAYERDATA->getPlayerData();
	player->init();
	//PLAYERDATA->getPlayerData()->init();
	//CAMERA->init(player->getPt().x, player->getPt().y, tileX * tileSize, tileY * tileSize, 0, 0, tileX * tileSize / 4, tileY * tileSize / 4, tileX * tileSize / 2, tileY * tileSize / 2);
	CAMERA->init(0, 0, tileX * tileSize, tileY * tileSize, 0, 0, tileX * tileSize / 4, tileY * tileSize / 4, tileX * tileSize / 2, tileY * tileSize / 2);
	//BackSecond->init(player->getPt().x, player->getPt().y, GameSizeX, GameSizeY, 0, 0, GameSizeX, GameSizeY, GameSizeX, GameSizeY);
	for (int i = 0; i < tileX * tileY; i++)
	{
		miniMap->init(mapSetting->getTile(i));
	}
	SCENE->setSCENETYPE(SCENE_TYPE::PLAY);

	OBSTACLE->createObstacle(OBSTACLE_TYPE::ITEMDOOR, { 300, 635 });
	ITEM->respawnPassiveItem(PASSIVEITEM::MEDAL, { 200,635 });
	//ENEMY->respawnEnemy(UNIT_TYPE::KNIGHT, { 300,300 });
	ENEMY->respawnEnemy(UNIT_TYPE::KNIGHT, { 400,300 });
	ENEMY->respawnEnemy(UNIT_TYPE::KNIGHT, { 500,300 });
	//ENEMY->respawnEnemy(UNIT_TYPE::KNIGHT, { 500,300 });

	return S_OK;
}

void C_stage::release()
{
	//OBSTACLE->eraserAllObstacle();
	//SAFE_DELETE(collision);
	//SAFE_DELETE(miniMap);
	//SAFE_DELETE(mapSetting);
}

void C_stage::update()
{
	if (InputManager->isOnceKeyDown(VK_TAB))
	{
		SCENE->changeScene("item");
	}
	
	player->update();
	PLAYERDATA->setPlayerData(player);
	//PLAYERDATA->getPlayerData()->update();
	//CAMERA->movePivot(player->getPt().x, player->getPt().y);
	CAMERA->movePivot(PLAYERDATA->getPlayerData()->getPt().x, PLAYERDATA->getPlayerData()->getPt().y);
	CAMERA->update();
	/*BackSecond->movePivot(player->getPt().x, player->getPt().y);
	BackSecond->update();*/
	ENEMY->update();
	//collision->stageCollision(player);
	collision->stageCollision(player);
	//DoorAni->frameUpdate(100);
	DoorAni->frameUpdate(TIME->getElapsedTime() * 1.0f);
	//PLAYERDATA->setPlayerData(player);
}

void C_stage::render()
{
	IMAGE->findImage("BackGround")->render(getCVOSDC());

	//IMAGE->findImage("BackGround2")->render(getBG());
	//_backGroundBuffer->render(IMAGE->findImage("backGroundDC")->getMemDC(), 0, 0, BackSecond->getRect().left, BackSecond->getRect().top,
	//	RectWidth(BackSecond->getRect()), RectHeight(BackSecond->getRect()));
	//IMAGE->findImage("backGroundDC")->stretchRenderXY(getCVOSDC(), 0, 0, 1);

	Door->aniRender(getCVOSDC(), 400, 500, DoorAni);
	OBSTACLE->render();
	//Door->aniRenderMe(getCVOSDC(), 400, 600, DoorAni);
	//Door->render(getCVOSDC(), 400, 500);
	player->render();
	//PLAYERDATA->getPlayerData()->render();
	//OBSTACLE->render();
	ENEMY->render();
	ITEM->render();
	//RECT recCamera = RectMake(200, 200, 1000, 1000);
	_CVOSBuffer->render(IMAGE->findImage("CVOSDC")->getMemDC(), 0, 0, CAMERA->getRect().left, CAMERA->getRect().top,
		RectWidth(CAMERA->getRect()), RectHeight(CAMERA->getRect()));
	IMAGE->findImage("CVOSDC")->stretchRenderXY(getMemDC(), 0, 0, 2);
	miniMap->render();
}

RECT C_stage::checkGameSize()
{
	RECT rc = this->getClRect();
	float wid = rc.right;
	float hei = rc.bottom;
	float widOverHei = (float)(tileX * tileSize) / (tileY * tileSize);
	float heiOverWid = (float)(tileY * tileSize) / (tileX * tileSize);

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

void C_stage::curRelease()
{
	OBSTACLE->eraserAllObstacle();
	SAFE_DELETE(collision);
	SAFE_DELETE(miniMap);
	SAFE_DELETE(mapSetting);
}

bool C_stage::isNextStage()
{
	return player->getNextLevel();
}
