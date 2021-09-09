#pragma once
#include"singleton.h"
class playerUI : public Singleton<playerUI>
{
private:
	int NowHp;
public:
	playerUI();
	~playerUI();

public:
	void render(HDC hdc);
};

