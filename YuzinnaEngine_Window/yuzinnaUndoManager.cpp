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
	bool UndoManager::mbCanSave = true;

	void UndoManager::SaveState()
	{
		if (!mbCanSave) return; // 이번 턴에 이미 저장했다면 패스

		Scene* activeScene = SceneManager::GetActiveScene();
		if (activeScene == nullptr) return;

		std::vector<ObjectState> currentState;

		for (int i = 0; i < (int)enums::eLayerType::End; ++i)
		{
			// ... (레이어 체크 로직 동일)
			if ((enums::eLayerType)i == enums::eLayerType::Camera ||
				(enums::eLayerType)i == enums::eLayerType::UI ||
				(enums::eLayerType)i == enums::eLayerType::None)
				continue;

			Layer* layer = activeScene->GetLayer((enums::eLayerType)i);
			if (layer == nullptr) continue;

			const std::vector<GameObject*>& objs = layer->GetGameObjects();
			for (GameObject* obj : objs)
			{
				// Dead 상태인 오브젝트도 Undo를 위해 저장해야 함 (이미 Dead이면 위치는 의미 없음)
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

					currentState.push_back({ obj, gridPos, version, animName, obj->GetState() });
				}
			}
		}

		mHistory.push(currentState);
		mbCanSave = false; // 한 번 저장했으면 다음 명시적 리셋 전까지 저장 불가
	}

	void UndoManager::Undo()
	{
		if (mHistory.empty()) return;

		std::vector<ObjectState> lastState = mHistory.top();
		mHistory.pop();

		for (const auto& state : lastState)
		{
			// 오브젝트 상태 복구 (Dead -> Active 등)
			if (state.state == GameObject::eState::Active)
			{
				state.obj->SetActive(true); // Active 상태로 강제 전환
			}
			else if (state.state == GameObject::eState::Dead)
			{
				// 사실 Undo 시점에 Dead인 것을 굳이 Dead로 바꿀 필요는 없지만 로직상 명시
				// state.obj->death(); // friend 관계이므로 필요 시 호출 가능
			}

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
		mbCanSave = true; // Undo 후에는 다시 저장 가능하게 함
	}
}
