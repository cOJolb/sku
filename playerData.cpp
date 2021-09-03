#include "framework.h"
#include "playerData.h"
#include "player.h"
#include "collider.h"

C_playerData::C_playerData()
{
}

C_playerData::~C_playerData()
{
}


void C_playerData::setPlayerData(C_player* _player)
{
	player = _player;
}

C_player* C_playerData::getPlayerData()
{
	return player;
}


