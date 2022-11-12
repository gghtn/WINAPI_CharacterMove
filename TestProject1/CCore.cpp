#include "pch.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CBackground.h"
#include "CUser.h"

CCore::CCore():
	hWnd(0),
	m_ptResolution{},
	hdc(0),
	memDC(0),
	bit(0)
{

}

CCore::~CCore()
{
	ReleaseDC(hWnd, hdc);
	DeleteObject(bit);
	DeleteDC(memDC);
}

void CCore::Update()
{
	CTimeMgr::GetInst()->Update();
}

void CCore::Render()
{
	CBackground::GetInst()->DrawUpdate(memDC);
	CUser::GetInst()->DrawUpdate(memDC, CTimeMgr::GetInst()->GetDeltaTime());

	BitBlt(hdc,
		0, 0, m_ptResolution.x, m_ptResolution.y,
		memDC,
		0, 0,
		SRCCOPY);
}

void CCore::Init(HWND _hWnd, POINT resolution)
{
	hWnd = _hWnd;
	m_ptResolution = resolution;
	// ���ϴ� �ػ� (Ŭ���̾�Ʈ â)
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	// ���ϴ� �ػ󵵸� ���߱� ���� �������� ��ü ũ��� rt �缳��
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);
	// ������â �缳��
	SetWindowPos(hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	hdc = GetDC(hWnd);

	// ���ۿ� ��Ʈ���� ����� ��Ʈ�� ����� ����
	bit = CreateCompatibleBitmap(hdc, resolution.x, resolution.y);
	memDC = CreateCompatibleDC(hdc);
	HBITMAP oldBit = (HBITMAP)SelectObject(memDC, bit);
	DeleteObject(oldBit);

	// ��� �ʱ�ȭ 
	CBackground::GetInst()->Init(memDC, "\\Background\\1.bmp");
	// ���� ĳ���� �ʱ�ȭ
	CUser::GetInst()->Init(memDC, "\\Motion\\allmotion.bmp");
}

void CCore::Progress()
{
	Update();
	Render();
}
