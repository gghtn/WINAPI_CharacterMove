#pragma once

class CObject
{
protected:
	HDC			objDC;			// memDC�� ������ dc
	HDC			stretchDC;		// �¿� ������ objDC�� �׸� dc
	float		m_posX, m_posY;
	HBITMAP		m_oldBit;
	HBITMAP		m_objBit;
	HBITMAP		bit;			// objDC ��Ʈ���� �ٲ��� HBITMAP
public:
	CObject();
	virtual ~CObject();
	virtual void DrawUpdate(HDC memDC, float DT = 0.f) = 0;

	void Init(HDC memDC, const char* path);

	// ��Ʈ�� �ε�
	void LoadBitmap(HDC memDC, const char* p);
	// DDB��ȯ
	HBITMAP MakeDDB(HDC hdc, const char* Path);

	float GetPosX() { return m_posX; }
};

