#include "framework.h"
#include "collisionManager.h"
#include "CCollider.h"
#include "CMap.h"
#include "CStage.h"
#include "CPlayer.h"
#include "CObstacle.h"
#include "CMonster.h"
#include "CFSM.h"
#include "CPlayer.h"
#include "CBullet.h"
collisionManager::collisionManager()
{
	bossDie = false;
	count = 0;
}

collisionManager::~collisionManager()
{
}

//HRESULT collisionManager::init()
//{
//	return S_OK;
//}
//
//void collisionManager::release()
//{
//}
//
//void collisionManager::update()
//{
//}
//
//void collisionManager::render()
//{
//}

bool collisionManager::isCollision(CCollider* _left, CCollider* _right)
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


bool collisionManager::isCollision(RECT _left, RECT _right)
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


int collisionManager::whereAreYouGoing(float& _prevX, float& _prevY, float _x, float _y)
{
	float incrementX = _x - _prevX;
	float incrementY = _y - _prevY;
	_prevX = _x;
	_prevY = _y;
	if (incrementX == 0 && incrementY == 0)
	{
		return FOWARD::NONE;
	}
	if (incrementX > 0 && incrementY == 0)
	{
		return FOWARD::RIGHT;
	}
	if (incrementX < 0 && incrementY == 0)
	{
		return FOWARD::LEFT;
	}
	if (incrementX == 0 && incrementY > 0)
	{
		return FOWARD::DOWN;
	}
	if (incrementX == 0 && incrementY < 0)
	{
		return FOWARD::UP;
	}
	if (incrementX > 0 && incrementY > 0)
	{
		return FOWARD::RIGHTDOWN;
	}
	if (incrementX > 0 && incrementY < 0)
	{
		return FOWARD::RIGHTTOP;
	}
	if (incrementX < 0 && incrementY > 0)
	{
		return FOWARD::LEFTDOWN;
	}
	if (incrementX < 0 && incrementY < 0)
	{
		return FOWARD::LEFTTOP;
	}
}

int collisionManager::whereAreYouGoing(vector2& _prevPt, vector2 _Pt)
{
	float incrementX = _Pt.x - _prevPt.x;
	float incrementY = _Pt.y - _prevPt.y;

	if (incrementX == 0 && incrementY == 0)
	{
		return FOWARD::NONE;
	}
	if (incrementX > 0 && incrementY == 0)
	{
		return FOWARD::RIGHT;
	}
	if (incrementX < 0 && incrementY == 0)
	{
		return FOWARD::LEFT;
	}
	if (incrementX == 0 && incrementY > 0)
	{
		return FOWARD::DOWN;
	}
	if (incrementX == 0 && incrementY < 0)
	{
		return FOWARD::UP;
	}
	if (incrementX > 0 && incrementY > 0)
	{
		return FOWARD::RIGHTDOWN;
	}
	if (incrementX > 0 && incrementY < 0)
	{
		return FOWARD::RIGHTTOP;
	}
	if (incrementX < 0 && incrementY > 0)
	{
		return FOWARD::LEFTDOWN;
	}
	if (incrementX < 0 && incrementY < 0)
	{
		return FOWARD::LEFTTOP;
	}
}


