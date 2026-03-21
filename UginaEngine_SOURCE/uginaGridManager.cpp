#include "uginaGridManager.h"
#include "uginaSceneManager.h"
#include "uginaScene.h"
#include "uginaLayer.h"
#include "uginaTransform.h"
#include "uginaTilemapRenderer.h"
#include "uginaBabaProperty.h"

namespace ugina
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

	bool GridManager::HasProperty(math::Vector2 gridIndex, eBabaProperty property)
	{
		std::vector<GameObject*> objects = GetObjectsAt(gridIndex);
		for (GameObject* obj : objects)
		{
			BabaProperty* p = obj->GetComponent<BabaProperty>();
			if (p && p->HasProperty(property))
				return true;
		}
		return false;
	}

	std::vector<GameObject*> GridManager::GetObjectsWithProperty(math::Vector2 gridIndex, eBabaProperty property)
	{
		std::vector<GameObject*> results;
		std::vector<GameObject*> objects = GetObjectsAt(gridIndex);
		for (GameObject* obj : objects)
		{
			BabaProperty* p = obj->GetComponent<BabaProperty>();
			if (p && p->HasProperty(property))
				results.push_back(obj);
		}
		return results;
	}

	bool GridManager::TryMove(GameObject* obj, math::Vector2 direction)
	{
		if (obj == nullptr) return false;

		math::Vector2 nextGridPos = obj->GetGridIndex() + direction;

		// 1. 다음 칸에 있는 물체들 확인
		std::vector<GameObject*> targets = GetObjectsAt(nextGridPos);

		// 2. 가로막는 것이 있는지 확인
		for (GameObject* target : targets)
		{
			BabaProperty* prop = target->GetComponent<BabaProperty>();
			if (prop == nullptr) continue;

			// STOP 속성이 있으면 이동 불가
			if (prop->HasProperty(eBabaProperty::STOP))
			{
				return false;
			}

			// PUSH 속성이 있으면 밀어본다
			if (prop->HasProperty(eBabaProperty::PUSH))
			{
				// 연쇄적으로 밀기에 실패하면 나도 못 움직임
				if (!TryMove(target, direction))
				{
					return false;
				}
			}
		}

		// 3. 이동 수행
		moveObject(obj, nextGridPos);
		return true;
	}

	void GridManager::moveObject(GameObject* obj, math::Vector2 nextGridPos)
	{
		obj->SetGridIndex(nextGridPos);

		// Transform 위치 업데이트 (픽셀 좌표)
		Transform* tr = obj->GetComponent<Transform>();
		if (tr)
		{
			// TilemapRenderer에서 설정한 전역 타일 크기를 활용
			math::Vector2 screenPos;
			screenPos.x = nextGridPos.x * TilemapRenderer::TileSize.x;
			screenPos.y = nextGridPos.y * TilemapRenderer::TileSize.y;
			tr->SetPosition(screenPos);
		}
	}
}
