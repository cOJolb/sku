#include "framework.h"
#include "CUI.h"

CUI::CUI()/* : 
    CObject()*/
{
}

CUI::CUI(vector2 _pt, RECT _rc) /*:
    CObject(_pt, _rc)*/
{
    //collider = new CCollider({ 0, 0 }, { 0, 0 });
    //colliderShadow = new CCollider({ 0, 0 }, { 0, 0 });
}

CUI::~CUI()
{
}

HRESULT CUI::init()
{
    return S_OK;
}

void CUI::release()
{
}

void CUI::update()
{
}

void CUI::render()
{
}
