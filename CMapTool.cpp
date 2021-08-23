#include "framework.h"
#include "CMapSetting.h"
#include "CMapSettingSub.h"
#include "CMap.h"
#include "CMapTool.h"

CMapTool::CMapTool()
{
}

CMapTool::~CMapTool()
{
}

HRESULT CMapTool::init()
{
	SUBWIN->init();
	mapSet = new CMapSetting;
	mapSet->init();
	SUBWIN->SetScene(new CMapSettingSub);
	SUBWIN->SetMapLink(mapSet);
	return S_OK;
}

void CMapTool::release()
{
}

void CMapTool::update()
{
	SUBWIN->update();
	mapSet->update();
}

void CMapTool::render()
{
	SUBWIN->render();
	mapSet->render();
}