bool collisionManager::tileCollision(CMap* _map, vector2& _pt, vector2& _prevPt, int _foward ,int _type)
{
	float width = 30;
	float height = 30;
	
	RECT rc = RectMakeCenter(_pt, width, height);
	RECT prevRc = RectMakeCenter(_prevPt, width, height);

	int hereIndex = (rc.left / TILEWIDTH-1 ) + (rc.top / TILEHEIGHT-1 ) * TILEX;
	

	int testIndex[3] = { 0,1,2 };
	switch (_foward)
	{
	case FOWARD::DOWN:
		testIndex[0] = hereIndex + TILEX;
		testIndex[1] = hereIndex + TILEX + 1;
		break;
	case FOWARD::LEFT:
		testIndex[0] = hereIndex;
		testIndex[1] = hereIndex + TILEX;
		break;
	case FOWARD::RIGHT:
		testIndex[0] = hereIndex + 1;
		testIndex[1] = hereIndex + 1 + TILEX;
		break;
	case FOWARD::UP:
		testIndex[0] = hereIndex ;
		testIndex[1] = hereIndex  + 1;
		break;
	case FOWARD::LEFTDOWN:
		testIndex[0] = hereIndex ;
		testIndex[1] = hereIndex + TILEX;
		testIndex[2] = hereIndex + TILEX + 1;
		//testIndex[3] = hereIndex + TILEX - 1;
		break;
	case FOWARD::LEFTTOP:
		testIndex[0] = hereIndex + TILEX;
		testIndex[1] = hereIndex;
		testIndex[2] = hereIndex + 1;
		//testIndex[3] = hereIndex - TILEX;
		break;
	case FOWARD::RIGHTDOWN:
		testIndex[0] = hereIndex + 1;
		testIndex[1] = hereIndex + TILEX + 1;
		testIndex[2] = hereIndex + TILEX;
		//testIndex[3] = hereIndex + TILEX - 1;
		break;
	case FOWARD::RIGHTTOP:
		testIndex[0] = hereIndex + TILEX +1;
		testIndex[1] = hereIndex + 1;
		testIndex[2] = hereIndex;
		//testIndex[3] = hereIndex - TILEX - 1;
		break;
	default:
		break;
	}

	bool isBump = 0;
	bool cant = 0;

	for (int i = 0; i < 3; i++)
	{
		if (testIndex[i] < 0) continue;
		isBump = isCollision(rc, _map->getTile()[testIndex[i]].rcTile);
		cant = (_map->getvObstacle()[testIndex[i]]->getUnmovalbe());

		if (isBump && cant)
		{
			switch (_foward)
			{
			case FOWARD::DOWN:
				rc.bottom = _map->getTile()[testIndex[i]].rcTile.top;
				rc.top = rc.bottom - height;
				break;
			case FOWARD::LEFT:
				rc.left = _map->getTile()[testIndex[i]].rcTile.right;
				rc.right = rc.left + width;
				break;
			case FOWARD::RIGHT:
				rc.right = _map->getTile()[testIndex[i]].rcTile.left;
				rc.left = rc.right - width;
				break;
			case FOWARD::UP:
				rc.top = _map->getTile()[testIndex[i]].rcTile.bottom;
				rc.bottom = rc.top + height;
				break;
			case FOWARD::LEFTDOWN:
				switch (i)
				{
				case 0:
					rc.left = _map->getTile()[testIndex[i]].rcTile.right;
					rc.right = rc.left + width;
					break;
				case 1:
					if (prevRc.left >= _map->getTile()[testIndex[i]].rcTile.right)
					{
						rc.left = _map->getTile()[testIndex[i]].rcTile.right;
						rc.right = rc.left + width;
					}
					else
					{
						rc.bottom = _map->getTile()[testIndex[i]].rcTile.top;
						rc.top = rc.bottom - height;
					}
					break;
				case 2:
					rc.bottom = _map->getTile()[testIndex[i]].rcTile.top;
					rc.top = rc.bottom - height;
					break;
				}
				break;
			case FOWARD::LEFTTOP:
				switch (i)
				{
				case 0:
					rc.left = _map->getTile()[testIndex[i]].rcTile.right;
					rc.right = rc.left + width;
					break;
				case 1:
					if (prevRc.top >= _map->getTile()[testIndex[i]].rcTile.bottom)
					{

						rc.top = _map->getTile()[testIndex[i]].rcTile.bottom;
						rc.bottom = rc.top + height;
					}
					else
					{
						rc.left = _map->getTile()[testIndex[i]].rcTile.right;
						rc.right = rc.left + width;
					}
					break;
				case 2:
					rc.top = _map->getTile()[testIndex[i]].rcTile.bottom;
					rc.bottom = rc.top + height;
					break;
				}
				break;
			case FOWARD::RIGHTDOWN:
				switch (i)
				{
				case 0:
					rc.right = _map->getTile()[testIndex[i]].rcTile.left;
					rc.left = rc.right - width;
					break;
				case 1:
					if (prevRc.right <= _map->getTile()[testIndex[i]].rcTile.left)
					{
						rc.right = _map->getTile()[testIndex[i]].rcTile.left;
						rc.left = rc.right - width;
					}
					else
					{
						rc.bottom = _map->getTile()[testIndex[i]].rcTile.top;
						rc.top = rc.bottom - height;
					}
					break;
				case 2:
					rc.bottom = _map->getTile()[testIndex[i]].rcTile.top;
					rc.top = rc.bottom - height;
					break;
				}
				break;
			case FOWARD::RIGHTTOP:
				switch (i)
				{
				case 0:
					rc.right = _map->getTile()[testIndex[i]].rcTile.left;
					rc.left = rc.right - width;
					break;
				case 1:
					if (prevRc.right <= _map->getTile()[testIndex[i]].rcTile.left)
					{
						rc.right = _map->getTile()[testIndex[i]].rcTile.left;
						rc.left = rc.right - width;
					}
					else
					{
						rc.top = _map->getTile()[testIndex[i]].rcTile.bottom;
						rc.bottom = rc.top + height;
					}
					break;
				case 2:
					rc.top = _map->getTile()[testIndex[i]].rcTile.bottom;
					rc.bottom = rc.top + height;
					break;
				}
				break;
			default:
				break;
			}
		}
	}
	

	if (_type == 1)
	{
		monsterCollision(rc, prevRc, _foward);
	}
	vector2 Pt = { RectX(rc), RectY(rc) };
	_prevPt = Pt;
	_pt = Pt;

	return (isBump && cant);
}

