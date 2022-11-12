#pragma once

class CObject
{
protected:
	HDC			objDC;			// memDC에 복사할 dc
	HDC			stretchDC;		// 좌우 반전을 objDC에 그릴 dc
	float		m_posX, m_posY;
	HBITMAP		m_oldBit;
	HBITMAP		m_objBit;
	HBITMAP		bit;			// objDC 비트맵을 바꿔줄 HBITMAP
public:
	CObject();
	virtual ~CObject();
	virtual void DrawUpdate(HDC memDC, float DT = 0.f) = 0;

	void Init(HDC memDC, const char* path);

	// 비트맵 로드
	void LoadBitmap(HDC memDC, const char* p);
	// DDB변환
	HBITMAP MakeDDB(HDC hdc, const char* Path);

	float GetPosX() { return m_posX; }
};

