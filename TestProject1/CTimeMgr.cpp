#include "pch.h"
#include "CTimeMgr.h"


CTimeMgr::CTimeMgr():
	_curCount{},
	_frequency{},
	_endCount{},
	DeltaTime(0.f),
	Acc(0.f)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::Init()
{
	// ���� ī��Ʈ
	QueryPerformanceCounter(&_curCount);
	// �ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&_frequency);
	// ���� ī��Ʈ �ʱ�ȭ
	QueryPerformanceCounter(&_endCount);
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&_endCount);

	DeltaTime = (float)((_endCount.QuadPart - _curCount.QuadPart) / (float)_frequency.QuadPart);
	_curCount.QuadPart = _endCount.QuadPart;

	Acc += DeltaTime;
	if (Acc > 1.f)
	{
		Acc = 0.0f;
	}
}
