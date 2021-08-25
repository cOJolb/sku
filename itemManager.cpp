#include "framework.h"
#include "itemManager.h"
#include "item.h"
#include "skulItem.h"
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

void itemManager::update()
{
	//viItem = vItem.begin();
	//for (viItem; viItem < vItem.end(); ++viItem)
	//{
	//	(*viItem)->update();
	//}
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

viitem itemManager::getviItem(int number)
{
    viItem = vItem.begin() + number;
    return viItem;
}

void itemManager::itemRemove(int number)
{
    vItem.erase(vItem.begin() + number);
}

void itemManager::eraseAllItem()
{
    vItem.clear();
}
