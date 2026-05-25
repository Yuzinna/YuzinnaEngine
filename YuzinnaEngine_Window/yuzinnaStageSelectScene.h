#pragma once
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaScene.h"

namespace yuzinna
{
	class StageSelectScene : public Scene
	{
	public:
		StageSelectScene();
		virtual ~StageSelectScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hdc) override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		void CreateStageIcon(int stageNum, int gridX, int gridY);
		
		class WorldMapScript* mCursorScript;
		bool mbAllClear;
	};
}
