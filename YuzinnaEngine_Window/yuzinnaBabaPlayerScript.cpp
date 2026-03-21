#include "yuzinnaBabaPlayerScript.h"
#include "yuzinnaInput.h"
#include "yuzinnaBabaGridComponent.h"
#include "yuzinnaBabaGridManager.h"
#include "yuzinnaGameObject.h"
#include "yuzinnaAnimator.h"

namespace yuzinna
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
		// Undo 泥섎━ (Z??
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			BabaGridManager::Undo();
			return;
		}

		// 1. 諛⑺뼢???낅젰???뺤씤?⑸땲??
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
			// ?대룞???뚮쭏???좊땲硫붿씠???몃뜳??利앷? (0~3 ?쒗솚)
			mAnimIndex = (mAnimIndex + 1) % 4;
			std::wstring fullAnimName = animName + L"_" + std::to_wstring(mAnimIndex);

			// ?좊땲硫붿씠??蹂寃?
			Animator* animator = GetOwner()->GetComponent<Animator>();
			if (animator && animName != L"")
			{
				animator->PlayAnimation(fullAnimName);
			}

			// ?대룞 ?꾩뿉 ?꾩옱 ?곹깭瑜????(Undo??
			BabaGridManager::SaveState();
			move(dir);
		}
	}

	void BabaPlayerScript::move(math::Vector2 direction)
	{
		// 2. ?꾩옱 ??媛앹껜??遺숈? BabaGridComponent瑜?媛?몄샃?덈떎.
		BabaGridComponent* comp = GetOwner()->GetComponent<BabaGridComponent>();
		if (comp == nullptr) return;

		// 3. ?닿? 'YOU' ?띿꽦??媛吏怨??덉쓣 ?뚮쭔 ?대룞?⑸땲??
		if (comp->HasProperty(eBabaProperty::YOU))
		{
			// 4. 寃⑹옄 留ㅻ땲?瑜??듯빐 ?대룞???쒕룄?⑸땲??
			// (諛湲?濡쒖쭅? 留ㅻ땲?媛 ?ш??곸쑝濡?泥섎━?⑸땲??)
			BabaGridManager::TryMove(comp, direction);
		}
	}
}