void collisionManager::monsterCollision(RECT& _rc, RECT& _prevRc, int _foward)
{
	float width = 30;
	float height = 30;

	bool isBump = 0;

	for (int i = 0; i < ENEMY->getvmonster().size(); i++)
	{
		RECT rec = RectMakeCenter((*ENEMY->getvimonster(i))->getcollider()->getPos(), 30, 30);
		if (RectX(_rc) == RectX(rec) && RectY(_rc) == RectY(rec))
		{
			break;
		}
		isBump = isCollision(_rc, rec);
		if (isBump)
		{
			switch (_foward)
			{
			case FOWARD::DOWN:
				_rc.bottom = rec.top;
				_rc.top = _rc.bottom - height;
				break;
			case FOWARD::LEFT:
				_rc.left = rec.right;
				_rc.right = _rc.left + width;
				break;
			case FOWARD::RIGHT:
				_rc.right = rec.left;
				_rc.left = _rc.right - width;
				break;
			case FOWARD::UP:
				_rc.top = rec.bottom;
				_rc.bottom = _rc.top + height;
				break;
			case FOWARD::LEFTDOWN:
				switch (i)
				{
				case 0:
					_rc.left = rec.right;
					_rc.right = _rc.left + width;
					break;
				case 1:
					if (_prevRc.left >= rec.right)
					{
						_rc.left = rec.right;
						_rc.right = _rc.left + width;
					}
					else
					{
						_rc.bottom = rec.top;
						_rc.top = _rc.bottom - height;
					}
					break;
				case 2:
					_rc.bottom = rec.top;
					_rc.top = _rc.bottom - height;
					break;
				}
				break;
			case FOWARD::LEFTTOP:
				switch (i)
				{
				case 0:
					_rc.left = rec.right;
					_rc.right = _rc.left + width;
					break;
				case 1:
					if (_prevRc.top >= rec.bottom)
					{

						_rc.top = rec.bottom;
						_rc.bottom = _rc.top + height;
					}
					else
					{
						_rc.left = rec.right;
						_rc.right = _rc.left + width;
					}
					break;
				case 2:
					_rc.top = rec.bottom;
					_rc.bottom = _rc.top + height;
					break;
				}
				break;
			case FOWARD::RIGHTDOWN:
				switch (i)
				{
				case 0:
					_rc.right = rec.left;
					_rc.left = _rc.right - width;
					break;
				case 1:
					if (_prevRc.right <= rec.left)
					{
						_rc.right = rec.left;
						_rc.left = _rc.right - width;
					}
					else
					{
						_rc.bottom = rec.top;
						_rc.top = _rc.bottom - height;
					}
					break;
				case 2:
					_rc.bottom = rec.top;
					_rc.top = _rc.bottom - height;
					break;
				}
				break;
			case FOWARD::RIGHTTOP:
				switch (i)
				{
				case 0:
					_rc.right = rec.left;
					_rc.left = _rc.right - width;
					break;
				case 1:
					if (_prevRc.right <= rec.left)
					{
						_rc.right = rec.left;
						_rc.left = _rc.right - width;
					}
					else
					{
						_rc.top = rec.bottom;
						_rc.bottom = _rc.top + height;
					}
					break;
				case 2:
					_rc.top = rec.bottom;
					_rc.bottom = _rc.top + height;
					break;
				}
				break;
			default:
				break;
			}
		}
	}
}

