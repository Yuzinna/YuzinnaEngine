#include "yuzinnaGridManager.h"
#include "yuzinnaSceneManager.h"
#include "yuzinnaScene.h"
#include "yuzinnaLayer.h"
#include "yuzinnaTransform.h"
#include "yuzinnaTilemapRenderer.h"

namespace yuzinna
{
	std::vector<GameObject*> GridManager::GetObjectsAt(math::Vector2 gridIndex)
	{
		std::vector<GameObject*> results;
		Scene* activeScene = SceneManager::GetActiveScene();
		if (activeScene == nullptr) return results;

		for (int i = 0; i < (int)enums::eLayerType::End; ++i)
		{
			Layer* layer = activeScene->GetLayer((enums::eLayerType)i);
			if (layer == nullptr) continue;

			const std::vector<GameObject*> objects = layer->GetGameObjects();
			for (GameObject* obj : objects)
			{
				if (obj == nullptr || !obj->IsActive()) continue;

				if (obj->GetGridIndex().x == gridIndex.x && obj->GetGridIndex().y == gridIndex.y)
				{
					results.push_back(obj);
				}
			}
		}
		return results;
	}

	void GridManager::MoveObject(GameObject* obj, math::Vector2 nextGridPos)
	{
		if (obj == nullptr) return;

		obj->SetGridIndex(nextGridPos);

		// Transform 위치 업데이트 (화면 좌표)
		Transform* tr = obj->GetComponent<Transform>();
		if (tr)
		{
			// TilemapRenderer에서 설정한 전역 타일 크기를 활용 (가정)
			// 실제 프로젝트 구조에 맞춰 조정 필요
			math::Vector2 screenPos;
			screenPos.x = nextGridPos.x * 48.0f; // 기본 타일 크기 예시 (48x48)
			screenPos.y = nextGridPos.y * 48.0f;
			tr->SetPosition(screenPos);
		}
	}
}
