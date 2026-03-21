#pragma once
#include "..\\UginaEngine_SOURCE\\uginaGameObject.h"

namespace ugina
{
	class Cat : public GameObject
	{
	public:
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;


	private:
	};
}