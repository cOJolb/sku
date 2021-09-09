#include "framework.h"
#include "playerUI.h"
#include "player.h"
playerUI::playerUI()
{
	NowHp = 0;
}

playerUI::~playerUI()
{
}

void playerUI::render(HDC hdc)
{
	IMAGE->findImage("playerUI")->renderCenter(hdc, { 168,GameSizeY - 66 });
	//NowHp = PLAYERDATA->getPlayerData()->getmaxHp();



	//NowHp = (IMAGE->findImage("hpBar")->getWidth() / PLAYERDATA->getPlayerData()->getmaxHp()) * PLAYERDATA->getPlayerData()->gethp();
	double maxHp = PLAYERDATA->getPlayerData()->getmaxHp();
	double Hp = PLAYERDATA->getPlayerData()->gethp();
	double barWidth = IMAGE->findImage("hpBar")->getWidth();
	NowHp = barWidth/maxHp *Hp;
	//NowHp = 50;
	IMAGE->findImage("hpBar")->renderCenter(hdc, { 204,GameSizeY - 35 },0,0,NowHp,IMAGE->findImage("hpBar")->getHeight());
	IMAGE->findImage(PLAYERDATA->getPlayerData()->getCurSkul()->getUnitName() + "Now")->renderCenter(hdc, { 57, GameSizeY -84 });
	IMAGE->findImage(PLAYERDATA->getPlayerData()->getCurSkul()->getUnitName() + "Skill1")->renderCenter(hdc, { 140, GameSizeY - 75 });
	IMAGE->findImage("coolTime")->render(hdc, 140-18, GameSizeY - 75-18+ PLAYERDATA->getPlayerData()->getSkillACoolTime(),0, PLAYERDATA->getPlayerData()->getSkillACoolTime(),36, 36);
	IMAGE->findImage("a")->renderCenter(hdc, { 140, GameSizeY - 95 });
	if (PLAYERDATA->getPlayerData()->getHaveTwoSkill())
	{
		IMAGE->findImage(PLAYERDATA->getPlayerData()->getCurSkul()->getUnitName() + "Skill2")->renderCenter(hdc, { 208, GameSizeY - 75 });
		IMAGE->findImage("coolTime")->render(hdc, 208 - 18, GameSizeY - 75 - 18 + PLAYERDATA->getPlayerData()->getSkillBCoolTime(), 0, PLAYERDATA->getPlayerData()->getSkillBCoolTime(), 36, 36);
		IMAGE->findImage("s")->renderCenter(hdc, { 208, GameSizeY - 95 });
	}
	if (PLAYERDATA->getPlayerData()->getNextSkul() != nullptr)
	{
		IMAGE->findImage(PLAYERDATA->getPlayerData()->getNextSkul()->getUnitName() + "Second")->renderCenter(hdc, { 30, GameSizeY - 20 });
		IMAGE->findImage("coolTime")->render(hdc, 30- 18, GameSizeY - 20 -18+ PLAYERDATA->getPlayerData()->getChangeCoolTime(), 0, PLAYERDATA->getPlayerData()->getChangeCoolTime(), 36, 36);
	}
}

