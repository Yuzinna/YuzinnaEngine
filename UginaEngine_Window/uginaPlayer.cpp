#include "uginaPlayer.h"
#include "uginaInput.h"
#include "uginaTransform.h"
#include "uginaTime.h"

namespace ugina
{
	void Player::Initialize()
	{
		GameObject::Initialize();
	}
	void Player::Update()
	{
		GameObject::Update();
	}
	void Player::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}