#pragma once
#include "uginaScript.h"
#include <vector>

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
		WORD,   // 단어 (규칙용)
		END
	};

	class BabaGridComponent : public Script
	{
	public:
		BabaGridComponent();
		~BabaGridComponent();

		void Initialize() override;
		void Update() override;

		void SetGridIndex(math::Vector2 index) { mGridIndex = index; }
		math::Vector2 GetGridIndex() { return mGridIndex; }

		void SetName(const std::wstring& name) { mName = name; }
		const std::wstring& GetName() const { return mName; }

		void SetAtlasIndex(math::Vector2 index) { mAtlasIndex = index; }
		math::Vector2 GetAtlasIndex() { return mAtlasIndex; }

		void AddProperty(eBabaProperty prop);
		void RemoveProperty(eBabaProperty prop);
		void ClearProperties() { mProperties.clear(); }
		bool HasProperty(eBabaProperty prop);

	private:
		math::Vector2 mGridIndex;
		math::Vector2 mAtlasIndex; // 스프라이트 시트 내 타일 인덱스
		std::wstring mName;
		std::vector<eBabaProperty> mProperties;
	};
}
