#include "framework.h"
#include "stage1_1.h"

stage1_1::stage1_1()
{
}

stage1_1::~stage1_1()
{
}

HRESULT stage1_1::init()
{
    stageScene::init();
    return S_OK;
}

void stage1_1::release()
{
    stageScene::release();
}

void stage1_1::update()
{
    stageScene::update();
}

void stage1_1::render()
{
    stageScene::render();
}
