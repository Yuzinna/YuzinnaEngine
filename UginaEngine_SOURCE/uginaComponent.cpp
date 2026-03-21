#include "uginaComponent.h"

namespace ugina
{
	Component::Component(enums::eComponentType type) : mType(type)
	{
	}
	ugina::Component::~Component()
	{
	}
	void Component::Initialize()
	{
	}
	void Component::Update()
	{
	}
	void Component::LateUpdate()
	{
	}
	void Component::Render(HDC hdc)
	{
	}
}
