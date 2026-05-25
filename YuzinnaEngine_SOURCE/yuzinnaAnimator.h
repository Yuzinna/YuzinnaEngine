#pragma once
#include "yuzinnaComponent.h"
#include "yuzinnaAnimation.h"

namespace yuzinna
{
	class Animator : public Component
	{
	public:
		// 애니메이션 이벤트
		struct Event
		{
			// 이벤트 함수 등록
			void operator =(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			// 이벤트 호출
			void operator()()
			{
				if (mEvent)
				{
					mEvent();
				}
			}
			std::function<void()> mEvent;
		};

		struct Events
		{
			Event startEvent;
			Event completeEvent;
			Event endEvent;
		};

		Animator();
		~Animator();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void CreateAnimation(const std::wstring& name
			, graphics::Texture* spriteSheet
			, Vector2 leftTop
			, Vector2 size
			, Vector2 offset
			, UINT spriteLength
			, float duration
			, bool vertical = false);
		
		// 폴더 경로를 통해 애니메이션을 생성하는 함수
		void CreateAnimationByFolder(const std::wstring& name,
			const std::wstring& path,Vector2 offset, float duration);

		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = true);

		// [추가] 모든 애니메이션을 삭제합니다.
		void ClearAnimations();

		Events* FindEvents(const std::wstring& name);
		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);
		bool IsComplete() { return mActiveAnimation->IsComplete(); }
		std::wstring GetActiveAnimationName() { return mActiveAnimation ? mActiveAnimation->GetName() : L""; }
	private:
		std::map<std::wstring, Animation*> mAnimations;

		Animation* mActiveAnimation;
		bool mbLoop;

		std::map<std::wstring, Events*> mEvents;
	};
}
