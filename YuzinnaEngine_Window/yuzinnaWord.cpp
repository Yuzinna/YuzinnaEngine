#include "yuzinnaWord.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaAnimator.h"
#include "..\\YuzinnaEngine_SOURCE\\yuzinnaGameObject.h"

namespace yuzinna
{
	Word::Word()
		: Component(enums::eComponentType::Script)
		, mType(eWordType::None)
		, mbActive(false)
		, mbPrevActive(true) // 처음 Update 진입 시 애니메이션을 재생시키기 위해 반대값으로 설정
	{
	}

	Word::~Word()
	{
	}

	void Word::Initialize()
	{
	}

	void Word::Update()
	{
		// 상태가 변했을 때만 애니메이션을 변경
		if (mbActive != mbPrevActive)
		{
			Animator* ani = GetOwner()->GetComponent<Animator>();
			if (ani)
			{
				std::wstring animName = mbActive ? L"On" : L"Off";
				ani->PlayAnimation(animName, true);
			}
			mbPrevActive = mbActive;
		}
	}


	void Word::LateUpdate()
	{
	}

	void Word::Render(HDC hdc)
	{
	}
}
