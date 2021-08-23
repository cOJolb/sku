#include "framework.h"
#include "UIManager.h"
#include "CUI.h"
#include "CPlayerUI.h"
#include "CMinimap.h"
#include "CPlayer.h"
#include "CMap.h"
#include "CBossUI.h"
UIManager::UIManager()
{
	playerUI = new CPlayerUI;
	minimap = new CMinimap;
	bossUI = new CBossUI;
	isRespawnBoss = 0;
}

UIManager::~UIManager()
{

}

HRESULT UIManager::init()
{
	playerUI->init();
	minimap->init();
	minimap->setRND(randomMap);
	minimap->mapAttrSetting();
	bossUI->init();
	return S_OK;
}

void UIManager::release()
{
	playerUI->release();
	minimap->release();
	bossUI->init();
}

void UIManager::update()
{
	playerUI->update();
	minimap->update();
	if (isRespawnBoss) { bossUI->update(); }
}

void UIManager::render()
{
	playerUI->render(player);
	minimap->render();
	if (isRespawnBoss) { bossUI->render(); }
}

void UIManager::setboss(CGurdy* _boss)
{
	bossUI->setBoss(_boss);
}
