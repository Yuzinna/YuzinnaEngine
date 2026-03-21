#pragma once
#include "..\\UginaEngine_SOURCE\\uginaGameObject.h"
namespace ugina
{
	class Player :public GameObject
	{
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
	};

}

