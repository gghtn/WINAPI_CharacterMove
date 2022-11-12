#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER _curCount;
	LARGE_INTEGER _frequency;
	LARGE_INTEGER _endCount;
	float DeltaTime;
	float Acc;
public:
	void Init();
	void Update();

	float GetDeltaTime() { return DeltaTime; }
	float GetAcc() { return Acc; }

	void SetAcc() { Acc = 0.f; }
};