vector2 collisionManager::sliding(int _foward, vector2 _pt)
{

	return vector2();
}

bool collisionManager::wallCollision(vector2& _objectPt, vector2 _startPt, float _sizeX, float _sizeY)
{
	float width = 30;
	float height = 30;
	bool isBump = false;
	RECT rc = RectMakeCenter(_objectPt, width, height);
	RECT map = RectMake(_startPt, _sizeX, _sizeY);

	if (rc.right > map.right)
	{
		rc.right = map.right;
		rc.left = rc.right - width;
		isBump = true;
	}
	if (rc.left < map.left)
	{
		rc.left = map.left;
		rc.right = rc.left + width;
		isBump = true;
	}
	if (rc.top < map.top)
	{
		rc.top = map.top;
		rc.bottom = rc.top + height;
		isBump = true;
	}
	if (rc.bottom > map.bottom)
	{
		rc.bottom = map.bottom;
		rc.top = rc.bottom - height;
		isBump = true;
	}
	_objectPt = { RectX(rc), RectY(rc) };

	return isBump;
}

DOOR_DIRECTION collisionManager::doorCollision(CMap* _map, CPlayer* _player)
{
	if (_map->getvObstacle()[7]->getObjType() == OBJECT::OBJ_TOPDOOR)
	{
		if (isCollision(_map->getvObstacle()[7]->getcollider(), _player->GetcolliderShadow()))
			return DOOR_DIRECTION::TOP;
	}
	
	if (_map->getvObstacle()[60]->getObjType() == OBJECT::OBJ_LEFTDOOR)
	{
		if (isCollision(_map->getvObstacle()[60]->getcollider(), _player->GetcolliderShadow()))
			return DOOR_DIRECTION::LEFT;
	}

	if (_map->getvObstacle()[74]->getObjType() == OBJECT::OBJ_RIGHTDOOR)
	{
		if (isCollision(_map->getvObstacle()[74]->getcollider(), _player->GetcolliderShadow()))
			return DOOR_DIRECTION::RIGHT;
	}

	if (_map->getvObstacle()[127]->getObjType() == OBJECT::OBJ_BOTTOMDOOR)
	{
		if (isCollision(_map->getvObstacle()[127]->getcollider(), _player->GetcolliderShadow()))
			return DOOR_DIRECTION::BOTTOM;
	}
	return DOOR_DIRECTION::END;
}

bool collisionManager::goalCollision(CMap* _map, CPlayer* player)
{
	for (int i = 0; i < _map->getvObstacle().size(); i++)
	{
		if (_map->getvObstacle()[i]->getObjType() == OBJECT::OBJ_GOAL)
		{
			if (isCollision(_map->getvObstacle()[i]->getcollider(), player->GetcolliderShadow()))
				return true;
			break;
		}
	}
	return false;
}

