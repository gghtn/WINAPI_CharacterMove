#pragma once


class CCore
{
	SINGLE(CCore);
private:
	HWND	hWnd;
	POINT	m_ptResolution;
	HDC		hdc;

	HDC		memDC;
	HBITMAP	bit;

private:
	void Update();
	void Render();

public:
	void Init(HWND _hWnd, POINT resolution);
	void Progress();
};

