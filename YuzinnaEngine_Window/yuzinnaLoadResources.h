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

		// Baba
		Resources::Load<graphics::Texture>(L"BabaDown", L"..\\Resources\\Baba\\babaDown.png");
		Resources::Load<graphics::Texture>(L"BabaLeft", L"..\\Resources\\Baba\\babaLeft.png");
		Resources::Load<graphics::Texture>(L"BabaRight", L"..\\Resources\\Baba\\babaRight.png");
		Resources::Load<graphics::Texture>(L"BabaUp", L"..\\Resources\\Baba\\babaUp.png");
		Resources::Load<graphics::Texture>(L"BabaWord", L"..\\Resources\\Baba\\Word\\BabaWord.png");
	}
}