void collisionManager::stageCollision(CPlayer* _player)
{
	bool playerIdle = _player->getstate() == STATE_TYPE::IDLE;
	ENEMY->SetPlayer(_player);

	for (int i = 0; i < ENEMY->getvmonster().size(); i++)		//playerBullet and monster collision
	{
		for (int j = 0; j < BULLET->getvBullet().size(); j++)
		{
			bool ispbcm = COLLISION->isCollision((*BULLET->getviBullet(j))->getcollider(), (*ENEMY->getvimonster(i))->getcollider());
			bool ispbrm = COLLISION->isCollision((*BULLET->getviBullet(j))->GetcolliderShadow(), (*ENEMY->getvimonster(i))->GetcolliderShadow());
			bool ispB = (*BULLET->getviBullet(j))->gettype() == CHARACTER::PLAYER;
			if (ispB &&ispbcm &&ispbrm)
			{
				
				(*ENEMY->getvimonster(i))->sethp((*ENEMY->getvimonster(i))->gethp() - (*BULLET->getviBullet(j))->getDamage());
				EFFECT->play("playerbulleteffect", (*BULLET->getviBullet(j))->getcollider()->getPos().x, (*BULLET->getviBullet(j))->getcollider()->getPos().y);
				BULLET->eraserBullet(j);
				SOUND->play("tearblocksound");
				break;
			}
		}
		bool ispcm = COLLISION->isCollision(_player->getcollider(), (*ENEMY->getvimonster(i))->getcollider());
		bool ispsm = COLLISION->isCollision(_player->GetcolliderShadow(), (*ENEMY->getvimonster(i))->GetcolliderShadow());
		if (playerIdle && ispcm && ispsm)
		{
		
			//SOUND->addSound("playerhurt", "sound/체리.mp3", true, false);
			//ENEMY->eraserEnemy(i);
			_player->sethp(_player->gethp() - 1);
			_player->getAI()->ChangeState(STATE_TYPE::ATTACK);
			SOUND->play("playerhurt",1.0f);
			break;
				
		}
	}
	for (int i = 0; i < STAGE->getCurStage()->getCurRoom()->getvObstacle().size(); i++)
	{
		bool isDamageTile = (*STAGE->getCurStage()->getCurRoom()->getviObstacle(i))->getDamage();
		bool isCollisionTile = COLLISION->isCollision((*STAGE->getCurStage()->getCurRoom()->getviObstacle(i))->getcollider(), _player->getcollider());
		if (playerIdle && isDamageTile && isCollisionTile)
		{
			_player->sethp(_player->gethp() - 1);
			_player->getAI()->ChangeState(STATE_TYPE::ATTACK);
			SOUND->play("playerhurt", 1.0f);
			break;
		}

	}
	for (int i = 0; i < BULLET->getvBullet().size(); i++)		//playerBullet and obstacle
	{
		bool ismbcp = COLLISION->isCollision((*BULLET->getviBullet(i))->getcollider(), _player->getcollider());
		bool ismbsp = COLLISION->isCollision((*BULLET->getviBullet(i))->GetcolliderShadow(), _player->GetcolliderShadow());
		bool ismB = (*BULLET->getviBullet(i))->gettype() == CHARACTER::MONSTER;
		for (int j = 0; j < STAGE->getCurStage()->getCurRoom()->getvObstacle().size(); j++)
		{
			bool colliderBump = COLLISION->isCollision((*BULLET->getviBullet(i))->getcollider(), (*STAGE->getCurStage()->getCurRoom()->getviObstacle(j))->getcollider());
			bool shadowBump = COLLISION->isCollision((*BULLET->getviBullet(i))->GetcolliderShadow(), (*STAGE->getCurStage()->getCurRoom()->getviObstacle(j))->getcollider());
			bool isObstacle = (*STAGE->getCurStage()->getCurRoom()->getviObstacle(j))->getObjType() != OBJECT::OBJ_NONE ;
			bool isPass = (*STAGE->getCurStage()->getCurRoom()->getviObstacle(j))->getPassBullet();
			bool ispB = (*BULLET->getviBullet(i))->gettype() == CHARACTER::PLAYER;
			bool isok = (*BULLET->getviBullet(i))->getshadowdistance() <= 30;
			
			bool isDestroyBullet = (*STAGE->getCurStage()->getCurRoom()->getviObstacle(j))->getDestroyBullet();
			
			if (ispB && isok && shadowBump )
			{
				if (isDestroyBullet)
				{
					(*STAGE->getCurStage()->getCurRoom()->getviObstacle(j))->setStrength((*STAGE->getCurStage()->getCurRoom()->getviObstacle(j))->getStrength() - 1);
					if ((*STAGE->getCurStage()->getCurRoom()->getviObstacle(j))->getStrength() == 0)
					{
						if ((*STAGE->getCurStage()->getCurRoom()->getviObstacle(j))->getObjType() == OBJECT::OBJ_POOP)
						{
							ITEM->respawnRandomBasicItem((*STAGE->getCurStage()->getCurRoom()->getviObstacle(j))->getcollider()->getPos());
							SOUND->play("poopsound");
							(*STAGE->getCurStage()->getCurRoom()->getviObstacle(j))->setObjType(OBJECT::OBJ_NONE);
							EFFECT->play("poofeffect", (*STAGE->getCurStage()->getCurRoom()->getviObstacle(j))->getcollider()->getPos().x, (*STAGE->getCurStage()->getCurRoom()->getviObstacle(j))->getcollider()->getPos().y);
						}
						else
						{
							ITEM->respawnRandomBasicItem((*STAGE->getCurStage()->getCurRoom()->getviObstacle(j))->getcollider()->getPos());
							EFFECT->play("poofeffect", (*STAGE->getCurStage()->getCurRoom()->getviObstacle(j))->getcollider()->getPos().x, (*STAGE->getCurStage()->getCurRoom()->getviObstacle(j))->getcollider()->getPos().y);
						}
					}
					SOUND->play("tearblocksound");
					EFFECT->play("playerbulleteffect", (*BULLET->getviBullet(i))->getcollider()->getPos().x, (*BULLET->getviBullet(i))->getcollider()->getPos().y);
					BULLET->eraserBullet(i);
					break;
				}
				else if (isObstacle)
				{
					if (!isPass)
					{
						SOUND->play("tearblocksound");
						EFFECT->play("playerbulleteffect", (*BULLET->getviBullet(i))->getcollider()->getPos().x, (*BULLET->getviBullet(i))->getcollider()->getPos().y);
						BULLET->eraserBullet(i);
						break;
					}
				}
			}
			else if (isok && shadowBump && isObstacle && !isPass)
			{
				
				SOUND->play("tearblocksound");
				EFFECT->play("enemybulleteffect", (*BULLET->getviBullet(i))->getcollider()->getPos().x, (*BULLET->getviBullet(i))->getcollider()->getPos().y);
				BULLET->eraserBullet(i);
				break;
			}
		}
		if (playerIdle && ismB && ismbcp && ismbsp)
		{

			SOUND->play("playerhurt2");
			EFFECT->play("enemybulleteffect", (*BULLET->getviBullet(i))->getcollider()->getPos().x, (*BULLET->getviBullet(i))->getcollider()->getPos().y);
			BULLET->eraserBullet(i);
			_player->sethp(_player->gethp() - 1);
			_player->getAI()->ChangeState(STATE_TYPE::ATTACK);
			break;
		}
	}
}

