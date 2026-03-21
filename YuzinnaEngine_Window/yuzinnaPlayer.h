#pragma once
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaGameObject.h"
namespace yuzinna
{
	class Player :public GameObject
	{
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
	};

}

