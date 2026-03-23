#pragma once
#include "CommonInclude.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaEnums.h"
#include <vector>

namespace yuzinna
{
	using namespace enums;

	struct Rule
	{
		eWordType noun;
		eWordType verb;
		eWordType target;
	};

	class RuleManager
	{
	public:
		// 현재 맵의 모든 단어 블록을 검사하여 규칙 리스트를 갱신합니다.
		static void UpdateRules();

		// 특정 명사가 특정 속성을 가지고 있는지 확인합니다. (예: Baba Is You)
		static bool HasRule(eWordType noun, eWordType target);

		// 오브젝트 이름(L"Baba", L"Rock" 등)을 통해 WordType을 반환합니다.
		static eWordType GetTypeByName(const std::wstring& name);

		// 현재 활성화된 모든 규칙을 반환합니다.
		static const std::vector<Rule>& GetRules() { return mRules; }

	private:
		static std::vector<Rule> mRules;

		// 특정 단어가 명사(Noun)인지 확인하는 헬퍼 함수
		static bool IsNoun(eWordType type);
		// 특정 단어가 속성(Property)인지 확인하는 헬퍼 함수
		static bool IsProperty(eWordType type);
	};
}
