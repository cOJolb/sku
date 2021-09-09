#include "framework.h"
#include "item.h"

C_item::C_item()
{

}

C_item::~C_item()
{
}

HRESULT C_item::init(C_player* _player)
{
	return S_OK;
}

void C_item::release(C_player* _player)
{
}

void C_item::update()
{
}

void C_item::update(C_player* _player)
{
}

void C_item::render()
{
}

void C_item::render(vector2 _pt)
{
}


