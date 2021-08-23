#include "framework.h"
#include "CPlayerUI.h"
#include "CPlayer.h"
CPlayerUI::CPlayerUI()
{
}

CPlayerUI::~CPlayerUI()
{
}

HRESULT CPlayerUI::init()
{
	return S_OK;
}

void CPlayerUI::release()
{
}

void CPlayerUI::update()
{
}

void CPlayerUI::render()
{
}

void CPlayerUI::render(CPlayer* _player)
{
	/*TCHAR bomb[128];
	TCHAR key[128];
	TCHAR coin[128];*/
	for (int i = 0; i < _player->getMaxHp() / 2; i++)
	{
		IMAGE->frameRender("hpUI", getMemDC(), i * 33 + 110, 60, 2, 0);
	}
	for (int i = 0; i < _player->gethp() / 2; i++)
	{
		IMAGE->frameRender("hpUI", getMemDC(), i * 33 + 110, 60, 0, 0);
	}
	if (_player->gethp() % 2 == 1)
	{
		IMAGE->frameRender("hpUI", getMemDC(), _player->gethp() / 2 * 33 + 110, 60, 1, 0);
	}
	for (int i = 0; i < 3; i++)
	{
		IMAGE->frameRender("basicitemUI", getMemDC(), 30, 110 + i * 23, i, 0);
	}
	int coinTen = _player->getCoin() / 10;
	int coinOne = _player->getCoin() % 10;
	int bombTen = _player->getBomb() / 10;
	int bombOne = _player->getBomb() % 10;
	int keyTen = _player->getKey() / 10;
	int keyOne = _player->getKey() % 10;

	IMAGE->frameRender("number", getMemDC(), 80, 95 + 1 * 23, coinTen, 0);
	IMAGE->frameRender("number",getMemDC(),94, 95 + 1 * 23, coinOne, 0);
	
	IMAGE->frameRender("number", getMemDC(), 80, 95 + 2 * 23, keyTen, 0);
	IMAGE->frameRender("number", getMemDC(), 94, 95 + 2 * 23, keyOne, 0);
	
	IMAGE->frameRender("number", getMemDC(), 80, 95 + 3 * 23, bombTen, 0);
	IMAGE->frameRender("number", getMemDC(), 94, 95 + 3 * 23, bombOne, 0);

	//wsprintf(coin, TEXT("%d"), _player->getCoin());
	//TextOut(getMemDC(), 80, 100 + 1 * 23, coin, strlen(coin));
	//wsprintf(bomb, TEXT("%d"), _player->getBomb());
	//TextOut(getMemDC(), 80, 100 + 2 * 23, bomb, strlen(bomb));
	//wsprintf(key, TEXT("%d"), _player->getkey());
	//TextOut(getMemDC(), 80, 100 + 3 * 23, key, strlen(key));
}
