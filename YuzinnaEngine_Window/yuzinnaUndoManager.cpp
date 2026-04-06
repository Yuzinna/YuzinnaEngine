#include "yuzinnaUndoManager.h"
#include "yuzinnaGameObject.h"
#include "yuzinnaTransform.h"
#include "yuzinnaAnimator.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaSceneManager.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaScene.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaLayer.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaGridManager.h"
#include "yuzinnaRuleManager.h"
#include "yuzinnaBabaScript.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaTilemapRenderer.h"
namespace yuzinna
{
	std::stack<std::vector<ObjectState>> UndoManager::mHistory = {};

	void UndoManager::SaveState()
	{
		Scene* activeScene = SceneManager::GetActiveScene();
		if (activeScene == nullptr) return;

		std::vector<ObjectState> currentState;

		for (int i = 0; i < (int)enums::eLayerType::End; ++i)
		{
			// Undo 대상에서 제외할 레이어 (카메라, UI 등)
			if ((enums::eLayerType)i == enums::eLayerType::Camera ||
				(enums::eLayerType)i == enums::eLayerType::UI ||
				(enums::eLayerType)i == enums::eLayerType::None)
				continue;

			Layer* layer = activeScene->GetLayer((enums::eLayerType)i);
			if (layer == nullptr) continue;

			const std::vector<GameObject*>& objs = layer->GetGameObjects();
			for (GameObject* obj : objs)
			{
				Transform* tr = obj->GetComponent<Transform>();
				if (tr)
				{
					Vector2 pos = tr->GetPosition();
					Vector2 tileSize = TilemapRenderer::TileSize;
					if (tileSize.x <= 0 || tileSize.y <= 0) tileSize = Vector2(48.0f, 48.0f);

					// 현재 그리드 좌표 저장
					Vector2 gridPos(std::round(pos.x / tileSize.x), std::round(pos.y / tileSize.y));

					int version = 0;
					std::wstring animName = L"";

					// 바바 스크립트 정보 저장
					BabaScript* babaScript = obj->GetComponent<BabaScript>();
					if (babaScript) version = babaScript->GetVersion();

					// 애니메이션 정보 저장
					Animator* ani = obj->GetComponent<Animator>();
					if (ani) animName = ani->GetActiveAnimationName();

					currentState.push_back({ obj, gridPos, version, animName });
				}
			}
		}

		mHistory.push(currentState);
	}

	void UndoManager::Undo()
	{
		if (mHistory.empty()) return;

		std::vector<ObjectState> lastState = mHistory.top();
		mHistory.pop();

		for (const auto& state : lastState)
		{
			// 오브젝트를 저장된 그리드 위치로 원복
			GridManager::MoveObject(state.obj, state.gridPos);

			// 애니메이션 복구
			Animator* ani = state.obj->GetComponent<Animator>();
			if (ani && !state.animName.empty())
			{
				ani->PlayAnimation(state.animName, true);
			}

			// 바바 스크립트의 애니메이션 버전도 원복
			BabaScript* script = state.obj->GetComponent<BabaScript>();
			if (script) script->SetVersion(state.version);
		}

		// 상태가 변했으니 규칙을 다시 갱신
		RuleManager::UpdateRules();
	}
}
