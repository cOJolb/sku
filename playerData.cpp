#include "framework.h"
#include "playerData.h"
#include "collider.h"

C_playerData::C_playerData()
{
	playerData.playerPt = { 200,200 };
}

C_playerData::~C_playerData()
{
}

void C_playerData::savePlayerData(vector2 _pt, C_collider* _collider)
{
	playerData.playerPt = _pt;
	playerData.playerCollider = _collider;
}

S_playerData C_playerData::getPlayerData()
{
	return playerData;
}
