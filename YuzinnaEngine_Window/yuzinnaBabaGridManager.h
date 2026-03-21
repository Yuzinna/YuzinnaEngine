#pragma once
#include "CommonInclude.h"
#include "yuzinnaBabaGridComponent.h"
#include "yuzinnaBabaWordComponent.h"
#include <vector>
#include <map>
#include <stack>

namespace yuzinna
{
	struct BabaRule
	{
		std::wstring subject; // "BABA", "ROCK" ??
		eBabaProperty property; // YOU, PUSH ??
		std::wstring transformTo; // "BABA"媛 "KEKE"濡?蹂????
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
		// 寃⑹옄 ?꾩껜瑜??ㅼ틪?섏뿬 洹쒖튃???덈줈 ?뚯떛?⑸땲??
		static void ParseRules();

		// ?뚯떛??洹쒖튃???꾩옱 紐⑤뱺 ?ㅻ툕?앺듃???곸슜?⑸땲??
		static void ApplyRules();

		// ?꾩옱 留듭쓽 紐⑤뱺 ?곹깭瑜?湲곕줉?⑸땲??(Undo??.
		static void SaveState();

		// ?댁쟾 ?댁쑝濡??곹깭瑜??섎룎由쎈땲??
		static void Undo();

		// ... (?섎㉧吏 ?⑥닔??
		static std::vector<BabaGridComponent*> GetGridAt(math::Vector2 gridIndex);
		static bool HasProperty(math::Vector2 gridIndex, eBabaProperty property);
		static std::vector<BabaGridComponent*> GetComponentsWithProperty(math::Vector2 gridIndex, eBabaProperty property);
		static bool TryMove(BabaGridComponent* comp, math::Vector2 direction);

	private:
		static void moveComponent(BabaGridComponent* comp, math::Vector2 nextGridPos);
		
		static std::vector<BabaRule> mCurrentRules;
		static std::stack<TurnState> mHistory; // Undo ?대젰
	};
}
