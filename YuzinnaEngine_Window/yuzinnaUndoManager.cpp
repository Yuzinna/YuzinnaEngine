#include "yuzinnaUndoManager.h"
#include "yuzinnaGameObject.h"
#include "yuzinnaTransform.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaSceneManager.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaScene.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaLayer.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaGridManager.h"
#include "yuzinnaRuleManager.h"
#include "yuzinnaBabaScript.h"

namespace yuzinna
{
	std::stack<std::vector<ObjectState>> UndoManager::mHistory = {};

	void UndoManager::SaveState()
	{
		Scene* activeScene = SceneManager::GetActiveScene();
		if (activeScene == nullptr) return;

		std::vector<ObjectState> currentState;

		for (int i = 0; i < (int)enums::eLayerType::Max; ++i)
		{
			Layer* layer = activeScene->GetLayer((enums::eLayerType)i);
			if (layer == nullptr) continue;

			const std::vector<GameObject*>& objs = layer->GetGameObjects();
			for (GameObject* obj : objs)
			{
				Transform* tr = obj->GetComponent<Transform>();
				if (tr)
				{
					Vector2 pos = tr->GetPosition();
					// 현재 그리드 좌표 저장 (50픽셀 기준)
					Vector2 gridPos(std::round(pos.x / 50.0f), std::round(pos.y / 50.0f));

					int version = 0;
					BabaScript* script = obj->GetComponent<BabaScript>();
					if (script) version = script->GetVersion();

					currentState.push_back({ obj, gridPos, version });
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

			// 바바 스크립트의 애니메이션 버전도 원복
			BabaScript* script = state.obj->GetComponent<BabaScript>();
			if (script) script->SetVersion(state.version);
		}

		// 상태가 변했으니 규칙을 다시 갱신
		RuleManager::UpdateRules();
	}
}
