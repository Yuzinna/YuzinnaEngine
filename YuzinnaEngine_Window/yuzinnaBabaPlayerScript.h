#pragma once
#include "yuzinnaScript.h"

namespace yuzinna
{
	class BabaPlayerScript : public Script
	{
	public:
		BabaPlayerScript();
		~BabaPlayerScript();

		void Initialize() override;
		void Update() override;

	private:
		// ?뱀젙 諛⑺뼢?쇰줈 ?대룞???쒕룄?⑸땲??
		void move(math::Vector2 direction);

		int mAnimIndex = 0;
	};
}
