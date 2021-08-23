#include "framework.h"
#include "CItem.h"
CItem::CItem()
{
}

CItem::~CItem()
{
}

HRESULT CItem::init()
{
	return E_NOTIMPL;
}

void CItem::release()
{
}

void CItem::update()
{
}

void CItem::render()
{
}
CHeart::CHeart()
{
}

CHeart::CHeart(vector2 _pt)
{
	rc = RectMakeCenter(_pt, 30, 30);
	CObject::init(_pt, rc, _pt, { 30 ,30 }, 5, { _pt.x , _pt.y + 5 }, { 30, 10 });
	type = ITEM_TYPE::ITEM_HEART;
}

CHeart::~CHeart()
{
}

HRESULT CHeart::init()
{
	return E_NOTIMPL;
}

void CHeart::release()
{
}

void CHeart::render()
{
	RECT rec = RectMakeCenter(getcollider()->getPos(), 30, 30);
	RECT recshadow = RectMakeCenter(GetcolliderShadow()->getPos(), 30, 10);
	
	IMAGE->render("itemshadow", getMemDC(), recshadow.left, recshadow.top);
	IMAGE->frameRender("heartitem", getMemDC(), rec.left, rec.top,0,0);
}
CCoin::CCoin()
{
}

CCoin::CCoin(vector2 _pt)
{
	rc = RectMakeCenter(_pt, 30, 30);
	CObject::init(_pt, rc, _pt, { 30 ,30 }, 5, { _pt.x , _pt.y + 5 }, { 30, 10 });
	type = ITEM_TYPE::ITEM_COIN;
	ani = ANIMATION->findAnimation("coinani");
	ANIMATION->start("coinani");
}

CCoin::~CCoin()
{
}

HRESULT CCoin::init()
{
	return E_NOTIMPL;
}

void CCoin::release()
{
}

void CCoin::render()
{
	RECT rec = RectMakeCenter(getcollider()->getPos(), 30, 30);
	RECT recshadow = RectMakeCenter(GetcolliderShadow()->getPos(), 30, 10);

	IMAGE->render("itemshadow", getMemDC(), recshadow.left, recshadow.top);
	IMAGE->findImage("coin")->aniRender(getMemDC(), rec.left, rec.top, ani);
}

CBomb::CBomb()
{
}

CBomb::CBomb(vector2 _pt)
{
	rc = RectMakeCenter(_pt, 30, 30);
	CObject::init(_pt, rc, _pt, { 30 ,30 }, 5, { _pt.x , _pt.y + 10 }, { 30, 10 });
	type = ITEM_TYPE::ITEM_BOMB;
}

CBomb::~CBomb()
{
}

HRESULT CBomb::init()
{
	return E_NOTIMPL;
}

void CBomb::release()
{
}

void CBomb::render()
{
	RECT rec = RectMakeCenter(getcollider()->getPos(), 45, 45);
	RECT recshadow = RectMakeCenter(GetcolliderShadow()->getPos(), 30, 10);
	
	IMAGE->render("itemshadow", getMemDC(), recshadow.left, recshadow.top);
	IMAGE->frameRender("bomb", getMemDC(), rec.left, rec.top, 0, 0);
}

CKey::CKey()
{
}

CKey::CKey(vector2 _pt)
{
	rc = RectMakeCenter(_pt, 30, 30);
	CObject::init(_pt, rc, _pt, { 30 ,30 }, 5, { _pt.x , _pt.y + 10 }, { 30, 10 });
	type = ITEM_TYPE::ITEM_KEY;
}

CKey::~CKey()
{
}

HRESULT CKey::init()
{
	return E_NOTIMPL;
}

void CKey::release()
{
}

void CKey::render()
{
	RECT rec = RectMakeCenter(getcollider()->getPos(), 45, 45);
	RECT recshadow = RectMakeCenter(GetcolliderShadow()->getPos(), 30, 10);

	IMAGE->render("itemshadow", getMemDC(), recshadow.left, recshadow.top);
	IMAGE->frameRender("key", getMemDC(), rec.left, rec.top, 0, 0);
}

CInnerEye::CInnerEye()
{
}

CInnerEye::CInnerEye(vector2 _pt)
{
	rc = RectMakeCenter(_pt, 60, 60);
	CObject::init(_pt, rc, _pt, { 60 ,60 }, 5, { _pt.x , _pt.y + 20 }, { 30, 10 });
	type = ITEM_TYPE::ITEM_THEINNEREYE;
}

CInnerEye::~CInnerEye()
{
}

