#pragma once
//이곳은 자주 사용되는 STL과 헤더를 모아놓기
#include <Windows.h>
#include <assert.h>

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <bitset>
#include <functional>
#include <filesystem>


#pragma comment(lib,"Msimg32.lib")
//Windows 멀티미디어 API(Multimedia API), 오디오, midi,타이머,조이스틱
#include <mmsystem.h>
//mmsystem.h을 사용하기위한 라이브러리
#pragma comment(lib, "winmm.lib")

#include <dinput.h>

//고급 그래픽처리를 위한 api헤더
#include <gdiplus.h>
//gdiplus.h을 사용하기위한 라이브러리
#pragma comment(lib,"gdiplus.lib")

#include "uginaEnums.h"
#include "uginaMath.h"