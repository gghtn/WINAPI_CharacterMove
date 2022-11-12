#pragma once
#include "CObject.h"
#include "CUser.h"

class CBackground : public CObject 
{
	SINGLE(CBackground);
private:
	BITMAP	m_size;
public:
	void DrawUpdate(HDC memDC, float DT = 0.f);
};

