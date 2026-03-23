#pragma once
#include "..\\YuzinnaEngine_SOURCE\\CommonInclude.h"
#include <vector>
#include <string>

namespace yuzinna
{
	class MapLoader
	{
	public:
		// 문자열 배열을 받아 실제 오브젝트들을 생성합니다.
		static void LoadMap(const std::vector<std::wstring>& mapData);
	};
}
