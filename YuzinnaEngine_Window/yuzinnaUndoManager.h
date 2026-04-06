#pragma once
#include "CommonInclude.h"
#include <vector>
#include <stack>
#include <string>

namespace yuzinna
{
	class GameObject;

	struct ObjectState
	{
		GameObject* obj;
		math::Vector2 gridPos;
		int version;
		std::wstring animName; // 추가: 현재 재생 중인 애니메이션 이름
	};

	class UndoManager
	{
	public:
		// 현재 맵의 모든 오브젝트 상태를 저장합니다.
		static void SaveState();

		// 이전 상태로 되돌립니다.
		static void Undo();

		// 히스토리를 비웁니다 (스테이지 시작 시)
		static void Clear() { while (!mHistory.empty()) mHistory.pop(); }

	private:
		static std::stack<std::vector<ObjectState>> mHistory;
	};
}
