#include "pch.h"
#include "CUser.h"


CUser::CUser():
	m_nCurMotion(IDLE),
	m_nPrevMotion(IDLE),
	m_bLeft(0),
	m_nFrame(0),
	m_nAtkCnt(0),
	m_fAcc(0.f),
	m_fJump(0.f),
	m_fVZ(0.f)
{
	m_userBitmapSize.x = 132;
	m_userBitmapSize.y = 86;

	m_nEmpty = 38;

	m_posY = 300.f;
}

CUser::~CUser()
{

}

void CUser::DrawUpdate(HDC memDC, float DT)
{
	Control(DT);
	Motion(DT);

	float tmpY = m_posY - m_fVZ;	// 가상의 z좌표로 높이 설정

	if (m_bLeft) 
	{
		m_oldBit = (HBITMAP)SelectObject(stretchDC, m_objBit);
		StretchBlt(objDC,
			m_posX + m_userBitmapSize.x - 1,
			m_posY,
			-m_userBitmapSize.x,
			m_userBitmapSize.y,

			stretchDC,
			m_userBitmapSize.x * m_nFrame,
			m_userBitmapSize.y * m_nCurMotion,
			m_userBitmapSize.x,
			m_userBitmapSize.y, 
			SRCCOPY);
		SelectObject(stretchDC, m_oldBit);

		TransparentBlt(memDC,
			(m_posX < 0) ? m_posX + m_nEmpty : min(MAX_POSX, m_posX),
			tmpY,
			m_userBitmapSize.x - m_nEmpty,
			m_userBitmapSize.y,

			objDC,
			(m_posX < 0) ? m_posX + m_nEmpty : min(MAX_POSX, m_posX),
			m_posY,
			m_userBitmapSize.x - m_nEmpty,
			m_userBitmapSize.y,
			TCOLOR);
	}
	else
	{
		m_oldBit = (HBITMAP)SelectObject(objDC, m_objBit);
		TransparentBlt(memDC,
			m_posX,
			tmpY,
			m_userBitmapSize.x,
			m_userBitmapSize.y,

			objDC,
			m_userBitmapSize.x * m_nFrame,
			m_userBitmapSize.y * m_nCurMotion,
			m_userBitmapSize.x,
			m_userBitmapSize.y,
			TCOLOR);
		SelectObject(objDC, m_oldBit);
	}
}

void CUser::Control(float DT)
{
	// 일반 공격이면 모션이 끝날 때까지 다른 모션 없음
	if (m_nPrevMotion == ATTACK1 || m_nPrevMotion == ATTACK2 || m_nPrevMotion == ATTACK3) return;

	// RUNATTACK모션 아직 안 끝났으면 현재 모션은 RUNATTACK
	// JUMP모션이 끝났으면 아이들 모션, 이전 모션이 점프모션이면 현재 모션은 JUMP
	if (m_nPrevMotion == RUNATTACK)	m_nCurMotion = RUNATTACK;
	else if(m_nPrevMotion != JUMP)m_nCurMotion = IDLE;

	// 이동
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if(m_nPrevMotion == RUN || m_nPrevMotion == RUNATTACK)
			m_posX = min(MAX_POSX, m_posX + 300 * DT);
		else
			m_posX = min(MAX_POSX, m_posX + 200 * DT);
		
		m_bLeft = false;
		if (m_nCurMotion == IDLE && m_nPrevMotion != RUNATTACK && m_nPrevMotion != JUMP) 
			m_nCurMotion = WALK;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (m_nPrevMotion == RUN || m_nPrevMotion == RUNATTACK)
			m_posX = max(-m_nEmpty, m_posX - 300 * DT);
		else 
			m_posX = max(-m_nEmpty, m_posX - 200 * DT);

		m_bLeft = true;
		if (m_nCurMotion == IDLE && m_nPrevMotion != RUNATTACK && m_nPrevMotion != JUMP)
			m_nCurMotion = WALK;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (m_nPrevMotion == RUN || m_nPrevMotion == RUNATTACK)
			m_posY = max(ROAD - m_userBitmapSize.y, m_posY - 150 * DT);
		else
			m_posY = max(ROAD - m_userBitmapSize.y, m_posY - 100 * DT);
		
		if (m_nCurMotion == IDLE && m_nPrevMotion != RUNATTACK && m_nPrevMotion != JUMP)
			m_nCurMotion = WALK;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if (m_nPrevMotion == RUN|| m_nPrevMotion == RUNATTACK)
			m_posY = min(WINDOW_Y - m_userBitmapSize.y, m_posY + 150 * DT);
		else
			m_posY = min(WINDOW_Y - m_userBitmapSize.y, m_posY + 100 * DT);
		
		if (m_nCurMotion == IDLE && m_nPrevMotion != RUNATTACK && m_nPrevMotion != JUMP)
			m_nCurMotion = WALK;
	}

	// 달리기
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		if (m_nCurMotion == WALK && m_nPrevMotion != RUNATTACK && m_nPrevMotion != JUMP)
			m_nCurMotion = RUN;
	}

	// 공격
	if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
	{
		if(m_nCurMotion == RUN || m_nPrevMotion == RUNATTACK) m_nCurMotion = RUNATTACK;
		else if(m_nPrevMotion != JUMP) m_nCurMotion = ATTACK1;
	}

	// 점프
	if (GetAsyncKeyState(VK_MENU) & 0x8000)
	{
		m_nCurMotion = JUMP;
	}

}

