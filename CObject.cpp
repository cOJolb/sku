#include "framework.h"
#include "CObject.h"

CObject::CObject() : 
	pt({ 0, 0 }), rc(RectMakeCenter(0,0,0,0)),
	ani(nullptr) , shadowdistance(0)
{
}

CObject::CObject(Vec2 _pos, RECT _rc) :
	pt(_pos), rc(_rc),
	ani(nullptr), shadowdistance(0)
{
}

CObject::~CObject()
{
	//SAFE_DELETE(ani);
	SAFE_DELETE(collider);
	SAFE_DELETE(colliderShadow);
}

HRESULT CObject::init()
{
	pt = 0;
	rc = RectMake(0, 0, 0, 0);
	return S_OK;
}

HRESULT CObject::init(vector2 _pt, RECT _rc, vector2 _objectPt, vector2 _objectSize, float _shadowdistance, vector2 _objectShadowPt, vector2 _objectShadowSize)
{
	pt = _pt;
	rc = _rc;
	shadowdistance = _shadowdistance;
	collider = new CCollider(_objectPt, _objectSize);
	colliderShadow = new CCollider(_objectShadowPt, _objectShadowSize);
	return S_OK;
}

void CObject::release()
{
}

void CObject::update()
{
}

void CObject::render()
{
}
