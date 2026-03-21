#pragma once
#include "uginaResource.h"
#include "uginaTexture.h"
namespace ugina
{
	class Animation : public Resource
	{
	public:

		struct Sprite
		{
			//��������Ʈ��Ʈ���� ���罺������Ʈ �̹����� �»�� ��ǩ��
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;

			//�ִϸ��̼� ��������Ʈ�� ����ð�����
			float duration;

			Sprite()
				: leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, duration(0.0f)
			{
				
			}
		};
		Animation();
		~Animation();

		HRESULT Load(const std::wstring& path) override;

		void Update();
		void Render(HDC hdc);

		void CreateAnimation(const std::wstring& name
			, graphics::Texture* spriteSheet
			, Vector2 leftTop
			, Vector2 size
			, Vector2 offset
			, UINT spriteLength
			, float duration
			, bool vertical = false);

		void Reset();
		bool IsComplete() { return mbComplete; }
		void SetAnimator(class Animator* animator) { mAnimator = animator; }

	private:
		
		class Animator* mAnimator;
		//��������Ʈ ��Ʈ�� �ؽ��� �̹����� ��� ����
		graphics::Texture* mTexture;
		
		//�ؽ��Ŀ��� �� �ִϸ��̼ǿ��� ������ �κи��� �ڸ���
		//�׺κ��� �� ��������Ʈ vector�� �ɰ��� ������ѳ���
		std::vector<Sprite> mAnimationSheet;
		int mIndex;
		float mTime;
		//���� �ִϸ��̼��� ������ ����Ǿ��°�
		bool mbComplete;
	};
}

