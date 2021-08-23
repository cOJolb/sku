#include "framework.h"
#include "itemManager.h"
#include "CItem.h"
#include "UseItem.h"
#include "CPlayer.h"
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
    //iItem = item.begin();
    //for (iItem; iItem < item.end(); ++iItem)
    //{
    //    (*iItem)->update();
    //}
    viuseItem = useItem.begin();
    for (viuseItem; viuseItem < useItem.end(); ++viuseItem)
    {
        (*viuseItem)->update();
    }
    bombFire();
}

void itemManager::render()
{
    iItem = item.begin();
    for (iItem; iItem < item.end(); ++iItem)
    {
        (*iItem)->render();
    }
    viuseItem = useItem.begin();
    for (viuseItem; viuseItem < useItem.end(); ++viuseItem)
    {
        (*viuseItem)->render();
    }
}

void itemManager::respawnItem(ITEM_TYPE type, vector2 pos)
{
    CItem* _item;
    switch (type)
    {
    case ITEM_TYPE::ITEM_HEART:
        _item = new CHeart(pos);
        break;
    case ITEM_TYPE::ITEM_COIN:
        _item = new CCoin(pos);
        break;
    case ITEM_TYPE::ITEM_BOMB:
        _item = new CBomb(pos);
        break;
    case ITEM_TYPE::ITEM_KEY:
        _item = new CKey(pos);
        break;
    case ITEM_TYPE::ITEM_THEINNEREYE:
        _item = new CInnerEye(pos);
        break;
    case ITEM_TYPE::ITEM_BLOODBAG:
        _item = new CBloodbag(pos);
        break;
    case ITEM_TYPE::ITEM_MOMSLIPSTICK:
        _item = new CLipstick(pos);
        break;
    case ITEM_TYPE::ITEM_PENTAGRAM:
        _item = new CPentagram(pos);
        break;
    case ITEM_TYPE::ITEM_SPEEDBALL:
        _item = new CSpeedBall(pos);
        break;
    default:
        break;
    }
    item.push_back(_item);
}

void itemManager::respawnUseItem(USE_ITEM type, vector2 pos)
{
    CUseItem* _useitem;
    switch (type)
    {
    case USE_ITEM::BOMB:
        _useitem = new CUseBomb(pos);
        _useitem->setPlayer(player);
        break;
    default:
        break;
    }
    useItem.push_back(_useitem);
}

viItem itemManager::getviItem(int number)
{
    iItem = item.begin() + number;
    return iItem;
}

viUseItem itemManager::getviUseItem(int number)
{
    return viUseItem();
}

void itemManager::itemRemove(int number)
{
    item.erase(item.begin() + number);
}

void itemManager::useItemRemove(int number)
{
    useItem.erase(useItem.begin() + number);
}

void itemManager::respawnRandomBasicItem(vector2 pos)
{
    CItem* _item;
    int random = RND->getFromIntTo(0, 6);
    switch (random)
    {
    case 0:
        _item = new CHeart(pos);
        break;
    case 1:
        _item = new CCoin(pos);
        break;
    case 2:
        _item = new CBomb(pos);
        break;
    case 3:
        _item = new CKey(pos);
        break;
    default:
        return;
    }
    item.push_back(_item);
}

void itemManager::bombFire()
{
    viuseItem = useItem.begin();
    for (viuseItem; viuseItem < useItem.end(); ++viuseItem)
    {
        if ((*viuseItem)->getisUse())
        {
            useItem.erase(viuseItem);
            break;
        }
        break;
    }
}

void itemManager::eraseAllItem()
{
    item.clear();
    useItem.clear();
}
