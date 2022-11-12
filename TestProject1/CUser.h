#pragma once
#include "CObject.h"

class CUser: public CObject
{
	SINGLE(CUser);
private:
	void Control(float DT);
	void Motion(float DT);

private:
	POINT	m_userBitmapSize;	// ��Ʈ�� ��� ������
	int		m_nEmpty;			// ��Ʈ�� ĳ���� �� ����
	int		m_nCurMotion;		// ���� ���
	int		m_nPrevMotion;		// ���� ���
	int		m_nFrame;			// ����� ������
	int		m_nAtkCnt;			// ���� ��� ��ȣ

	float	m_fAcc;				// DeltaTime ����
	float	m_fJump;			// 1�ʰ� ���� ����
	float	m_fVZ;				// ���� ���� ����

	bool	m_bLeft;			// ĳ���� ������ �������� Ȯ��

public:
	void DrawUpdate(HDC memDC, float DT = 0.f);
};