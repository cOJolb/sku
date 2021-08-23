#include "framework.h"
#include "CStage.h"
#include "CPlayer.h"
#include "CGameScene.h"

CGameScene::CGameScene() :
	isPause(false),
	isPlayerDead(false),
	selectMenu(0),
	isKeyDown(0), 
	frameCnt(0)
{
}

CGameScene::~CGameScene()
{
}

HRESULT CGameScene::init()
{
	ENEMY->init();
	ITEM->init();
	MAP->init();
	STAGE->init();
	ALLUI->init();

	isPause = false;
	isPlayerDead = false;
	selectMenu = 0;
	isKeyDown = 0;
	frameCnt = 0;
    return S_OK;
}

void CGameScene::release()
{
	SOUND->stop("bgm");
	STAGE->release();
	MAP->release();
	BULLET->release();
	ENEMY->release();
	ALLUI->release();
}

void CGameScene::update()
{
	if (STAGE->getCurStage()->getPlayer()->getstate() == STATE_TYPE::DEAD && !isPlayerDead)
		isPlayerDead = true;

	if (isPlayerDead && frameCnt < 30) 
		frameCnt++;
	else if (isPlayerDead && frameCnt >= 30)
	{
		if (InputManager->isOnceKeyDown(VK_SPACE))
		{
			if (SOUND->isPlaySound("bossfight"))
				SOUND->stop("bossfight");
			SOUND->stop("playerdiebgm");
			init();
		}
	}


	if (InputManager->isOnceKeyDown('P'))
	{
		isPause = true;
	}

	if (isPause)
	{
		if (InputManager->isOnceKeyDown(VK_UP))
		{
			if (selectMenu > 0)
				selectMenu--;
		}
		if (InputManager->isOnceKeyDown(VK_DOWN))
		{
			if (selectMenu < 1)
				selectMenu++;
		}
		if (InputManager->isOnceKeyDown(VK_SPACE))
			isKeyDown = true;
	}

	if (isKeyDown)
	{
		switch (selectMenu)
		{
		case 0:
			isPause = false;
			isKeyDown = false;
			break;
		case 1:
			SCENE->changeScene("mainMenu");
			break;
		}
	}

	if (!isPause)
	{
		ALLUI->update();
		STAGE->update();
		BULLET->update();
		ENEMY->update();
		ITEM->update();
	}
}

void CGameScene::render()
{
	STAGE->render();
	BULLET->render();
	ENEMY->render();
	ITEM->render();
	MAP->render();
	ALLUI->render();

	if (isPause)
	{
		IMAGE->alphaRender("black", getMemDC(), 220);
		IMAGE->render("pause_menu", getMemDC(), 180, 100);
		IMAGE->render("menu_arrow", getMemDC(), 325, 510 + selectMenu * 60);
	}

	if (frameCnt >= 30)
	{
		IMAGE->alphaRender("black", getMemDC(), 220);
		IMAGE->render("deathMenu", getMemDC(), 180, 100);
	}
}