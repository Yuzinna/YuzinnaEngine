#include "yuzinnaPlayerScript.h"
#include "yuzinnaInput.h"
#include "yuzinnaTransform.h"
#include "yuzinnaTime.h"
#include "yuzinnaGameObject.h"
#include "yuzinnaAnimator.h"
#include "yuzinnaCat.h"
#include "yuzinnaCatScript.h"
#include "yuzinnaObject.h"
#include "yuzinnaResources.h"
#include "yuzinnaRigidbody.h"

namespace yuzinna
{
	PlayerScript::PlayerScript()
		: mState(PlayerScript::eState::Idle)
		, mAnimator(nullptr)
		, mSpeed(300.0f)
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{


	}
	void PlayerScript::Update()
	{
		Move();
	}
	void PlayerScript::LateUpdate()
	{
	}
	void PlayerScript::Render(HDC hdc)
	{
	}

	

	void PlayerScript::OnCollisionEnter(Collider* other)
	{
		//other->GetOwner()->GetComponent<Transform>()->SetPosition(Vector2(400.0f, 500.0f));
	}

	void PlayerScript::OnCollisionStay(Collider* other)
	{
	}

	void PlayerScript::OnCollisionExit(Collider* other)
	{
	}

	void PlayerScript::Move()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		// 상하좌우 이동 로직
		if (Input::GetKey(eKeyCode::W))
		{
			pos.y -= mSpeed * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::S))
		{
			pos.y += mSpeed * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= mSpeed * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::D))
		{
			pos.x += mSpeed * Time::DeltaTime();
		}

		tr->SetPosition(pos);
	}

	

}