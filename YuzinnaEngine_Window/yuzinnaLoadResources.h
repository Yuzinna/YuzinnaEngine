#pragma once
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaResources.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaTexture.h"

namespace yuzinna
{
	void LoadResources()
	{
		Resources::Load<graphics::Texture>(L"Cat", L"..\\Resources\\ChickenAlpha.bmp");
		Resources::Load<graphics::Texture>(L"Player", L"..\\Resources\\Player.bmp");
		Resources::Load<graphics::Texture>(L"SpringFloor", L"..\\Resources\\SpringFloor.bmp");

		// Baba 캐릭터 이미지 (4방향 시트)
		Resources::Load<graphics::Texture>(L"BabaUp", L"..\\Resources\\Baba\\babaUp.png");
		Resources::Load<graphics::Texture>(L"BabaDown", L"..\\Resources\\Baba\\babaDown.png");
		Resources::Load<graphics::Texture>(L"BabaLeft", L"..\\Resources\\Baba\\babaLeft.png");
		Resources::Load<graphics::Texture>(L"BabaRight", L"..\\Resources\\Baba\\babaRight.png");

		// 단어 블록 이미지 (Baba, Is, You - On/Off 상태별)
		Resources::Load<graphics::Texture>(L"BabaOffWord", L"..\\Resources\\Baba\\Word\\BabaOffWord.png");
		Resources::Load<graphics::Texture>(L"BabaOnWord", L"..\\Resources\\Baba\\Word\\BabaOnWord.png");
		Resources::Load<graphics::Texture>(L"IsOffWord", L"..\\Resources\\Baba\\Word\\IsOffWord.png");
		Resources::Load<graphics::Texture>(L"IsOnWord", L"..\\Resources\\Baba\\Word\\IsOnWord.png");
		Resources::Load<graphics::Texture>(L"YouOffWord",  L"..\\Resources\\Baba\\Word\\YouOffWord.png");
		Resources::Load<graphics::Texture>(L"YouOnWord",   L"..\\Resources\\Baba\\Word\\YouOnWord.png");

		// 추가 단어 (Flag, Win, Stop, Push, Wall 등)
		Resources::Load<graphics::Texture>(L"FlagOffWord", L"..\\Resources\\Baba\\Word\\FlagOffWord.png");
		Resources::Load<graphics::Texture>(L"FlagOnWord",  L"..\\Resources\\Baba\\Word\\FlagOnWord.png");
		Resources::Load<graphics::Texture>(L"WinOffWord",  L"..\\Resources\\Baba\\Word\\WinOffWord.png");
		Resources::Load<graphics::Texture>(L"WinOnWord",   L"..\\Resources\\Baba\\Word\\WinOnWord.png");
		Resources::Load<graphics::Texture>(L"StopOffWord", L"..\\Resources\\Baba\\Word\\StopOffWord.png");
		Resources::Load<graphics::Texture>(L"StopOnWord",  L"..\\Resources\\Baba\\Word\\StopOnWord.png");
		Resources::Load<graphics::Texture>(L"PushOffWord", L"..\\Resources\\Baba\\Word\\PushOffWord.png");
		Resources::Load<graphics::Texture>(L"PushOnWord",  L"..\\Resources\\Baba\\Word\\PushOnWord.png");
		Resources::Load<graphics::Texture>(L"SinkOffWord", L"..\\Resources\\Baba\\Word\\SinkOffWord.png");
		Resources::Load<graphics::Texture>(L"SinkOnWord",  L"..\\Resources\\Baba\\Word\\SinkOnWord.png");
		Resources::Load<graphics::Texture>(L"WallOffWord", L"..\\Resources\\Baba\\Word\\WallOffWord.png"); 
		Resources::Load<graphics::Texture>(L"WallOnWord",  L"..\\Resources\\Baba\\Word\\WallOnWord.png");

		// 추가 단어 (Rock, Key, Skull - On/Off 상태별)
		Resources::Load<graphics::Texture>(L"RockOffWord", L"..\\Resources\\Baba\\Word\\RockOffWord.png");
		Resources::Load<graphics::Texture>(L"RockOnWord",  L"..\\Resources\\Baba\\Word\\RockOnWord.png");
		Resources::Load<graphics::Texture>(L"KeyOffWord",  L"..\\Resources\\Baba\\Word\\KeyOffWord.png");
		Resources::Load<graphics::Texture>(L"KeyOnWord",   L"..\\Resources\\Baba\\Word\\KeyOnWord.png");
		Resources::Load<graphics::Texture>(L"SkullOffWord",L"..\\Resources\\Baba\\Word\\SkullOffWord.png");
		Resources::Load<graphics::Texture>(L"SkullOnWord", L"..\\Resources\\Baba\\Word\\SkullOnWord.png");
		Resources::Load<graphics::Texture>(L"WaterOffWord",L"..\\Resources\\Baba\\Word\\WaterOffWord.png");
		Resources::Load<graphics::Texture>(L"WaterOnWord", L"..\\Resources\\Baba\\Word\\WaterOnWord.png");

		// 깃발 및 기타 오브젝트 이미지
		Resources::Load<graphics::Texture>(L"Flag", L"..\\Resources\\Baba\\Flag.png");
		Resources::Load<graphics::Texture>(L"Key",  L"..\\Resources\\Baba\\Key.png");
		Resources::Load<graphics::Texture>(L"Rock", L"..\\Resources\\Baba\\Rock.png");
		Resources::Load<graphics::Texture>(L"Skull",L"..\\Resources\\Baba\\Skull.png");

		// 월드맵 및 스테이지 아이콘
		Resources::Load<graphics::Texture>(L"WorldMap", L"..\\Resources\\Baba\\Map\\Map.png");
		Resources::Load<graphics::Texture>(L"WorldCursor", L"..\\Resources\\Baba\\Map\\Cursor.png");

		for (int i = 0; i <= 5; ++i)
		{
			std::wstring stageKey = L"StageIcon_" + std::to_wstring(i);
			std::wstring stagePath = L"..\\Resources\\Baba\\Map\\Stage" + std::to_wstring(i) + L".png";
			Resources::Load<graphics::Texture>(stageKey, stagePath);

			std::wstring clearedKey = L"StageIcon_" + std::to_wstring(i) + L"_Cleared";
			std::wstring clearedPath = L"..\\Resources\\Baba\\Map\\Stage" + std::to_wstring(i) + L"Cleared.png";
			// Stage 2는 오타(Cleard)가 있을 수 있으니 예외 처리
			if (i == 2) clearedPath = L"..\\Resources\\Baba\\Map\\Stage2Cleard.png";
			Resources::Load<graphics::Texture>(clearedKey, clearedPath);
		}

		// 벽 및 물 이미지 (0~15번 비트마스킹용)
		for (int i = 0; i <= 15; ++i)
		{
			std::wstring wallKey = L"Wall_" + std::to_wstring(i);
			std::wstring wallPath = L"..\\Resources\\Baba\\Wall\\Wall_" + std::to_wstring(i) + L".png";
			Resources::Load<graphics::Texture>(wallKey, wallPath);

			std::wstring waterKey = L"Water_" + std::to_wstring(i);
			std::wstring waterPath = L"..\\Resources\\Baba\\Water\\Water_" + std::to_wstring(i) + L".png";
			Resources::Load<graphics::Texture>(waterKey, waterPath);
		}
		}

}
