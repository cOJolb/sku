#include "framework.h"
#include "changePlayer.h"
#include "skul.h"
#include "clown.h"
changePlayer::changePlayer()
{
	Cur_Player = new C_skul;
	Stanby_Player = new C_clown;
	Temp_Player = nullptr;
}

changePlayer::~changePlayer()
{
}

void changePlayer::update()
{
	Cur_Player->update();
	//PLAYERDATA->savePlayerData(Cur_Player->getPt(),Cur_Player->getCollider());
}

void changePlayer::render()
{
	Cur_Player->render();
}

void changePlayer::addSkulType(SKUL_TYPE _type)
{
	if (Stanby_Player == nullptr)
	{
		switch (_type)
		{
		case SKUL_TYPE::SKUL:
			Stanby_Player = new C_skul;
			break;
		case SKUL_TYPE::CLOWN:
			Stanby_Player = new C_clown;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (_type)
		{
		case SKUL_TYPE::SKUL:
			Cur_Player = new C_skul;
			break;
		case SKUL_TYPE::CLOWN:
			Cur_Player = new C_clown;
			break;
		default:
			break;
		}
	}
}

void changePlayer::changeSkul()
{
	if (Stanby_Player != nullptr)
	{
		Temp_Player = Cur_Player;
		Cur_Player->release();
		Cur_Player = Stanby_Player;
		Stanby_Player = Temp_Player;

		Cur_Player->init(PLAYERDATA->getPlayerData().playerPt);
	}
}

void changePlayer::lootSkul()
{
}
