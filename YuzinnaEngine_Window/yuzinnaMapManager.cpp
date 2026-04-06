#include "yuzinnaMapManager.h"

namespace yuzinna
{
	std::map<int, std::vector<std::wstring>> MapManager::mMaps = {};
	int MapManager::mCurrentStage = 0;
	int MapManager::mMaxUnlockedStage = 0; // 초기 해금된 스테이지 0번

	void MapManager::Initialize()
	{
		// [Stage 0]
		mMaps[0] = {
			L"WWWWWWWWWWWWWWWW",
			L"W..............W",
			L"W....B....kis..W",
			L"W..............W",
			L"WWWWWWWWWWWWWWWW",
			L".......F........",
			L"......biy....fin"
		};

		// [Stage 1~5] (임시 데이터 추가)
		for (int i = 1; i <= 5; ++i)
		{
			mMaps[i] = mMaps[0];
		}
	}

	std::vector<std::wstring> MapManager::GetMap(int stageNum)
	{
		auto it = mMaps.find(stageNum);
		if (it != mMaps.end()) return it->second;
		return mMaps[0];
	}

	void MapManager::UnlockNextStage()
	{
		// 현재 진행 중인 스테이지가 가장 최근에 열린 스테이지라면 다음 스테이지 해금
		if (mCurrentStage == mMaxUnlockedStage)
		{
			mMaxUnlockedStage++;
			if (mMaxUnlockedStage > 5) mMaxUnlockedStage = 5;
		}
	}
}
