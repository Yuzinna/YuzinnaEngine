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

		// 현재 설정된 타일 크기를 가져옵니다. (TilemapRenderer에 정의된 정적 변수 사용)
		math::Vector2 tileSize = TilemapRenderer::TileSize;
		if (tileSize.x <= 0 || tileSize.y <= 0) tileSize = math::Vector2(48.0f, 48.0f); // 안전장치

		for (int i = 0; i < (int)enums::eLayerType::End; ++i)
		{
			Layer* layer = activeScene->GetLayer((enums::eLayerType)i);
			if (layer == nullptr) continue;

			const std::vector<GameObject*> objects = layer->GetGameObjects();
			for (GameObject* obj : objects)
			{
				if (obj == nullptr || !obj->IsActive()) continue;

				Transform* tr = obj->GetComponent<Transform>();
				if (tr == nullptr) continue;

				// Transform의 위치를 타일 크기로 나누어 현재 그리드 인덱스를 계산합니다.
				math::Vector2 pos = tr->GetPosition();
				int objGridX = static_cast<int>(pos.x / tileSize.x);
				int objGridY = static_cast<int>(pos.y / tileSize.y);

				if (objGridX == (int)gridIndex.x && objGridY == (int)gridIndex.y)
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

		Transform* tr = obj->GetComponent<Transform>();
		if (tr)
		{
			// 타일 크기를 곱하여 실제 화면상의 픽셀 좌표를 계산합니다.
			math::Vector2 tileSize = TilemapRenderer::TileSize;
			if (tileSize.x <= 0 || tileSize.y <= 0) tileSize = math::Vector2(48.0f, 48.0f); // 안전장치

			math::Vector2 screenPos;
			screenPos.x = nextGridPos.x * tileSize.x;
			screenPos.y = nextGridPos.y * tileSize.y;
			
			tr->SetPosition(screenPos);
		}
	}
}
