#pragma once
#include "..\\YuzinnaEngine_SOURCE\\CommonInclude.h"
#include <vector>
#include <string>
#include <map>

namespace yuzinna
{
	class MapManager
	{
	public:
		static void Initialize();
		static std::vector<std::wstring> GetMap(int stageNum);
		
		static void SetCurrentStage(int stage) { mCurrentStage = stage; }
		static int GetCurrentStage() { return mCurrentStage; }

		static int GetMaxUnlockedStage() { return mMaxUnlockedStage; }
		static void UnlockNextStage();

	private:
		static std::map<int, std::vector<std::wstring>> mMaps;
		static int mCurrentStage;
		static int mMaxUnlockedStage;
	};
}
