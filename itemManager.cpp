#include "framework.h"
#include "itemManager.h"
#include "item.h"
#include "skulItem.h"
#include "goodsItem.h"
#include "passiveItem.h"
#include "activeItem.h"
itemManager::itemManager()
{
}

itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{
	return S_OK;
}

void itemManager::release()
{
}

void itemManager::update(C_player* _player)
{
	viEquipItem = vEquipItem.begin();
	for (viEquipItem; viEquipItem < vEquipItem.end(); ++viEquipItem)
	{
		(*viEquipItem)->update(_player);
	}
    viItem = vItem.begin();
    for (viItem; viItem < vItem.end(); ++viItem)
    {
        (*viItem)->update(_player);
    }
}

void itemManager::render()
{
	viItem = vItem.begin();
	for (viItem; viItem < vItem.end(); ++viItem)
	{
		(*viItem)->render();
	}
}

void itemManager::respawnPassiveItem(PASSIVEITEM _type, vector2 _pt)
{
    C_item* item;
    switch (_type)
    {
    case PASSIVEITEM::CRISTAL:
        item = new C_DimLightDarkcite(_pt);
        break;
    case PASSIVEITEM::MEDAL:
        item = new C_MedalOfCarleon(_pt);
        break;
    case PASSIVEITEM::SWORD:
        item = new C_BasicCaerleonSword(_pt);
        break;
    default:
        break;
    }
    vItem.push_back(item);
}

void itemManager::respawnSkulItem(SKUL_TYPE _type, vector2 _pt)
{
    C_item* item;
    switch (_type)
    {
    case SKUL_TYPE::SKUL:
        item = new C_littleBoneskul(_pt);
        break;
    case SKUL_TYPE::CLOWN:
        item = new C_crownskul(_pt);
        break;
    case SKUL_TYPE::WARRIOR:
        item = new C_warriorskul(_pt);
        break;
    default:
        return;
        break;
    }
    vItem.push_back(item);
}

void itemManager::respawnActiveItem(ACTIVEITEM _type, vector2 _pt)
{
    C_item* item;
    switch (_type)
    {
    case ACTIVEITEM::LITTLEBONEHEAD:
        item = new C_littleBoneHead(_pt);
        break;
   
    default:
        break;
    }
    vItem.push_back(item);
}

void itemManager::respawnGoodsItem(GOODSITEM _type, vector2 _pt)
{
    C_item* item;
    switch (_type)
    {
    case GOODSITEM::GOLD:
        item = new C_Gold(_pt);
        break;
    default:
        break;
    }
    vItem.push_back(item);
}

void itemManager::respawnRandom(vector2 _pt)
{
    C_item* item;
    int random = RND->getFromIntTo(0, 4);
    switch (random)
    {
    case 0:
        item = new C_crownskul(_pt);
        break;
    case 1:
        item = new C_warriorskul(_pt);
        break;
    case 2:
        item = new C_BasicCaerleonSword(_pt);
        break;
    case 3:
        item = new C_MedalOfCarleon(_pt);
        break;
    case 4:
        item = new C_DimLightDarkcite(_pt);
        break;
    default:
        break;
    }
    vItem.push_back(item);
}

void itemManager::EquipPassiveItem(C_item* _passiveItem)
{
    vEquipItem.push_back(_passiveItem);
}

viitem itemManager::getviItem(int number)
{
    viItem = vItem.begin() + number;
    return viItem;
}

viitem itemManager::getviEquipItem(int number)
{
    viEquipItem = vEquipItem.begin() + number;
    return viEquipItem;
}

void itemManager::Equip(C_player* _player)
{
    viEquipItem = vEquipItem.begin();
    for (viEquipItem; viEquipItem < vEquipItem.end(); ++viEquipItem)
    {
        (*viEquipItem)->init(_player);
    }
}

void itemManager::itemRemove(int number)
{
    vItem.erase(vItem.begin() + number);
}

void itemManager::EquipRemove(int number)
{
    viEquipItem = vEquipItem.begin() + number;
    (*viEquipItem)->release(PLAYERDATA->getPlayerData());
    vEquipItem.erase(vEquipItem.begin() + number);
}

void itemManager::eraseAllItem()
{
    vItem.clear();
}
