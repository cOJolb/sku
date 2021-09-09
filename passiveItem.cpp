#include "framework.h"
#include "passiveItem.h"
#include "player.h"


C_DimLightDarkcite::C_DimLightDarkcite(vector2 _pt)
{
	pt = _pt;
	collider = new C_collider(pt, { 30,30 });
	itemType = ITEM_TYPE::PASSIVE;
	passiveType = PASSIVEITEM::CRISTAL;
}

HRESULT C_DimLightDarkcite::init(C_player* _player)
{
	S_skulInfo changeInfo;
	changeInfo = _player->getPlayerInfo();
	//stats = changeInfo.playerSpeed / 10;
	stats = 1;
	changeInfo.playerSpeed += stats;
	_player->setPlayerInfo(changeInfo);
	return S_OK;
}

void C_DimLightDarkcite::release(C_player* _player)
{
	S_skulInfo changeInfo;
	changeInfo = _player->getPlayerInfo();
	changeInfo.playerSpeed -= stats;
	_player->setPlayerInfo(changeInfo);
}

void C_DimLightDarkcite::render()
{
	IMAGE->findImage("DimLightDarkcite")->renderCenter(getCVOSDC(), pt);
}

void C_DimLightDarkcite::render(vector2 _pt)
{
	IMAGE->findImage("DimLightDarkcite")->renderCenter(getMemDC(), _pt);
}


C_MedalOfCarleon::C_MedalOfCarleon(vector2 _pt)
{
	pt = _pt;
	collider = new C_collider(pt, { 30,30 });
	itemType = ITEM_TYPE::PASSIVE;
	passiveType = PASSIVEITEM::MEDAL;
}

HRESULT C_MedalOfCarleon::init(C_player* _player)
{
	_player->sethp(_player->gethp() + 20);
	if(_player->gethp() >= _player->getmaxHp()) { _player->sethp(_player->getmaxHp()); }
	return S_OK;
}

void C_MedalOfCarleon::release(C_player* _player)
{
}

void C_MedalOfCarleon::update(C_player* _player)
{
}

void C_MedalOfCarleon::render()
{
	IMAGE->findImage("MedalOfCarleon")->renderCenter(getCVOSDC(), pt);
}

void C_MedalOfCarleon::render(vector2 _pt)
{
	IMAGE->findImage("MedalOfCarleon")->renderCenter(getMemDC(), _pt);
}

C_BasicCaerleonSword::C_BasicCaerleonSword(vector2 _pt)
{
	pt = _pt;
	collider = new C_collider(pt, { 30,30 });
	itemType = ITEM_TYPE::PASSIVE;
	passiveType = PASSIVEITEM::SWORD;
}

HRESULT C_BasicCaerleonSword::init(C_player* _player)
{
	S_skulInfo changeInfo;
	changeInfo = _player->getPlayerInfo();
	//stats = changeInfo.playerSpeed / 10;
	stats = 5;
	changeInfo.playerDamage += stats;
	_player->setPlayerInfo(changeInfo);
	return S_OK;
}

void C_BasicCaerleonSword::release(C_player* _player)
{
	S_skulInfo changeInfo;
	changeInfo = _player->getPlayerInfo();
	changeInfo.playerDamage -= stats;
	_player->setPlayerInfo(changeInfo);
}

void C_BasicCaerleonSword::render()
{
	IMAGE->findImage("BasicCaerleonSword")->renderCenter(getCVOSDC(), pt);
}

void C_BasicCaerleonSword::render(vector2 _pt)
{
	IMAGE->findImage("BasicCaerleonSword")->renderCenter(getMemDC(), _pt);
}
