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
		Resources::Load<graphics::Texture>(L"WallOffWord", L"..\\Resources\\Baba\\Word\\WallOffWord.png"); 
		Resources::Load<graphics::Texture>(L"WallOnWord",  L"..\\Resources\\Baba\\Word\\WallOnWord.png");

		// 깃발 자체 이미지
		Resources::Load<graphics::Texture>(L"Flag", L"..\\Resources\\Baba\\Flag.png");

		// 벽 이미지 (0~15번 비트마스킹용)
		for (int i = 0; i <= 15; ++i)
		{
			std::wstring key = L"Wall_" + std::to_wstring(i);
			std::wstring path = L"..\\Resources\\Baba\\Wall\\Wall_" + std::to_wstring(i) + L".png";
			Resources::Load<graphics::Texture>(key, path);
		}
		}

}
