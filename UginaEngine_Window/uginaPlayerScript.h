#pragma once
#include "..\\UginaEngine_SOURCE\\uginaScript.h"
namespace ugina
{
	class PlayerScript :public Script
	{
	public:
		enum class eState
		{
			Idle,
			Walk
		};
		PlayerScript();
		~PlayerScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

	private:
		void Move();
	private:
		eState mState;
		class Animator* mAnimator;
		float mSpeed;

		//애니메이션 이벤트에 대한 델리게이트들
		
		//void (*Startevent)();
		//std::function<void()> start;
		//void (*CompleteEvent)();
		//void (*EndEvent)();
	};
}

