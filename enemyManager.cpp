#include "framework.h"
#include "enemyManager.h"
#include"CMonster.h"
#include"CHopper.h"
#include"CFly.h"
#include"CHost.h"
#include"CWORM.h"
#include"CMulligan.h"
#include"CGurdy.h"
#include"Csmallfly.h"

#include "CCollider.h"

#include "CPlayer.h"
enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{

	visummon = vsummon.begin();
	for (visummon; visummon != vsummon.end(); ++visummon)
	{
		if (visummon->isrespawn == true)
		{
			respawnMinion(visummon->m_Mtype, visummon->p_pos);
			visummon->isrespawn = false;
		}
	}
	
	_viminion = _vminion.begin();
	for (_viminion; _viminion != _vminion.end(); ++_viminion)
	{
		(*_viminion)->update();
	}
}

void enemyManager::render()
{
	_viminion = _vminion.begin();
	for (_viminion; _viminion != _vminion.end(); ++_viminion)
	{
		(*_viminion)->render();
	}
}


void enemyManager::respawnMinion(MONSTER_TYPE type, Vec2 pos)
{
	CMonster* monster;
	switch (type)
	{
	case MONSTER_TYPE::NONE:
		return;
		break;
	case MONSTER_TYPE::FLY:
		monster = new CFly;
		break;
	case MONSTER_TYPE::HOPPER:
		monster = new CHopper;
		break;
	case MONSTER_TYPE::HOST:
		monster = new CHost;
		break;
	case MONSTER_TYPE::MULLIGAN:
		monster = new CMulligan;
		break;
	case MONSTER_TYPE::WORM:
		monster = new CWORM;
		break;
	case MONSTER_TYPE::GURDY:
		monster = new CGurdy;
		break;
	case MONSTER_TYPE::SMALLFLY:
		monster = new Csmallfly;
		break;
	default:
		return;
		break;
	}
	monster->init(pos.x, pos.y);
	_vminion.push_back(monster);

}

void enemyManager::respawn(MONSTER_TYPE type, Vec2 pos)
{
	summon _summon;
	_summon.m_Mtype = type;
	_summon.p_pos = pos;
	_summon.isrespawn = true;

	vsummon.push_back(_summon);
}

viminion enemyManager::getvimonster(int number)
{
	_viminion = _vminion.begin() + number;
	return _viminion;
}
//
//void enemyManager::bossDie()
//{
//	_viminion = _vminion.begin();
//	for (_viminion; _viminion != _vminion.end(); ++_viminion)
//	{
//		if ((*_viminion)->getMonster_Type() == MONSTER_TYPE::GURDY)
//		{
//
//		}
//	}
//	if (count <= 300)
//	{
//		count++;
//		EFFECT->play("gurdydie", m_pFSM->GetMon()->getPt().x, m_pFSM->GetMon()->getPt().y);
//		EFFECT->play("bossdiebase", m_pFSM->GetMon()->getPt().x, m_pFSM->GetMon()->getPt().y - 100);
//		if (count % 20 == 0)
//		{
//			int x = RND->getFromIntTo(m_pFSM->GetMon()->getPt().x - 100, m_pFSM->GetMon()->getPt().x + 100);
//			int y = RND->getFromIntTo(m_pFSM->GetMon()->getPt().y, m_pFSM->GetMon()->getPt().y + 100);
//			EFFECT->play("bossdiebase", x, y);
//		}
//	}
//}
