#include "yuzinnaWorldMapScript.h"
#include "yuzinnaInput.h"
#include "yuzinnaTransform.h"
#include "yuzinnaGameObject.h"
#include "yuzinnaMapManager.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaSceneManager.h"

namespace yuzinna
{
	WorldMapScript::WorldMapScript()
		: Script()
		, mGridPos(0.0f, 0.0f)
	{
	}

	WorldMapScript::~WorldMapScript()
	{
	}

	void WorldMapScript::Initialize()
	{
		UpdatePosition();
	}

	void WorldMapScript::Update()
	{
		// 방향키 입력
		if (Input::GetKeyDown(eKeyCode::W))    Move(math::Vector2(0.0f, -1.0f));
		if (Input::GetKeyDown(eKeyCode::S))  Move(math::Vector2(0.0f, 1.0f));
		if (Input::GetKeyDown(eKeyCode::A))  Move(math::Vector2(-1.0f, 0.0f));
		if (Input::GetKeyDown(eKeyCode::D)) Move(math::Vector2(1.0f, 0.0f));

		// 스페이스바 입력 시 스테이지 진입
		if (Input::GetKeyDown(eKeyCode::Space))
		{
			TryEnterStage();
		}
	}

	void WorldMapScript::Move(math::Vector2 direction)
	{
		math::Vector2 nextGridPos = mGridPos + direction;
		int nextX = (int)nextGridPos.x;
		int nextY = (int)nextGridPos.y;

		// [이동 제한 로직]
		// 다음 칸에 스테이지(StageIcon)가 존재하는지 확인합니다.
		auto it = mStages.find({ nextX, nextY });
		if (it != mStages.end())
		{
			// 스테이지가 있는 칸으로만 이동 허용
			mGridPos = nextGridPos;
			UpdatePosition();
		}
		// 스테이지가 없는 빈 공간으로는 이동하지 않습니다.
	}

	void WorldMapScript::UpdatePosition()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		if (tr)
		{
			// 엔진의 중앙 정렬(Center Pivot)을 사용하므로 24px 그리드의 중앙(+12px)을 기준으로 설정
			math::Vector2 pixelPos;
			pixelPos.x = (mGridPos.x * 24.0f) + 12.0f;
			pixelPos.y = (mGridPos.y * 24.0f) + 12.0f;
			tr->SetPosition(pixelPos);
		}
	}

	void WorldMapScript::AddStage(int stageNum, int gridX, int gridY)
	{
		mStages[{gridX, gridY}] = stageNum;
	}

	void WorldMapScript::SetToStage(int stageNum)
	{
		// 지정된 스테이지 번호의 좌표를 찾아 이동
		for (auto const& [pos, num] : mStages)
		{
			if (num == stageNum)
			{
				mGridPos.x = (float)pos.first;
				mGridPos.y = (float)pos.second;
				UpdatePosition();
				return;
			}
		}
	}

	bool WorldMapScript::HasStage(int stageNum)
	{
		for (auto const& [pos, num] : mStages)
		{
			if (num == stageNum) return true;
		}
		return false;
	}

	void WorldMapScript::TryEnterStage()
	{
		int x = (int)mGridPos.x;
		int y = (int)mGridPos.y;

		auto it = mStages.find({ x, y });
		if (it != mStages.end())
		{
			MapManager::SetCurrentStage(it->second);
			SceneManager::LoadScene(L"PlayScene");
		}
	}
}
