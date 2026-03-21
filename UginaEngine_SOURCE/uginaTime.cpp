#include "uginaTime.h"


namespace ugina
{
	//컴퓨터 cpu의 고유진동수
	LARGE_INTEGER Time::CpuFrequency = {};
	//이전 프레잉에 측정한 진동수
	LARGE_INTEGER Time::PrevFrequency = {};
	//이전 프레잉에 현재 진동수
	LARGE_INTEGER Time::CurrentFrequency = {};
	float Time::DeltaTimeValue = 0.0f;
	float Time::displayFps = 0.0f;

	void Time::Initailize()
	{
		//cpu의 고유진동수(초당 카운트수)를 매개변수에 반환해주는 함수(cpu의 클럭과는 다름)
		QueryPerformanceFrequency(&CpuFrequency);
		//시스템이 부팅된 이후부터 증가하는 카운트수를 반환(이 카운트수는QueryPerformanceFrequency가 반환해주는 초당 카운트수에 의해 증가함)

		//처음 잰 카운트 수
		QueryPerformanceCounter(&PrevFrequency);
	}

	void Time::Update()
	{
		//이후에 잰 현재 카운트수
		QueryPerformanceCounter(&CurrentFrequency);

		//현재 카운트 수 와 이전 카운트 수의 차 = 이전 프레임에서 현재 프레임까지의 진동수(카운트 수)
		float differenceFrequency 
			= static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart);
		//이전 프레임에서 현재 프레임까지의 진동수 에서 초당 진동수로 나누기=이전 프레임에서 현재 프레임까지 걸린 시간
		DeltaTimeValue = differenceFrequency / static_cast<float>(CpuFrequency.QuadPart);

		//현재 진동수는 이제 다음 프레임의 이전 진동수가 됨
		PrevFrequency.QuadPart = CurrentFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		//static float time = 0.0f;

		//time += DeltaTime();
		//wchar_t str[50] = L"";

		//float Fps = 1.0f / DeltaTime();
		//
		//swprintf_s(str, L"Fps : %f", displayFps);
		//int len = wcsnlen_s(str, 50);
		//if (time > 1.0)
		//{
		//	//초당 프레임수
		//	displayFps = Fps;
		//	time = 0.0;
		//}
		//
		//TextOut(hdc, 0, 0, str, len);

		//
		static float time = 0.0f;

		time += DeltaTimeValue;
		float fps = 1.0f / DeltaTimeValue;

		wchar_t str[50] = L"";
		swprintf_s(str, 50, L"Time : %d", (int)fps);
		int len = wcsnlen_s(str, 50);

		TextOut(hdc, 0, 0, str, len);
	}

}
