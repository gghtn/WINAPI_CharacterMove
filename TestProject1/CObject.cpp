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
	// DC 생성, 비트맵 로드
	objDC = CreateCompatibleDC(memDC);
	stretchDC = CreateCompatibleDC(memDC);

	// objDC의 기본 비트맵 사이즈를 바꿔준다.
	// CUser 클래스에서 StretchBlt 사용시 objDC가 비트맵을 선택하지 않기 때문
	bit = CreateCompatibleBitmap(memDC, WINDOW_X, WINDOW_Y);
	tmpBit = (HBITMAP)SelectObject(objDC, bit);
	DeleteObject(tmpBit);

	LoadBitmap(memDC, path);	// m_objBit에 비트맵 로드
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

	//// 파일을 연다
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

	//// DDB로 변환한다.
	hBit = CreateDIBitmap(hdc,						// hdc
		iheader,					// BITMAPINFOHEADER 헤더
		CBM_INIT,					// 0 또는 CBM_INIT ( 초기화 )
		lpMemBlock + fh->bfOffBits,	// 래스터 어드래스
		ih,							// BITMAPINFO 헤더
		DIB_RGB_COLORS);

	free(lpMemBlock);

	return hBit;
}