HRESULT CInnerEye::init()
{
	return E_NOTIMPL;
}

void CInnerEye::release()
{
}

void CInnerEye::render()
{
	RECT rec = RectMakeCenter(getcollider()->getPos(), 60, 60);
	RECT recshadow = RectMakeCenter(GetcolliderShadow()->getPos(), 30, 10);

	IMAGE->render("itemshadow", getMemDC(), recshadow.left, recshadow.top);
	IMAGE->frameRender("passiveitem", getMemDC(), rec.left, rec.top, 0, 0);
}

CLipstick::CLipstick()
{
}

CLipstick::CLipstick(vector2 _pt)
{
	rc = RectMakeCenter(_pt, 30*2, 30*2);
	CObject::init(_pt, rc, _pt, { 60 ,60 }, 5, { _pt.x , _pt.y + 20 }, { 30, 10 });
	type = ITEM_TYPE::ITEM_MOMSLIPSTICK;
}

CLipstick::~CLipstick()
{
}

HRESULT CLipstick::init()
{
	return E_NOTIMPL;
}

void CLipstick::release()
{
}

void CLipstick::render()
{
	RECT rec = RectMakeCenter(getcollider()->getPos(), 60, 60);
	RECT recshadow = RectMakeCenter(GetcolliderShadow()->getPos(), 30, 10);

	IMAGE->render("itemshadow", getMemDC(), recshadow.left, recshadow.top);
	IMAGE->frameRender("passiveitem", getMemDC(), rec.left, rec.top, 1, 0);
}

CPentagram::CPentagram()
{
}

CPentagram::CPentagram(vector2 _pt)
{
	rc = RectMakeCenter(_pt, 60, 60);
	CObject::init(_pt, rc, _pt, { 60 ,60 }, 5, { _pt.x , _pt.y + 20 }, { 30, 10 });
	type = ITEM_TYPE::ITEM_PENTAGRAM;
}

CPentagram::~CPentagram()
{
}

HRESULT CPentagram::init()
{
	return E_NOTIMPL;
}

void CPentagram::release()
{
}

void CPentagram::render()
{
	RECT rec = RectMakeCenter(getcollider()->getPos(), 60, 60);
	RECT recshadow = RectMakeCenter(GetcolliderShadow()->getPos(), 30, 10);

	IMAGE->render("itemshadow", getMemDC(), recshadow.left, recshadow.top);
	IMAGE->frameRender("passiveitem", getMemDC(), rec.left, rec.top, 2, 0);
}

CBloodbag::CBloodbag()
{
}

CBloodbag::CBloodbag(vector2 _pt)
{
	rc = RectMakeCenter(_pt, 60, 60);
	CObject::init(_pt, rc, _pt, { 60 ,60 }, 5, { _pt.x , _pt.y + 20 }, { 30, 10 });
	type = ITEM_TYPE::ITEM_BLOODBAG;
}

CBloodbag::~CBloodbag()
{
}

HRESULT CBloodbag::init()
{
	return E_NOTIMPL;
}

void CBloodbag::release()
{
}

void CBloodbag::render()
{
	RECT rec = RectMakeCenter(getcollider()->getPos(), 60, 60);
	RECT recshadow = RectMakeCenter(GetcolliderShadow()->getPos(), 30, 10);

	IMAGE->render("itemshadow", getMemDC(), recshadow.left, recshadow.top);
	IMAGE->frameRender("passiveitem", getMemDC(), rec.left, rec.top, 3, 0);
}

CSpeedBall::CSpeedBall()
{
}

CSpeedBall::CSpeedBall(vector2 _pt)
{
	rc = RectMakeCenter(_pt, 60, 60);
	CObject::init(_pt, rc, _pt, { 60 ,60 }, 5, { _pt.x , _pt.y + 20 }, { 30, 10 });
	type = ITEM_TYPE::ITEM_SPEEDBALL;
}

CSpeedBall::~CSpeedBall()
{
}

HRESULT CSpeedBall::init()
{
	return E_NOTIMPL;
}

void CSpeedBall::release()
{
}

void CSpeedBall::render()
{
	RECT rec = RectMakeCenter(getcollider()->getPos(), 60, 60);
	RECT recshadow = RectMakeCenter(GetcolliderShadow()->getPos(), 30, 10);

	IMAGE->render("itemshadow", getMemDC(), recshadow.left, recshadow.top);
	IMAGE->frameRender("passiveitem", getMemDC(), rec.left, rec.top, 4, 0);
}
