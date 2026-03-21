#pragma once
#include "CommonInclude.h"
#include "uginaGameObject.h"

namespace ugina
{
	enum class eBabaProperty
	{
		NONE = 0,
		YOU,    // 내가 조종함
		PUSH,   // 밀 수 있음
		STOP,   // 막힘
		WIN,    // 닿으면 승리
		SINK,   // 닿으면 같이 사라짐
		PULL,   // 당길 수 있음
		END
	};

	class GridManager
	{
	public:
		// 현재 씬의 특정 위치(GridIndex)에 있는 모든 오브젝트를 가져옵니다.
		static std::vector<GameObject*> GetObjectsAt(math::Vector2 gridIndex);

		// 특정 위치에 특정 속성(STOP, PUSH 등)을 가진 오브젝트가 있는지 확인합니다.
		static bool HasProperty(math::Vector2 gridIndex, eBabaProperty property);

		// 특정 위치에 있는 물체들 중 특정 속성을 가진 물체만 골라냅니다.
		static std::vector<GameObject*> GetObjectsWithProperty(math::Vector2 gridIndex, eBabaProperty property);

		// 격자 이동을 시도합니다 (재귀적으로 미는 로직 포함).
		static bool TryMove(GameObject* obj, math::Vector2 direction);

	private:
		// 실제 이동을 수행하고 화면 좌표(Transform)를 업데이트합니다.
		static void moveObject(GameObject* obj, math::Vector2 nextGridPos);
	};
}
