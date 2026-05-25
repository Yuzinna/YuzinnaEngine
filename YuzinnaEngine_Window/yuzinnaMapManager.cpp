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
		mMaps[4] = {
			L"fiw...................",
			L"biy...................",
			L"......................",
			L".............SSSSSSSSS",
			L".............S.......S",
			L"..rip........S.u.....S",
			L".............S.i.....S",
			L".....S.S.....S.d.....S",
			L".....SRS.....S.......S",
			L"...SSSRSSS...S.......S",
			L"...S..R..S...S....F..S",
			L"...S.....S...S.......S",
			L"...S..B..S...SSSSSSSSS",
			L"...S.....S............",
			
		};
		mMaps[5] = {
			L"......................",
			L"......................",
			L"..WWWWWWWWWWWWWW......",
			L"..W....R.......W......",
			L"..W.biy......F.W......",
			L"..WR......R....W......",
			L"..W........R.R.W......",
			L"..W...B..R..R.RW.....r",
			L"..WR.....R.f.w.W.....i",
			L"..W.R....R..R..W.....s",
			L"..W....R..R....W......",
			L"..WWWWWWWWWWWWWW......",
			L"......................",
			L"......................",
			
		};
		mMaps[6] = {
			L".WWWWW.......WWWWW....",
			L".WbiyW.......WeisW....",
			L".WWWWW.......WWWWW....",
			L".WaisW.......WeihW....",
			L".WWWWWWW....WWWWWWW...",
			L".W.....W....W.....W...",
			L".W.K.B.D.RK.D..r..W...",
			L".W.....W....W.....W...",
			L".WWWWWWW....WWWDWWW...",
			L"............W....W....",
			L".....kio....W..F.W....",
			L".....i......WW...W....",
			L".....p.......WfiwW....",
			L".............WWWWW....",
			
		};
		mMaps[7] = {
			L"W.biy.W.........",
			L"W.eis.W.........",
			L"W.ais.W.........",
			L"WWWWWWWWWWWWWWWW",
			L"W.....W........W",
			L"W.....W........W",
			L"W.kio.W........W",
			L"W.....W...eih..W",
			L"W.k.p.W........W",
			L"W.B...D........W",
			L"W.K...W........W",
			L"W.....WWWWWDWWWW",
			L"W.....W.........",
			L"WWWWWWW....F....",
			L"................",
			L"..........fiw...",
			
		};
		
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
			if (mMaxUnlockedStage > 8) mMaxUnlockedStage = 8;
		}
	}
}
