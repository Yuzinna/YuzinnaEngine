#include "uginaBabaPlayerScript.h"
#include "uginaInput.h"
#include "uginaBabaGridComponent.h"
#include "uginaBabaGridManager.h"
#include "uginaGameObject.h"
#include "uginaAnimator.h"

namespace ugina
{
	BabaPlayerScript::BabaPlayerScript()
	{
	}

	BabaPlayerScript::~BabaPlayerScript()
	{
	}

	void BabaPlayerScript::Initialize()
	{
	}

	void BabaPlayerScript::Update()
	{
		// Undo 처리 (Z키)
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			BabaGridManager::Undo();
			return;
		}

		// 1. 방향키 입력을 확인합니다.
		math::Vector2 dir = math::Vector2::Zero;
		std::wstring animName = L"";

		if (Input::GetKeyDown(eKeyCode::W))
		{
			dir = math::Vector2(0, -1);
			animName = L"BabaUp";
		}
		else if (Input::GetKeyDown(eKeyCode::S))
		{
			dir = math::Vector2(0, 1);
			animName = L"BabaDown";
		}
		else if (Input::GetKeyDown(eKeyCode::A))
		{
			dir = math::Vector2(-1, 0);
			animName = L"BabaLeft";
		}
		else if (Input::GetKeyDown(eKeyCode::D))
		{
			dir = math::Vector2(1, 0);
			animName = L"BabaRight";
		}

		if (dir != math::Vector2::Zero)
		{
			// 이동할 때마다 애니메이션 인덱스 증가 (0~3 순환)
			mAnimIndex = (mAnimIndex + 1) % 4;
			std::wstring fullAnimName = animName + L"_" + std::to_wstring(mAnimIndex);

			// 애니메이션 변경
			Animator* animator = GetOwner()->GetComponent<Animator>();
			if (animator && animName != L"")
			{
				animator->PlayAnimation(fullAnimName);
			}

			// 이동 전에 현재 상태를 저장 (Undo용)
			BabaGridManager::SaveState();
			move(dir);
		}
	}

	void BabaPlayerScript::move(math::Vector2 direction)
	{
		// 2. 현재 내 객체에 붙은 BabaGridComponent를 가져옵니다.
		BabaGridComponent* comp = GetOwner()->GetComponent<BabaGridComponent>();
		if (comp == nullptr) return;

		// 3. 내가 'YOU' 속성을 가지고 있을 때만 이동합니다.
		if (comp->HasProperty(eBabaProperty::YOU))
		{
			// 4. 격자 매니저를 통해 이동을 시도합니다.
			// (밀기 로직은 매니저가 재귀적으로 처리합니다.)
			BabaGridManager::TryMove(comp, direction);
		}
	}
}
