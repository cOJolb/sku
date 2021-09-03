#pragma once
#include "singleton.h"
class C_collider;
class C_player;

class C_playerData : public Singleton<C_playerData>
{
private:
	C_player* player;
public:
	C_playerData();
	~C_playerData();
public:
	void setPlayerData(C_player* _player);
	C_player* getPlayerData();
};

