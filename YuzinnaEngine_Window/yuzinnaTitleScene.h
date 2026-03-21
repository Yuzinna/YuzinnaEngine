#pragma once
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaScene.h"
namespace yuzinna
{
	class TitleScene :public Scene
	{
	public:
		TitleScene();
		~TitleScene();

		 void Initialize() override;
		 void Update() override;
		 void LateUpdate() override;
		 void Render(HDC hdc) override;

		 void OnEnter() override;
		 void OnExit() override;
	};
}

