#pragma once
#include "CommonInclude.h"
#include "uginaBabaGridComponent.h"
#include "uginaBabaWordComponent.h"
#include <vector>
#include <map>
#include <stack>

namespace ugina
{
	struct BabaRule
	{
		std::wstring subject; // "BABA", "ROCK" 등
		eBabaProperty property; // YOU, PUSH 등
		std::wstring transformTo; // "BABA"가 "KEKE"로 변할 때
	};

	struct ObjectState
	{
		GameObject* obj;
		math::Vector2 gridIndex;
	};

	typedef std::vector<ObjectState> TurnState;

	class BabaGridManager
	{
	public:
		// 격자 전체를 스캔하여 규칙을 새로 파싱합니다.
		static void ParseRules();

		// 파싱된 규칙을 현재 모든 오브젝트에 적용합니다.
		static void ApplyRules();

		// 현재 맵의 모든 상태를 기록합니다 (Undo용).
		static void SaveState();

		// 이전 턴으로 상태를 되돌립니다.
		static void Undo();

		// ... (나머지 함수들)
		static std::vector<BabaGridComponent*> GetGridAt(math::Vector2 gridIndex);
		static bool HasProperty(math::Vector2 gridIndex, eBabaProperty property);
		static std::vector<BabaGridComponent*> GetComponentsWithProperty(math::Vector2 gridIndex, eBabaProperty property);
		static bool TryMove(BabaGridComponent* comp, math::Vector2 direction);

	private:
		static void moveComponent(BabaGridComponent* comp, math::Vector2 nextGridPos);
		
		static std::vector<BabaRule> mCurrentRules;
		static std::stack<TurnState> mHistory; // Undo 이력
	};
}
