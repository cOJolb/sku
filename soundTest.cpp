#include "framework.h"
#include "soundTest.h"

soundTest::soundTest()
{
}

soundTest::~soundTest()
{
}

HRESULT soundTest::init()
{

    SOUND->addSound("카드", "sound/체리.mp3", true, true);
    return S_OK;
}

void soundTest::release()
{
}

void soundTest::update()
{
    if (InputManager->isOnceKeyDown('Q'))
    {
        SOUND->play("카드",1.0f);
    }
    if (InputManager->isOnceKeyDown('S'))
    {
        SOUND->stop("카드");
    }
    if (InputManager->isOnceKeyDown('T'))
    {
        SOUND->resume("카드");
    }
    if (InputManager->isOnceKeyDown('P'))
    {
        SOUND->pause("카드");
    }
}
