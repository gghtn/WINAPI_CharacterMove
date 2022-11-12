#include "pch.h"
#include "CObject.h"

CObject::CObject():
	objDC(0),
	stretchDC(0),
	m_posX(0),
	m_posY(0),
	m_objBit(0),
	m_oldBit(0)
{

}

CObject::~CObject()
{
	DeleteDC(objDC);
	DeleteDC(stretchDC);
	DeleteObject(m_objBit);
	DeleteObject(bit);
}

void CObject::Init(HDC memDC, const char* path)
{
	HBITMAP		tmpBit;
	// DC ����, ��Ʈ�� �ε�
	objDC = CreateCompatibleDC(memDC);
	stretchDC = CreateCompatibleDC(memDC);

	// objDC�� �⺻ ��Ʈ�� ����� �ٲ��ش�.
	// CUser Ŭ�������� StretchBlt ���� objDC�� ��Ʈ���� �������� �ʱ� ����
	bit = CreateCompatibleBitmap(memDC, WINDOW_X, WINDOW_Y);
	tmpBit = (HBITMAP)SelectObject(objDC, bit);
	DeleteObject(tmpBit);

	LoadBitmap(memDC, path);	// m_objBit�� ��Ʈ�� �ε�
}

void CObject::LoadBitmap(HDC memDC, const char* p)
{
	char path[255];

	memset(path, '\0', 255);
	GetCurrentDirectory(255, path); 
	strcat(path, p);
	m_objBit = MakeDDB(memDC, path);
}

HBITMAP CObject::MakeDDB(HDC hdc, const char* Path)
{
	HANDLE  hFile;
	DWORD   FileSize, dwRead;
	HBITMAP hBit;
	BITMAPFILEHEADER* fh;
	BITMAPINFO* ih;
	BITMAPINFOHEADER* iheader;
	LPBYTE			 lpMemBlock;

	//// ������ ����
	hFile = CreateFile(Path, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE) {
		return NULL;
	}

	FileSize = GetFileSize(hFile, NULL);

	lpMemBlock = (LPBYTE)malloc(FileSize);
	fh = (BITMAPFILEHEADER*)lpMemBlock;
	ReadFile(hFile, lpMemBlock, FileSize, &dwRead, NULL);
	CloseHandle(hFile);

	ih = (BITMAPINFO*)(lpMemBlock + sizeof(BITMAPFILEHEADER));
	iheader = (BITMAPINFOHEADER*)(lpMemBlock + sizeof(BITMAPFILEHEADER));

	//// DDB�� ��ȯ�Ѵ�.
	hBit = CreateDIBitmap(hdc,						// hdc
		iheader,					// BITMAPINFOHEADER ���
		CBM_INIT,					// 0 �Ǵ� CBM_INIT ( �ʱ�ȭ )
		lpMemBlock + fh->bfOffBits,	// ������ ��巡��
		ih,							// BITMAPINFO ���
		DIB_RGB_COLORS);

	free(lpMemBlock);

	return hBit;
}
