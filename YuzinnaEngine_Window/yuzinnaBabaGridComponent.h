#pragma once
#include "yuzinnaScript.h"
#include <vector>

namespace yuzinna
{
	enum class eBabaProperty
	{
		NONE = 0,
		YOU,    // ?닿? 議곗쥌??
		PUSH,   // 諛 ???덉쓬
		STOP,   // 留됲옒
		WIN,    // ?우쑝硫??밸━
		SINK,   // ?우쑝硫?媛숈씠 ?щ씪吏?
		PULL,   // ?밴만 ???덉쓬
		WORD,   // ?⑥뼱 (洹쒖튃??
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
		math::Vector2 mAtlasIndex; // ?ㅽ봽?쇱씠???쒗듃 ??????몃뜳??
		std::wstring mName;
		std::vector<eBabaProperty> mProperties;
	};
}
