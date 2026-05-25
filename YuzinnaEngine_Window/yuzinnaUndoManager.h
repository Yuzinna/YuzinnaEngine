#pragma once
#include "CommonInclude.h"
#include <vector>
#include <stack>
#include <string>
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaGameObject.h"
namespace yuzinna
{
	class GameObject;

	struct ObjectState
	{
		GameObject* obj;
		std::wstring name; // 추가: 오브젝트 이름 (변이 복구용)
		math::Vector2 gridPos;
		int version;
		std::wstring animName; // 추가: 현재 재생 중인 애니메이션 이름
		GameObject::eState state; // 추가: 오브젝트 상태 (Active, Dead 등)
	};

	class UndoManager
	{
	public:
		// 현재 맵의 모든 오브젝트 상태를 저장합니다. (한 턴에 한 번만 실제 저장)
		static void SaveState();

		// 다음 턴을 위해 저장 가능 상태로 리셋합니다.
		static void ResetCanSave() { mbCanSave = true; }

		// 이전 상태로 되돌립니다.
		static void Undo();

		// 히스토리를 비웁니다 (스테이지 시작 시)
		static void Clear() { while (!mHistory.empty()) mHistory.pop(); mbCanSave = true; }

	private:
		static std::stack<std::vector<ObjectState>> mHistory;
		static bool mbCanSave;
	};
}
