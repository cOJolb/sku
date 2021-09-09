#include "framework.h"
#include "collision.h"
#include "collider.h"
#include "obstacle.h"
#include "enemy.h"
#include "item.h"
#include "player.h"
#include "bullet.h"

C_collision::C_collision()
{
	skulDelay = 0;
}

C_collision::~C_collision()
{
}

bool C_collision::isCollision(RECT _left, RECT _right)
{
	int leftSize = _left.right - _left.left;
	int rightSize = _right.right - _right.left;

	int leftPt = _left.left + leftSize / 2;
	int rightPt = _right.left + rightSize / 2;

	float fDist = abs(leftPt - rightPt);
	float fSize = leftSize / 2.f + rightSize / 2.f;

	if (fDist < fSize)
	{
		leftSize = _left.bottom - _left.top;
		rightSize = _right.bottom - _right.top;
		leftPt = _left.top + leftSize / 2;
		rightPt = _right.top + rightSize / 2;

		fDist = abs(leftPt - rightPt);
		fSize = leftSize / 2.f + rightSize / 2.f;

		if (fDist < fSize)
		{
			// y축으로 겹친다.
			return true;
		}
	}
	return false;
}

bool C_collision::isCollision(C_collider* _left, C_collider* _right)
{
	float fDist = abs(_left->getPos().x - _right->getPos().x);
	float fSize = _left->getSize().x / 2.f + _right->getSize().x / 2.f;

	if (fDist < fSize)
	{
		// x 축으로 겹친다.
		fDist = abs(_left->getPos().y - _right->getPos().y);
		fSize = _left->getSize().y / 2.f + _right->getSize().y / 2.f;

		if (fDist < fSize)
		{
			// y축으로 겹친다.
			return true;
		}
	}
	return false;
}

bool C_collision::tileCollision(C_obstacle* _tile, C_object* _unit)
{
	return false;
}

void C_collision::stageCollision(C_player* _player)
{
	skulDelay++;
	if (skulDelay > 100) {skulDelay = 100;}
	bool skulChangeOk = skulDelay >= 100;
	for (int i = 0; i < BULLET->getvBullet().size(); i++)
	{
		bool isPlayerBullet = (*BULLET->getviBullet(i))->getPlayerBullet();
		bool BtP = isCollision(_player->getCollider(), (*BULLET->getviBullet(i))->getCollider());
		if (isPlayerBullet)
		{
			for (int j = 0; j < ENEMY->getvEnemy().size(); j++)
			{
				bool BtE = isCollision((*ENEMY->getviEnemy(j))->getCollider(), (*BULLET->getviBullet(i))->getCollider());
				if (BtE)
				{
					if (!(*ENEMY->getviEnemy(j))->isSuperArmor()) { (*ENEMY->getviEnemy(j))->setState(STATE_TYPE::DAMAGE); }
					int bulletdamage = (*BULLET->getviBullet(i))->getDamage();
					int enemyhp = (*ENEMY->getviEnemy(j))->gethp();
					
					(*ENEMY->getviEnemy(j))->sethp((*ENEMY->getviEnemy(j))->gethp() - (*BULLET->getviBullet(i))->getDamage());
					(*ENEMY->getviEnemy(j))->setAlpha(50);
					if ((*BULLET->getviBullet(i))->getJustOne())
					{
						BULLET->eraserBullet(i);
						break;
					}
				}
			}
		}
		else if (BtP)
		{
			_player->sethp(_player->gethp() - (*BULLET->getviBullet(i))->getDamage());
			if ((*BULLET->getviBullet(i))->getJustOne())
			{
				BULLET->eraserBullet(i);
				_player->setAlpha(50);
				break;
			}
		}
	}
	for (int i = 0; i < ENEMY->getvEnemy().size(); i++)
	{
		
		if ((*ENEMY->getviEnemy(i))->gethp() <= 0)
		{
			ENEMY->eraserEnemy(i);
			break;
		}
		
	}
	for (int i = 0; i < ITEM->getvItem().size(); i++)
	{
		bool PtI = isCollision(_player->getCollider(), (*ITEM->getviItem(i))->getCollider());
		bool pushF = InputManager->isStayKeyDown('F');
		bool goods = (*ITEM->getviItem(i))->getItemType() == ITEM_TYPE::GOODS;
		bool skultem = (*ITEM->getviItem(i))->getItemType() == ITEM_TYPE::SKUL;
		bool passive = (*ITEM->getviItem(i))->getItemType() == ITEM_TYPE::PASSIVE;
		bool active = (*ITEM->getviItem(i))->getItemType() == ITEM_TYPE::PASSIVE;
		if (PtI && goods)
		{
			ITEM->itemRemove(i);
		}
		if (PtI && passive && pushF)
		{
			if (ITEM->getvEquipItem().size() >= 9)
			{
				SCENE->changeScene("item");
			}
			else
			{
				C_item* item = (*ITEM->getviItem(i));
				ITEM->EquipPassiveItem(item);
				item->init(_player);
				ITEM->itemRemove(i);
			}
		}
		if (PtI && skultem && pushF&& skulChangeOk)
		{
			skulDelay = 0;
			if (PLAYERDATA->getPlayerData()->getNextSkul() == nullptr)
			{
				PLAYERDATA->getPlayerData()->setNextSkul((*ITEM->getviItem(i))->getSkulItemType());
				ITEM->itemRemove(i);
			}
			else
			{
				ITEM->respawnSkulItem(PLAYERDATA->getPlayerData()->getCurSkul()->getSkulType(), PLAYERDATA->getPlayerData()->getPt());
				PLAYERDATA->getPlayerData()->setCurSkul((*ITEM->getviItem(i))->getSkulItemType());
				ITEM->itemRemove(i);
			}
		}
	}
	for (int i = 0; i < OBSTACLE->getvDoor().size(); i++)
	{
		bool enemyNothing = ENEMY->getvEnemy().size() <= 0;
		bool inputF = InputManager->isStayKeyDown('F');
		bool isDoor = isCollision(_player->getCollider(), (*OBSTACLE->getviDoor(i))->getCollider());
		if (enemyNothing && inputF && isDoor)
		{
			_player->setNextLevel(true);
			break;
		}
		else { _player->setNextLevel(false); }
	}
}