void CUser::Motion(float DT)
{
	if (m_nPrevMotion != m_nCurMotion) 
	{
		m_nPrevMotion = m_nCurMotion;
		m_nFrame = 0;
		m_fAcc = 0.f;
	}

	m_fAcc += DT;	// DT누적

	switch (m_nCurMotion)
	{
	case IDLE:
		if (m_fAcc > 0.9f)
		{
			m_fAcc = 0.f;
			if (++m_nFrame == 4)
			{
				m_nFrame = 0;
			}
		}
		break;
	case WALK:
		if (m_fAcc > 0.1f)
		{
			m_fAcc = 0;
			if (++m_nFrame == 8)
			{
				m_nFrame = 0;
			}
		}
		break;
	case RUN:
		if (m_fAcc > 0.1f)
		{
			m_fAcc = 0;
			if (++m_nFrame == 7)
			{
				m_nFrame = 0;
			}
		}
		break;

	case ATTACK1:
	case ATTACK2:
	case ATTACK3:

		// 공격 모션 설정
		switch (m_nAtkCnt)
		{
		case 0:
			m_nCurMotion = ATTACK1;
			break;
		case 1:
			m_nCurMotion = ATTACK2;
			break;
		case 2:
			m_nCurMotion = ATTACK3;
			break;
		default:
			break;
		}

		if (m_fAcc > 0.1f)
		{
			m_fAcc = 0;
			m_nFrame++;

			if (m_nCurMotion == ATTACK1)
			{
				if (m_nFrame == 5)
				{
					m_nFrame = 0;
					m_nAtkCnt++;
					m_nPrevMotion = IDLE;
				}
			}
			else if(m_nCurMotion == ATTACK2)
			{
				if (m_nFrame == 4)
				{
					m_nFrame = 0;
					m_nAtkCnt++;
					m_nPrevMotion = IDLE;
				}
			}
			else
			{
				if (m_nFrame == 4)
				{
					m_nFrame = 0;
					m_nAtkCnt = 0;
					m_nPrevMotion = IDLE;
				}
			}
		}
		break;
	case RUNATTACK:
		if (m_fAcc > 0.1f)
		{
			m_fAcc = 0;
			if (++m_nFrame == 6)
			{
				m_nFrame = 0;
				m_nPrevMotion = IDLE;
			}
		}
		break;

	case JUMP:
		
		switch (m_nFrame)
		{
		case 0:
			m_fJump = JUMP_HEIGHT;
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			m_fVZ += m_fJump * DT;		// 가상의 z축 증가 -> 점프 높이 증가
			m_fJump -= GRAVITY * DT;	// 중력 * DT만큼 점프 높이 감소
			if (m_fVZ < 0.f) m_fVZ = 0.f;
			break;

		}

		if (m_fAcc > 0.1f)
		{
			m_fAcc = 0;
			if (++m_nFrame == 6)
			{
				m_nFrame = 0;
				m_nPrevMotion = IDLE;
			}
		}

		
		break;
	default:
		break;
	}
}