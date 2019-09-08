#pragma once
#include "CircusObject.h"
class FireJar :
	public CircusObject
{
private:
	static int	m_sFireJarNumber;
	int			miThisNumber;
	POINT		m_Pos;
	BitMap*		m_pBitMap;
public:
	virtual void Init();
	virtual void Input(WPARAM wParam);
	virtual void TerminateInput(WPARAM wParam);
	virtual void Update();
	virtual void Draw(HDC hdc);
	virtual void Release();
public:
	virtual RECT GetCollisonBox();
	virtual void ReStart();
	inline virtual OBJECT_TAG GetTag()
	{
		return TAG_FIRERING;
	}
public:
	FireJar();
	virtual ~FireJar();
};

