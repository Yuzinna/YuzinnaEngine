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
	}
}
