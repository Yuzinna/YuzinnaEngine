#pragma once
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaScript.h"
#include <map>

namespace yuzinna
{
	class WorldMapScript : public Script
	{
	public:
		WorldMapScript();
		virtual ~WorldMapScript();

		virtual void Initialize() override;
		virtual void Update() override;

		// 스테이지 위치 등록 및 0번 스테이지로 초기화
		void AddStage(int stageNum, int gridX, int gridY);
		void SetToStage(int stageNum);
		bool HasStage(int stageNum);

	private:
		void Move(math::Vector2 direction);
		void TryEnterStage();
		void UpdatePosition();

		math::Vector2 mGridPos;    // 현재 그리드 좌표 (0~32, 0~17)
		const float mGridSize = 24.0f;
		const math::Vector2 mCursorOffset = math::Vector2(0.0f, 0.0f); // 엔진의 중앙 정렬을 사용하므로 0으로 설정

		// 스테이지 정보: (gridX, gridY) -> stageNum
		std::map<std::pair<int, int>, int> mStages;
	};
}
