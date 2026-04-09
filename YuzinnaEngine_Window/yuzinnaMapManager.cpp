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
			L"biy..........fiw",
			L"................",
			L"WWWWWWWWWWWWWWWW",
			L".......R........",
			L".B.....R......F.",
			L".......R........",
			L"WWWWWWWWWWWWWWWW",
			L"................",
			L"................",
			L"ais..........rip",
		};
		// [Stage 1]
		mMaps[1] = {
			L"....WWWWWWWW",
			L"....W......W",
			L"....W.i....W",
			L"....W......W",
			L"WWWWW....w.W",
			L"W..........W",
			L"W.f...F....W",
			L"W..........W",
			L"WWWWWWWWWWWW",
			L"....W......W",
			L".b..W.a....W",
			L".i..W.i..B.W",
			L".y..W.s....W",
			L"....W......W",
			L"....WWWWWWWW",
			
		};
		// [Stage 2]
		mMaps[2] = {
			L"....FFFFFFFF",
			L"....F......F",
			L"....F.i....F",
			L"....F......F",
			L"FFFFF....w.F",
			L"F..........F",
			L"F.b........F",
			L"F..........F",
			L"FFFFFFFFFFFF",
			L"....F......F",
			L".a..F.f....F",
			L".i..F.i..W.F",
			L".y..F.s....F",
			L"....F...FFFF",
			L"....FFFFF...",
			
		};
		mMaps[3] = {
			L"baW...............",
			L"iiW....WWWWWWWW...",
			L"ysW....W......W...",
			L"WWW....W.B..R.W...",
			L"......tW......W...",
			L"......iW....R.W...",
			L"......vW......W...",
			L"....WWWWOOOWWWWWWW",
			L"....W......W.....W",
			L"....W......W.rip.W",
			L"....W......W.....W",
			L"....WOOO.W.......W",
			L"....WOOO...W.fiw.W",
			L"....WFOO...W.....W",
			L"....WWWWWWWWWWWWWW",
			
		};

		// [Stage 1~5] (임시 데이터 추가)
		for (int i = 4; i <= 5; ++i)
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
