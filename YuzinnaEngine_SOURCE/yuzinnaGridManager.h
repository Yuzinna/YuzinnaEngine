#pragma once
#include "CommonInclude.h"
#include "yuzinnaGameObject.h"
#include <vector>

namespace yuzinna
{
	class GridManager
	{
	public:
		// 특정 그리드 인덱스(x, y)에 있는 모든 GameObject를 반환합니다.
		static std::vector<GameObject*> GetObjectsAt(math::Vector2 gridIndex);

		// 오브젝트를 특정 그리드 위치로 이동시키고 Transform의 실제 좌표도 업데이트합니다.
		static void MoveObject(GameObject* obj, math::Vector2 nextGridPos);
	};
}
