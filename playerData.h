#pragma once
#include "singleton.h"
class C_collider;
struct S_playerData
{
	vector2 playerPt;
	C_collider* playerCollider;
};
class C_playerData : public Singleton<C_playerData>
{
private:
	S_playerData playerData;
public:
	C_playerData();
	~C_playerData();

public:
	void savePlayerData(vector2 _pt, C_collider* _collider);
	S_playerData getPlayerData();
};

