#include "framework.h"
#include "UseItem.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CFSM.h"
#include "CStage.h"
#include "CMap.h"
#include "CObstacle.h"
CUseItem::CUseItem()
{
	type = ITEM_TYPE::ITEM_NONE;
}

CUseItem::CUseItem(vector2 _pt)
{
}

CUseItem::~CUseItem()
{
}

HRESULT CUseItem::init()
{
	return E_NOTIMPL;
}

void CUseItem::release()
{
}

void CUseItem::update()
{
}

void CUseItem::render()
{
}


CUseBomb::CUseBomb()
{
}

CUseBomb::CUseBomb(vector2 _pt)
{
	rc = RectMakeCenter(_pt, 30, 30);
	CObject::init(_pt, rc, _pt, { 20 ,20 }, 5, { _pt.x , _pt.y + 10 }, { 30, 10 });
	usetype = USE_ITEM::BOMB;
}

CUseBomb::~CUseBomb()
{
}

HRESULT CUseBomb::init()
{
	return E_NOTIMPL;
}

void CUseBomb::release()
{
	delete this;
}

void CUseBomb::update()
{
	count++;
	if (count == 50)
	{
		SOUND->play("bombsound");
		RECT playerCollider = RectMakeCenter(player->getcollider()->getPos(), player->getcollider()->getSize().x, player->getcollider()->getSize().y);
		RECT bombRange = RectMakeCenter(pt, 100, 100);
		if (COLLISION->isCollision(bombRange, playerCollider))
		{
			SOUND->play("playerhurt2");
			player->sethp(player->gethp() - 2);
			player->getAI()->ChangeState(STATE_TYPE::ATTACK);

		}
		
		for (int i = 0; i < ENEMY->getvmonster().size(); i++)
		{
			RECT monsterCollider = RectMakeCenter((*ENEMY->getvimonster(i))->getcollider()->getPos(), (*ENEMY->getvimonster(i))->getcollider()->getSize().x, (*ENEMY->getvimonster(i))->getcollider()->getSize().y);

			if (COLLISION->isCollision(bombRange, monsterCollider))
			{
				(*ENEMY->getvimonster(i))->sethp((*ENEMY->getvimonster(i))->gethp() - 10);
			}
		}
		for (int i = 0; i < 135; i++)
		{
			RECT cheakTile = RectMakeCenter((*STAGE->getCurStage()->getCurRoom()->getviObstacle(i))->getcollider()->getPos(),
				(*STAGE->getCurStage()->getCurRoom()->getviObstacle(i))->getcollider()->getSize().x,
				(*STAGE->getCurStage()->getCurRoom()->getviObstacle(i))->getcollider()->getSize().y);
			bool isbroke = (*STAGE->getCurStage()->getCurRoom()->getviObstacle(i))->getDestroyBomb();

			if (COLLISION->isCollision(bombRange, cheakTile) && isbroke)
			{
				(*STAGE->getCurStage()->getCurRoom()->getviObstacle(i))->setObjType(OBJECT::OBJ_NONE);
				SOUND->play("rockbrokensound");
			}
		}
		EFFECT->play("explosion", RectX(bombRange), RectY(bombRange));
	}
	if (count == 55)
	{
		isUse = true;
	}
}

void CUseBomb::render()
{
	if (count > 50)
	{
		if (InputManager->isToggleKey(VK_TAB))
		{
			RECT bombRange = RectMakeCenter(pt, 100, 100);
			Rectangle(getMemDC(), bombRange.left, bombRange.top, bombRange.right, bombRange.bottom);
		}
	}
	RECT rec = RectMakeCenter(getcollider()->getPos(), 45, 45);
	RECT recshadow = RectMakeCenter(GetcolliderShadow()->getPos(), 30, 10);

	IMAGE->render("itemshadow", getMemDC(), recshadow.left, recshadow.top);
	IMAGE->frameRender("bomb", getMemDC(), rec.left, rec.top, 0, 0);


}
