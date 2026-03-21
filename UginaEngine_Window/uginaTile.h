#pragma once
#include "..\\UginaEngine_SOURCE\\uginaGameObject.h"
namespace ugina
{
	class Tile:public GameObject
	{
	public:
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void SetIndexPosition(int x, int y);

	private:

	};
}

