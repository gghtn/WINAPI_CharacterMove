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
	// 현재 카운트
	QueryPerformanceCounter(&_curCount);
	// 초당 카운트 횟수
	QueryPerformanceFrequency(&_frequency);
	// 종료 카운트 초기화
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
