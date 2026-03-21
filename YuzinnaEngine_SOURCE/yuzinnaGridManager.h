#pragma once
#include "CommonInclude.h"
#include "yuzinnaGameObject.h"

namespace yuzinna
{
	class GridManager
	{
	public:
		// 현재 씬의 특정 위치(GridIndex)에 있는 모든 오브젝트를 가져옵니다.
		static std::vector<GameObject*> GetObjectsAt(math::Vector2 gridIndex);

		// 위치 이동을 수행하고 화면 좌표(Transform)를 업데이트합니다.
		static void MoveObject(GameObject* obj, math::Vector2 nextGridPos);

	private:
	};
}
