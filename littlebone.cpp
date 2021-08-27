#include "framework.h"
#include "littlebone.h"
#include "collision.h"
#include"enemy.h"
#include"fsm.h"
C_littlebone::C_littlebone()
{
	skulInfo.playerSpeed = 5;
	skulInfo.DashTerm = 10;
	skulInfo.playerDashSpeed = 8;
	skulInfo.DashTime = 34;
	skulInfo.playerJumpPower = 20;
	skulInfo.canDoubleDash = true;

	unitName = "skul";
}

C_littlebone::~C_littlebone()
{
}

HRESULT C_littlebone::init()
{
	return S_OK;
}

void C_littlebone::release()
{
}

void C_littlebone::update()
{
}

void C_littlebone::render()
{
}

void C_littlebone::playerAttack(vector2 _pt, bool _isLeft )
{
	attackRange = new C_collider;
	attackRange->setSize({ 60, 60 });
	if (_isLeft)
	{
		attackRange->setPos({ _pt.x - 30, _pt.y });
	}
	else attackRange->setPos({ _pt.x + 30, _pt.y });
	for (int i = 0; i < ENEMY->getvEnemy().size(); i++)
	{
		if (COLLISION->isCollision(attackRange, (*ENEMY->getviEnemy(i))->getCollider()))
		{
			(*ENEMY->getviEnemy(i))->sethp((*ENEMY->getviEnemy(i))->gethp() - 3);
			(*ENEMY->getviEnemy(i))->getAi()->SetState(STATE_TYPE::DAMAGE);
			if ((*ENEMY->getviEnemy(i))->gethp() <= 0)
			{
				ENEMY->eraserEnemy(i);
			}
		}
	}
	SAFE_DELETE(attackRange);
}

void C_littlebone::playerDashMove(vector2& _pt, int& _DashCount, bool _DashJump, bool _DashFoward, float _DashSpeed)
{
	if (_DashCount > 0 && !_DashJump)
	{
		_DashCount--;
		if (_DashFoward)
		{
			_pt.x -= _DashSpeed;
		}

		else if (!_DashFoward)
		{
			_pt.x += _DashSpeed;
		}
	}
}

void C_littlebone::skillA()
{
}

void C_littlebone::skillB()
{
}
