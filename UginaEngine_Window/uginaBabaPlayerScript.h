#pragma once
#include "uginaScript.h"

namespace ugina
{
	class BabaPlayerScript : public Script
	{
	public:
		BabaPlayerScript();
		~BabaPlayerScript();

		void Initialize() override;
		void Update() override;

	private:
		// 특정 방향으로 이동을 시도합니다.
		void move(math::Vector2 direction);

		int mAnimIndex = 0;
	};
}
