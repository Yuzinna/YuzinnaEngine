#pragma once
#include "uginaScene.h"

namespace ugina
{
	class BabaScene : public Scene
	{
	public:
		BabaScene();
		~BabaScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void OnEnter() override;
		void OnExit() override;

	private:
	};
}
