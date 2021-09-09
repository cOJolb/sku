#include "framework.h"
#include "stage.h"

C_stage::C_stage()
{
	//mapSetting = new C_mapSetting;
	//collision = new C_collision;
	//miniMap = new C_miniMap;
	//player = nullptr;

	IMAGE->addImage("CVOSDC", WINSIZEX * 3, WINSIZEY * 3);
	IMAGE->addImage("backGroundDC", WINSIZEX * 3, WINSIZEY * 3);


}

C_stage::~C_stage()
{
}

HRESULT C_stage::init(int number)
{
	mapSetting = new C_mapSetting(number);
	collision = new C_collision;
	miniMap = new C_miniMap;

	mapSetting->init();
	player = PLAYERDATA->getPlayerData();
	player->init();
	for (int i = 0; i < OBSTACLE->getvObstacle().size(); i++)
	{
		if ((*OBSTACLE->getviObstacle(i))->getStart())
		{
			vector2 startPt = (*OBSTACLE->getviObstacle(i))->getPt();
			startPt.y -= player->getCollider()->getSize().y / 2;
			player->setPt(startPt);
		}
	}
	CAMERA->init(0, 0, tileX * tileSize, tileY * tileSize, 0, 0, tileX * tileSize / 4, tileY * tileSize / 4, tileX * tileSize / 2, tileY * tileSize / 2);
	for (int i = 0; i < tileX * tileY; i++)
	{
		miniMap->init(mapSetting->getTile(i));
	}
	SCENE->setSCENETYPE(SCENE_TYPE::PLAY);
	

	//ENEMY->respawnEnemy(UNIT_TYPE::BIGKNIGHT, { player->getPt().x +250,player->getPt().y -100 });
	//ITEM->respawnSkulItem(SKUL_TYPE::WARRIOR, player->getPt());
	//ITEM->respawnSkulItem(SKUL_TYPE::CLOWN, { player->getPt().x + 50, player->getPt().y });

	return S_OK;
}

void C_stage::release()
{
}

void C_stage::update()
{
	if (InputManager->isOnceKeyDown('P')) { ITEM->respawnSkulItem(SKUL_TYPE::WARRIOR, player->getPt()); }
	if (InputManager->isOnceKeyDown('O')) { ITEM->respawnSkulItem(SKUL_TYPE::CLOWN, player->getPt()); }
	if (InputManager->isOnceKeyDown('I')) { ITEM->respawnPassiveItem(PASSIVEITEM::CRISTAL, player->getPt()); }
	if (InputManager->isOnceKeyDown('U')) { ITEM->respawnPassiveItem(PASSIVEITEM::MEDAL, player->getPt()); }
	if (InputManager->isOnceKeyDown('Y')) { ITEM->respawnPassiveItem(PASSIVEITEM::SWORD, player->getPt()); }
	if (InputManager->isOnceKeyDown('L')) { ENEMY->respawnEnemy(UNIT_TYPE(UNIT_TYPE::KNIGHT), { 500, 200}); }
	if (InputManager->isOnceKeyDown(VK_TAB))
	{
		SCENE->changeScene("item");
	}
	BULLET->update();
	player->update();
	ITEM->update(player);
	EFFECT->update();
	CAMERA->movePivot(PLAYERDATA->getPlayerData()->getPt().x, PLAYERDATA->getPlayerData()->getPt().y);
	CAMERA->update();
	ENEMY->update();
	collision->stageCollision(player);

	PLAYERDATA->setPlayerData(player);
	if (player->gethp() <= 0)
	{
		SCENE->changeScene("end");
	}
	if (ENEMY->getvEnemy().size() <= 0 && !isFinish)
	{
		ITEM->respawnRandom(player->getPt());
		isFinish = true;
	}
	
}

void C_stage::render()
{
	
	OBSTACLE->render();
	ENEMY->render();
	player->render();
	BULLET->render();
	EFFECT->render();
	ITEM->render();
	_CVOSBuffer->render(IMAGE->findImage("CVOSDC")->getMemDC(), 0, 0, CAMERA->getRect().left, CAMERA->getRect().top,
		RectWidth(CAMERA->getRect()), RectHeight(CAMERA->getRect()));
	IMAGE->findImage("CVOSDC")->stretchRenderXY(getMemDC(), 0, 0, 2);
	if (InputManager->isToggleKey(VK_SHIFT))
	{
		miniMap->render();
	}
	PLAYERUI->render(getMemDC());
}

RECT C_stage::checkGameSize()
{
	RECT rc = this->getClRect();
	float wid = rc.right;
	float hei = rc.bottom;
	float widOverHei = (float)(tileX * tileSize) / (tileY * tileSize);
	float heiOverWid = (float)(tileY * tileSize) / (tileX * tileSize);

	float w, h;
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
	return { left, top, right, bottom };
}

void C_stage::curRelease()
{
	OBSTACLE->eraserAllObstacle();
	ITEM->eraseAllItem();
	SAFE_DELETE(collision);
	SAFE_DELETE(miniMap);
	SAFE_DELETE(mapSetting);
}

bool C_stage::isNextStage()
{
	return player->getNextLevel();
}
