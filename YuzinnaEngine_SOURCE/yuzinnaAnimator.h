#pragma once
#include "yuzinnaComponent.h"
#include "yuzinnaAnimation.h"

namespace yuzinna
{
	class Animator : public Component
	{
	public:
		//�ִϸ��̼� �̺�Ʈ
		struct Event
		{
			//��ü�� �Ű��ִ� ����� ����
			void operator =(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			//Event����ü�� ������ ����� �� ���� �̸��� ������ ������ function ����(�� �Լ�)�� �ٷ� ȣ���ϱ����� ���۷�����
			void operator()()
			{
				if (mEvent)
				{
					mEvent();
				}
			}
			//��ȯ���� void�� �Ű������� ���� ��������Ʈ ����
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
		//������ �ִ� �ؽ��������� ���ļ� �ϳ��� �ִϸ��̼� ��Ʈ�� ����� �����ϴ� �Լ�
		void CreateAnimationByFolder(const std::wstring& name,
			const std::wstring& path,Vector2 offset, float duration);

		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = true);

		Events* FindEvents(const std::wstring& name);
		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);
		bool IsComplete() { return mActiveAnimation->IsComplete(); }
		std::wstring GetActiveAnimationName() { return mActiveAnimation ? mActiveAnimation->GetName() : L""; }
	private:
		std::map<std::wstring, Animation*> mAnimations;

		Animation* mActiveAnimation;
		//�ִϸ��̼��� ������ ���°�
		bool mbLoop;

		std::map<std::wstring, Events*> mEvents;
	};
}

