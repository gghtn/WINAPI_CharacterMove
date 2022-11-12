#pragma once
#include "CObject.h"

class CUser: public CObject
{
	SINGLE(CUser);
private:
	void Control(float DT);
	void Motion(float DT);

private:
	POINT	m_userBitmapSize;	// 비트맵 모션 사이즈
	int		m_nEmpty;			// 비트맵 캐릭터 뒤 여백
	int		m_nCurMotion;		// 현재 모션
	int		m_nPrevMotion;		// 이전 모션
	int		m_nFrame;			// 모션의 프레임
	int		m_nAtkCnt;			// 공격 모션 번호

	float	m_fAcc;				// DeltaTime 누적
	float	m_fJump;			// 1초간 점프 높이
	float	m_fVZ;				// 가상 점프 높이

	bool	m_bLeft;			// 캐릭터 방향이 왼쪽인지 확인

public:
	void DrawUpdate(HDC memDC, float DT = 0.f);
};