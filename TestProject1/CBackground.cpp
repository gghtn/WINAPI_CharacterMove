#include "pch.h"
#include "CBackground.h"

CBackground::CBackground():
	m_size{}
{

}

CBackground::~CBackground()
{

}


void CBackground::DrawUpdate(HDC memDC, float DT)
{
	int userPosX = max(0, CUser::GetInst()->GetPosX());
	int backBitPosX = min(userPosX - WINDOW_X/2, m_size.bmWidth - WINDOW_X);		

	GetObject(m_objBit, sizeof(BITMAP), &m_size);
	m_oldBit = (HBITMAP)SelectObject(objDC, m_objBit);
	BitBlt(memDC,
		m_posX, m_posY, m_size.bmWidth, m_size.bmHeight,
		objDC,
		(userPosX > WINDOW_X/2)? backBitPosX : 0, 0,
		SRCCOPY);
	SelectObject(objDC, m_oldBit);
}