void collisionManager::isMonsterDie()
{
	for (int i = 0; i < ENEMY->getvmonster().size(); i++)		//playerBullet and monster collision
	{
		if ((*ENEMY->getvimonster(i))->getstate() == STATE_TYPE::DEAD)
		{
			if ((*ENEMY->getvimonster(i))->getMonster_Type() == MONSTER_TYPE::GURDY)
			{
				bossDie = true;
				bossDiePt = (*ENEMY->getvimonster(i))->getPt();
				SOUND->play("bossdiesound");
			}
			SOUND->play("miniondeathssound");
			EFFECT->play("enemydie", (*ENEMY->getvimonster(i))->getPt().x, (*ENEMY->getvimonster(i))->getPt().y);
			ENEMY->eraserEnemy(i);
			break;
		}
	}
}

void collisionManager::isBossDie()
{
	if (bossDie)
	{
		count++;
		
		if (count % 20 == 0)
		{
			EFFECT->play("gurdydie", bossDiePt.x, bossDiePt.y);
			EFFECT->play("bossdiebase", bossDiePt.x, bossDiePt.y - 100);
			int x = RND->getFromIntTo(bossDiePt.x - 100, bossDiePt.x + 100);
			int y = RND->getFromIntTo(bossDiePt.y, bossDiePt.y + 100);
			EFFECT->play("bossdiebase", x, y);
		}
		else if (count >= 200)
		{
			ENEMY->eraserAllEnemy();
			SOUND->stop("bossdiesound");
			bossDie = false;
			count = 0;
			(*STAGE->getCurStage()->getCurRoom()->getviObstacle(52))->setObjType(OBJECT::OBJ_GOAL);
		}
	}
}
