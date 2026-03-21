#pragma once
#include "uginaComponent.h"
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
		WORD,   // 단어 (규칙을 만드는 데 쓰임)
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
