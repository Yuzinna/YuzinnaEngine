#include "yuzinnaGridManager.h"
#include "yuzinnaSceneManager.h"
#include "yuzinnaScene.h"
#include "yuzinnaLayer.h"
#include "yuzinnaTransform.h"
#include "yuzinnaTilemapRenderer.h"
#include "yuzinnaBabaProperty.h"

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

		// 1. ?ㅼ쓬 移몄뿉 ?덈뒗 臾쇱껜???뺤씤
		std::vector<GameObject*> targets = GetObjectsAt(nextGridPos);

		// 2. 媛濡쒕쭑??寃껋씠 ?덈뒗吏 ?뺤씤
		for (GameObject* target : targets)
		{
			BabaProperty* prop = target->GetComponent<BabaProperty>();
			if (prop == nullptr) continue;

			// STOP ?띿꽦???덉쑝硫??대룞 遺덇?
			if (prop->HasProperty(eBabaProperty::STOP))
			{
				return false;
			}

			// PUSH ?띿꽦???덉쑝硫?諛?대낯??
			if (prop->HasProperty(eBabaProperty::PUSH))
			{
				// ?곗뇙?곸쑝濡?諛湲곗뿉 ?ㅽ뙣?섎㈃ ?섎룄 紐??吏곸엫
				if (!TryMove(target, direction))
				{
					return false;
				}
			}
		}

		// 3. ?대룞 ?섑뻾
		moveObject(obj, nextGridPos);
		return true;
	}

	void GridManager::moveObject(GameObject* obj, math::Vector2 nextGridPos)
	{
		obj->SetGridIndex(nextGridPos);

		// Transform ?꾩튂 ?낅뜲?댄듃 (?쎌? 醫뚰몴)
		Transform* tr = obj->GetComponent<Transform>();
		if (tr)
		{
			// TilemapRenderer?먯꽌 ?ㅼ젙???꾩뿭 ????ш린瑜??쒖슜
			math::Vector2 screenPos;
			screenPos.x = nextGridPos.x * TilemapRenderer::TileSize.x;
			screenPos.y = nextGridPos.y * TilemapRenderer::TileSize.y;
			tr->SetPosition(screenPos);
		}
	}
}
