#pragma once
#include "..\\UginaEngine_SOURCE\\uginaResources.h"
#include "..\\UginaEngine_SOURCE\\uginaTexture.h"

namespace ugina
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