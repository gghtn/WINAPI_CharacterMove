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
	// 원하는 해상도 (클라이언트 창)
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	// 원하는 해상도를 맞추기 위한 윈도우의 전체 크기로 rt 재설정
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);
	// 윈도우창 재설정
	SetWindowPos(hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	hdc = GetDC(hWnd);

	// 버퍼용 비트맵을 만들고 비트맵 사이즈를 설정
	bit = CreateCompatibleBitmap(hdc, resolution.x, resolution.y);
	memDC = CreateCompatibleDC(hdc);
	HBITMAP oldBit = (HBITMAP)SelectObject(memDC, bit);
	DeleteObject(oldBit);

	// 배경 초기화 
	CBackground::GetInst()->Init(memDC, "\\Background\\1.bmp");
	// 유저 캐릭터 초기화
	CUser::GetInst()->Init(memDC, "\\Motion\\allmotion.bmp");
}

void CCore::Progress()
{
	Update();
	Render();
}
