#include "framework.h"
#include "itemManager.h"
#include "item.h"
#include "skulItem.h"
#include "goodsItem.h"
#include "passiveItem.h"
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
    default:
        break;
    }
    vItem.push_back(item);
}

void itemManager::respawnSkulItem(SKULITEM _type, vector2 _pt)
{
    C_skulItem* item;
    switch (_type)
    {
    case SKULITEM::SKUL:
        item = new C_crownskul(_pt);
        break;
    case SKULITEM::CROWN:
        item = new C_crownskul(_pt);
        break;
    default:
        return;
        break;
    }
    vItem.push_back(item);
}

void itemManager::respawnActiveItem(ACTIVEITEM _type, vector2 _pt)
{
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

void itemManager::eraseAllItem()
{
    vItem.clear();
}
