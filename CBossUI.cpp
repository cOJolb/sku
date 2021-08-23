#include "framework.h"
#include "CBossUI.h"
#include "CGurdy.h"
CBossUI::CBossUI()
{
}

CBossUI::~CBossUI()
{
}

HRESULT CBossUI::init()
{
	return E_NOTIMPL;
}

void CBossUI::release()
{
}

void CBossUI::update()
{
	//if (boss->gethp() <= 0) isDie = true;

	//if (isDie)
	//{
	//	count++;
	//	EFFECT->play("gurdydie", boss->getPt().x, boss->getPt().y);
	//	EFFECT->play("bossdiebase", boss->getPt().x, boss->getPt().y-100);
	//	if (count % 20 == 0)
	//	{
	//		int x = RND->getFromIntTo(boss->getPt().x - 100, boss->getPt().x + 100);
	//		int y = RND->getFromIntTo(boss->getPt().y, boss->getPt().y + 100);
	//		EFFECT->play("bossdiebase", x,y);
	//	}
	//	if (count >= 300)
	//	{
	//		count = 0;
	//		isDie = false;
	//	}
	//}
}

void CBossUI::render()
{
	int bossHp = boss->getMaxHp() - boss->gethp();
	if (bossHp > boss->getMaxHp()) { bossHp = boss->getMaxHp(); }
	if (bossHp < boss->getMaxHp())
	{
		minusHp = (IMAGE->findImage("bossFront")->getWidth() / boss->getMaxHp()) * bossHp;
		IMAGE->render("bossBack", getMemDC(), WINSIZEX / 2 - IMAGE->findImage("bossBack")->getWidth() / 2, 100);
		IMAGE->render("bossFront", getMemDC(), WINSIZEX / 2 - IMAGE->findImage("bossFront")->getWidth() / 2 + 14, 100 + 14,
			0, 0, IMAGE->findImage("bossFront")->getWidth() - minusHp, IMAGE->findImage("bossFront")->getHeight());
	}
}
