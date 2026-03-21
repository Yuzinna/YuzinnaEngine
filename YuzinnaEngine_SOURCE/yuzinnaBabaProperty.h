#pragma once
#include "yuzinnaComponent.h"
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
		WORD,   // ?⑥뼱 (洹쒖튃??留뚮뱶?????곗엫)
		END
	};

	class BabaProperty : public Component
	{
	public:
		BabaProperty();
		~BabaProperty();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void AddProperty(eBabaProperty prop);
		void RemoveProperty(eBabaProperty prop);
		void ClearProperties();
		bool HasProperty(eBabaProperty prop);

		const std::vector<eBabaProperty>& GetProperties() const { return mProperties; }

	private:
		std::vector<eBabaProperty> mProperties;
	};
}
